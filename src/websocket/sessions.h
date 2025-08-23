/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef SHARED_STATE_SESSIONS_H_
#define SHARED_STATE_SESSIONS_H_

#include <cstdint>
#include <string>
#include <string_view>
#include <mutex>
#include <unordered_set>

// Forward declaration
class websocket_session;

using TSessions = std::unordered_set<websocket_session*>;
using TSessionsConstItr = TSessions::const_iterator;

// Represents the shared server state
// Keep a list of all the connected clients
class Sessions {
    const uint32_t max_num_connections_;
    // This mutex synchronizes all access to sessions_
    std::mutex mutex_;

    TSessions sessions_;

 public:
    // TODO
    explicit Sessions(uint32_t max_num_connections = 10);
    ~Sessions();
    bool insert(websocket_session *session);
    void remove(websocket_session *session);

    TSessionsConstItr begin() const { return sessions_.begin(); }
    TSessionsConstItr end() const { return sessions_.end(); }
    TSessionsConstItr find(std::string_view id) const;
    size_t size() const { return sessions_.size(); }
    bool exists(std::string_view id) const { return find(id) != end(); }
    bool newConnectionIsAllowed() const { return (sessions_.size() + 1) <= max_num_connections_; }

    int broadcastMessage(std::string message);
    int sendMessage(std::string_view from, std::string_view to, std::string_view message);

#if defined (DEBUG)
 private:
    void dump() const;

#endif
};

#endif  // SHARED_STATE_SESSIONS_H_

