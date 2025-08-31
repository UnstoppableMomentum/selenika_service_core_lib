/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#include "command_dispatcher_base.h"

std::string CommandDispatcherBase::DispatchCommand(MessageProcessingData &&messageProcessingData) {
    selenika::core::service::CommandResult res = commandDispatcher_.DispatchCommand(messageProcessingData.getCommand(), messageProcessingData);
    return res.response;
}
