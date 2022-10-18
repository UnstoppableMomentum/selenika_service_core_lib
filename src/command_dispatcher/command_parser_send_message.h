/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef COMMAND_PROCESSOR_COMMAND_PARSER_SEND_MESSAGE_H_
#define COMMAND_PROCESSOR_COMMAND_PARSER_SEND_MESSAGE_H_

#include <iostream>
#include <string>
#include <tuple>
#include <utility>

#include "messaging/message_processing_data.h"
#include "websocket/websocket_session.hpp"

struct CmdParserSendMessage
{
    MessageProcessingData data_;
    CmdParserSendMessage() = delete;
    explicit CmdParserSendMessage(MessageProcessingData data)
        : data_(data) {
        std::cout << __PRETTY_FUNCTION__ << " data:"  << std::endl;
    }

    CmdParserSendMessage(const CmdParserSendMessage &) = delete;

    CmdParserSendMessage(const CmdParserSendMessage &&parser2) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    ~CmdParserSendMessage() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    const CmdParserSendMessage &operator=(CmdParserSendMessage &&parser) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return *this;
    }

    const CmdParserSendMessage &operator=(const CmdParserSendMessage &parser) = delete;

    bool Validate() {
        return true;
    }

    std::tuple<std::string, std::string, std::string, MessageProcessingData> Parse(MessageProcessingData data) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        const std::string from = data.ws_->getId();
        const std::string to = data.pt_.get<std::string>("data.to", "");
        const std::string message = data.pt_.get<std::string>("data.msg", "");
        return std::make_tuple(from, to, message, data);
    }
};


#endif  // COMMAND_PROCESSOR_COMMAND_PARSER_SEND_MESSAGE_H_
