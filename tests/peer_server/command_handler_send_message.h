/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef MESSAGING_MESSAGE_HANDLER_SEND_MESSAGE_H_
#define MESSAGING_MESSAGE_HANDLER_SEND_MESSAGE_H_

#include <string>
#include <string_view>

#include "logging/logging.h"
#include "messaging/response.h"
#include "messaging/message_processing_data.h"
#include "websocket/sessions.h"

selenika::core::service::CommandResult sendMessage(
    std::string from, std::string to, std::string message, MessageProcessingData data) {
    selenika::core::service::CommandResult res;
    if (!to.empty() && !message.empty()) {
        res.returnCode = data.sessions_->sendMessage(from, to, message);
        if (res.returnCode > 0) {
            res.response = makeResponseSuccess();
        } else {
            SLNK_LOG_ERROR() << "Invalid send message request: recipient " << to << " not found";
            res.response = makeResponseError(EError::recipientNotFound);
        }
    } else {
        std::stringstream ss;
        ss << "Invalid send message request:";

        if (to.empty()) {
           ss << " recipient id is empty";
        }

        if (message.empty()) {
           ss << " message is empty";
        }

        SLNK_LOG_ERROR() << ss.str();
        res.response = makeResponseError(EError::invalidRequest);
    }
    return res;
}

#endif  // MESSAGING_MESSAGE_HANDLER_SEND_MESSAGE_H_
