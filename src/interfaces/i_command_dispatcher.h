/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef COMMAND_PROCESSOR_COMMAND_DISPATCHER_H_
#define COMMAND_PROCESSOR_COMMAND_DISPATCHER_H_

#include <string>
#include <string_view>

#include "messaging/message_processing_data.h"

class ICommandDispatcher {
 public:
    virtual ~ICommandDispatcher() {}
    virtual std::string DispatchCommand(MessageProcessingData&& messageProcessingDatae) = 0;
};

#endif  // COMMAND_PROCESSOR_COMMAND_DISPATCHER_H_

