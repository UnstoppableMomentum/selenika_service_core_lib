/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef COMMAND_PROCESSOR_COMMAND_PARSER_JOIN_H_
#define COMMAND_PROCESSOR_COMMAND_PARSER_JOIN_H_

#include <iostream>
#include <string>
#include <tuple>
#include <utility>

#include "messaging/message_processing_data.h"


struct ParserCmdJoin
{
    MessageProcessingData data_;
    ParserCmdJoin() = delete;
    explicit ParserCmdJoin(MessageProcessingData data)
        : data_(data) {
        std::cout << __PRETTY_FUNCTION__ << " data:"  << std::endl;
    }

    ParserCmdJoin(const ParserCmdJoin &) = delete;

    ParserCmdJoin(const ParserCmdJoin &&parser) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    ~ParserCmdJoin() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    const ParserCmdJoin &operator=(ParserCmdJoin &&parser) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return *this;
    }

    const ParserCmdJoin &operator=(const ParserCmdJoin &parser) = delete;

    bool Validate() {
        return true;
    }

    std::tuple<std::string, MessageProcessingData> Parse(MessageProcessingData data) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::string id(data.pt_.get<std::string>("data.id", ""));
        return std::make_tuple(id, data);
    }
};


#endif  // COMMAND_PROCESSOR_COMMAND_PARSER_JOIN_H_
