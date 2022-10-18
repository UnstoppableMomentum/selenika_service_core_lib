/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef MESSAGING_MESSAGE_HANDLER_LEAVE_H_
#define MESSAGING_MESSAGE_HANDLER_LEAVE_H_

#include <string>
#include <string_view>

#include "logging/logging.h"
#include "messaging/response.h"
#include "messaging/message_processing_data.h"
#include "websocket/sessions.h"

selenika::core::service::CommandResult makeResponseDisonnect(std::string id, MessageProcessingData data) {
    selenika::core::service::CommandResult res;
    try {
        SLNK_LOG_DEBUG() << " id:" << id;
        if (id.empty()) {
            res.response = makeResponseError(EError::idIsEmpty);
        } else {
            if (data.sessions_->exists(id)) {
                res.response = makeResponseError(EError::idIsAlreadyConnected);
            } else {
                // TODO(Serg) what to do on disconnect?
                data.ws_->setId(id);
                data.sessions_->remove();
                res.response = makeResponseDisconnect();
            }
        }
    } catch(...) {
        res.response = makeResponseError(EError::invalidRequest);
    }
    return res;
}

#endif  // MESSAGING_MESSAGE_HANDLER_LEAVE_H_
