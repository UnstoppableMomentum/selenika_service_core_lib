/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#include <utility>

#include "logging/logging.h"
#include "websocket_session.hpp"
#include "../messaging/response.h"

#include "sessions.h"

Sessions::Sessions(std::uint32_t max_num_connections)
    : max_num_connections_(max_num_connections) {
    SLNK_LOG_DEBUG() << " max_num_connections:" << max_num_connections_;
}

Sessions::~Sessions() = default;

bool Sessions::insert(websocket_session *session) {
    std::lock_guard<std::mutex> lock(mutex_);
    bool res = false;
    if (newConnectionIsAllowed()) {
        sessions_.insert(session);
        res = true;
    }
    return res;
}

void Sessions::remove(websocket_session *session) {
    std::lock_guard<std::mutex> lock(mutex_);
    sessions_.erase(session);
#if defined (DEBUG)
    dump();
#endif
}

TSessionsConstItr Sessions::find(std::string_view id) const {
    TSessionsConstItr res = sessions_.end();
    for (TSessionsConstItr it(sessions_.begin()); it != sessions_.end(); ++it) {
        if ((*it)->getId() == id) {
            res = it;
        }
    }
    return res;
}

// Broadcast a message to all websocket client sessions
int Sessions::broadcastMessage(std::string message) {
    SLNK_LOG_DEBUG() << " message:" << message;
    // Put the message in a shared pointer so we can re-use it for each client
    auto const ss = boost::make_shared<std::string const>(std::move(message));

    int res = 0;
    // Make a local list of all the weak pointers representing
    // the sessions, so we can do the actual sending without
    // holding the mutex:
    std::vector<boost::weak_ptr<websocket_session>> v;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        v.reserve(sessions_.size());
        for (auto p : sessions_) {
            v.emplace_back(p->weak_from_this());
        }
    }

    // For each session in our local list, try to acquire a strong
    // pointer. If successful, then send the message o.n that session.
    for (auto const &wp : v) {
        if (auto sp = wp.lock()) {
            sp->send(ss);
            ++res;
        }
    }
    return res;
}

int Sessions::sendMessage(
    std::string_view from, std::string_view to, std::string_view message) {

    const std::string messageToSend(makeResponseSendMessage(from, message));

    int res = 0;
    // Put the message in a shared pointer so we can re-use it for each client
    auto const ss = boost::make_shared<std::string const>(std::move(messageToSend));

    // Make a local list of all the weak pointers representing
    // the sessions, so we can do the actual sending without
    // holding the mutex:
    std::vector<boost::weak_ptr<websocket_session>> v;
    {
        std::lock_guard<std::mutex> lock(mutex_);
         v.reserve(sessions_.load_factor());
         for (auto p : sessions_) {
             if (p->getId() == to) {
                 ++res;
                 v.emplace_back(p->weak_from_this());
            }
        }
    }

    // For each session in our local list, try to acquire a strong
    // pointer. If successful, then send the message on that session.
    for (auto const &wp : v) {
        SLNK_LOG_DEBUG() << " send to:" << to << " " << message;

        if (auto sp = wp.lock())
            sp->send(ss);
    }
    return res;
}


#if defined (DEBUG)
void Sessions::dump() const {
    SLNK_LOG_DEBUG() << ">>>";
    for (auto p : sessions_) {
        SLNK_LOG_DEBUG() << " id:" << p->getId();
    }
    SLNK_LOG_DEBUG() << "<<<";
}
#endif
