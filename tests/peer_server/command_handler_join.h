/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef MESSAGING_MESSAGE_HANDLER_JOIN_H_
#define MESSAGING_MESSAGE_HANDLER_JOIN_H_

#include <string>
#include <string_view>

#include "logging/logging.h"
#include "messaging/response.h"
#include "messaging/message_processing_data.h"
#include "websocket/sessions.h"
#include "websocket/websocket_session.hpp"

selenika::core::service::CommandResult processRequestSignIn(std::string id, MessageProcessingData data) {
    selenika::core::service::CommandResult res;
    try {
        SLNK_LOG_DEBUG() << " id:" << id;
        if (id.empty()) {
            res.response = makeResponseError(EError::idIsEmpty);
        } else {
            if (data.sessions_->exists(id)) {
                res.response = makeResponseError(EError::idIsAlreadyConnected);
            } else {
                data.ws_->setId(id);
                res.response = makeResponseSignIn();
            }
        }
    } catch(...) {
        res.response = makeResponseError(EError::invalidRequest);
    }
    return res;
}

#endif  // MESSAGING_MESSAGE_HANDLER_JOIN_H_
