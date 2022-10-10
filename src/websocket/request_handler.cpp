/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#include "interfaces/i_command_dispatcher.h"
#include "sessions.h"
#include "websocket_session.hpp"

#include "request_handler.h"

RequestHandler::RequestHandler(
    boost::shared_ptr<ICommandDispatcher> commandDispatcher)
: sessions_(boost::make_shared<Sessions>())
, commandDispatcher_(commandDispatcher) {
}

RequestHandler::~RequestHandler() = default;

bool RequestHandler::Register(websocket_session* session) {
    return sessions_->insert(session);
}

void RequestHandler::Unregister(websocket_session* session) {
    sessions_->remove(session);
}

std::string RequestHandler::HandleRequest(std::string_view message, websocket_session* ws) {
    return commandDispatcher_->DispatchCommand({message, ws, sessions_});
}


