/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef INTERFACES_REQUEST_HANDLER_H_
#define INTERFACES_REQUEST_HANDLER_H_

#include <string>
#include <string_view>

#include <boost/smart_ptr.hpp>

class ICommandDispatcher;
class Sessions;
class websocket_session;

// Represents the shared server state
class RequestHandler {
    boost::shared_ptr<ICommandDispatcher> commandDispatcher_;
    boost::shared_ptr<Sessions> sessions_;

 public:
    explicit RequestHandler(boost::shared_ptr<ICommandDispatcher> commandDispatcher);
    ~RequestHandler();
    bool Register(websocket_session* session);
    void Unregister(websocket_session* session);
    std::string HandleRequest(std::string_view message, websocket_session* ws);
};

#endif  // INTERFACES_REQUEST_HANDLER_H_
