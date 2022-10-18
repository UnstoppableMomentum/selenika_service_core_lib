/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef COMMAND_PROCESSOR_COMMAND_PARSER_LEAVE_H_
#define COMMAND_PROCESSOR_COMMAND_PARSER_LEAVE_H_

#include <iostream>
#include <string>
#include <tuple>
#include <utility>

#include "messaging/message_processing_data.h"


struct CmdParserLeave
{
    MessageProcessingData data_;
    CmdParserLeave() = delete;
    explicit CmdParserLeave(MessageProcessingData data)
        : data_(data) {
        std::cout << __PRETTY_FUNCTION__ << " data:"  << std::endl;
    }

    CmdParserLeave(const CmdParserLeave &) = delete;

    CmdParserLeave(const CmdParserLeave &&parser2) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    ~CmdParserLeave() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    const CmdParserLeave &operator=(CmdParserLeave &&parser) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return *this;
    }

    const CmdParserLeave &operator=(const CmdParserLeave &parser) = delete;

    bool Validate() {
        return true;
    }

    std::tuple<std::string, MessageProcessingData> Parse(MessageProcessingData data) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::string id(data.pt_.get<std::string>("data.id", ""));
        return std::make_tuple(id, data);
    }
};


#endif  // COMMAND_PROCESSOR_COMMAND_PARSER_LEAVE_H_
