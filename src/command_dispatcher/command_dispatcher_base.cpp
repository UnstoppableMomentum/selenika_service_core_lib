/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#include "command_dispatcher_base.h"

#include "command_parser_join.h"
#include "command_parser_send_message.h"
#include "command_handler_join.h"
#include "command_handler_send_message.h"

CommandDispatcherBase::CommandDispatcherBase() {
    selenika::core::service::Dispatcher<MessageProcessingData> commandDispatcher2_;
    AddHandler<ParserCmdJoin>(1, processRequestSignIn);
    AddHandler<CmdParserSendMessage>(3, sendMessage);
}

CommandDispatcherBase::~CommandDispatcherBase() {}

std::string CommandDispatcherBase::DispatchCommand(MessageProcessingData &&messageProcessingData) {
    selenika::core::service::CommandResult res = commandDispatcher_.DispatchCommand(messageProcessingData.getCommand(), messageProcessingData);
    return res.response;
}
