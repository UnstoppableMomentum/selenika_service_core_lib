/////////////////////////////////
//                             //
// Copyright (c) 2025 Selenika //
//                             //
/////////////////////////////////

#ifndef SLNK_00c1dc8d_6454_4f8b_b6ba_bbec703cd574
#define SLNK_00c1dc8d_6454_4f8b_b6ba_bbec703cd574

#include <functional>
#include <iostream>
#include <map>
#include <stdint.h>
#include <string>
#include <tuple>
#include <utility>

namespace selenika::core::service
{

    class CommandResult
    {
    public:
        CommandResult()
            : returnCode(0)
        {
        }
        int returnCode;
        std::string response;
    };

    template <typename TData, typename TParser, typename... Args>
    struct tuple_reader_sv
    {
        static std::tuple<> read(TData, TParser &&)
        {
            return {};
        }
    };

    template <typename TData, typename TParser, typename First, typename... Rest>
    struct tuple_reader_sv<TData, TParser, First, Rest...>
    {
        static std::tuple<First, Rest...> read(TData packet, TParser &&parser)
        {
            return parser.Parse(packet);
        }
    };

    template <typename TData, typename TResult = CommandResult, typename TCommand = uint32_t>
    class Dispatcher
    {
        std::map<TCommand, std::function<TResult(TData)>> commandMap;

    public:
        template <typename TParser, typename... Args>
        void AddHandler(TCommand command, TResult (*func)(Args...))
        {
            commandMap.emplace(command, [func](TData data)
                               {
                               TParser parser(data);
                               TResult res;
                               if (parser.Validate()) {
                                   auto args = tuple_reader_sv<TData, TParser, Args...>::read(data, std::move(parser));
                                   res = std::apply(func, std::move(args));
                               } else {
                                   res.response = "invalid data";
                               }
                                return res; });
        }

        TResult DispatchCommand(TCommand command, TData data)
        {
            auto it = commandMap.find(command);
            TResult res;
            if (it != commandMap.end())
            {
                res = it->second(data);
            }
            else
            {
                res.response = "command was not registered";
            }
            return res;
        }
    };

} // namespace selenika::core::service

#endif // SLNK_00c1dc8d_6454_4f8b_b6ba_bbec703cd574
