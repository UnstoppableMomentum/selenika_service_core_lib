/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef COMMAND_PROCESSOR_COMMAND_DISPATCHER_H_2
#define COMMAND_PROCESSOR_COMMAND_DISPATCHER_H_2

#include <string>

#include "interfaces/i_command_dispatcher.h"

#include "messaging/message_processing_data.h"
#include "command_dispatcher/command_dispatcher.hpp"

class CommandDispatcherBase : public ICommandDispatcher  {
    selenika::core::service::Dispatcher<
        MessageProcessingData,
        selenika::core::service::CommandResult,
        std::string> commandDispatcher_;
 public:
    CommandDispatcherBase();
    virtual ~CommandDispatcherBase();

    template <typename TParser, typename... Args>
    void AddHandler(std::string command, selenika::core::service::CommandResult (*func)(Args...)) {
        commandDispatcher_.AddHandler<TParser>(command, func);
    }

    std::string DispatchCommand(MessageProcessingData&& messageProcessingData) final;
};

#endif  // COMMAND_PROCESSOR_COMMAND_DISPATCHER_H_2

