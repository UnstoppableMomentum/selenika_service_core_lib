/////////////////////////////////
//                             //
// Copyright (c) 2025 Selenika //
//                             //
/////////////////////////////////

#ifndef SLNK_94ae5887_7ca5_4aef_9ded_3ee1e8b97274
#define SLNK_94ae5887_7ca5_4aef_9ded_3ee1e8b97274

#include <string> 

#include "common/selenika_api.h"
#include "command_dispatcher/command_dispatcher.hpp"
#include "interfaces/i_command_dispatcher.h"
#include "messaging/message_processing_data.h"

// Base class implementing web socket service
class SELENIKA_API CommandDispatcherBase : public ICommandDispatcher
{

    selenika::core::service::Dispatcher<
        MessageProcessingData,
        selenika::core::service::CommandResult,
        std::string>
        commandDispatcher_;

public:
    CommandDispatcherBase() = default;
    virtual ~CommandDispatcherBase() = default;

    template <typename TParser, typename... Args>
    void AddHandler(std::string command, selenika::core::service::CommandResult (*func)(Args...))
    {
        commandDispatcher_.AddHandler<TParser>(command, func);
    }

    std::string DispatchCommand(MessageProcessingData &&messageProcessingData) final;

};

#endif // SLNK_94ae5887_7ca5_4aef_9ded_3ee1e8b97274
