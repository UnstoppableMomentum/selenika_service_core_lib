/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef SRC_COMMAND_DISPATCHER_COMMAND_DISPATCHER_HPP_
#define SRC_COMMAND_DISPATCHER_COMMAND_DISPATCHER_HPP_

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <utility>


namespace selenika::core::service {

class CommandResult {
 public:
    CommandResult()
        : returnCode(0)
    {}
    int returnCode;
    std::string response;
};

template <typename TData, typename TParser, typename... Args>
struct tuple_reader_sv {
    static std::tuple<> read(TData, TParser&&) {
        return {};
    }
};

template <typename TData, typename TParser, typename First, typename... Rest>
struct tuple_reader_sv<TData, TParser, First, Rest...> {
    static std::tuple<First, Rest...> read(TData packet, TParser &&parser) {
        return parser.Parse(packet);
    }
};

template <typename TData, typename TResult = CommandResult>
class Dispatcher {
    std::map<uint32_t, std::function<TResult(TData)>> commandMap;

 public:
    template <typename TParser, typename... Args>
    void AddHandler(uint32_t command, TResult (*func)(Args...)) {
        commandMap.emplace(command, [func](TData data) {
                               TParser parser(data);
                               TResult res;
                               if (parser.Validate()) {
                                   auto args = tuple_reader_sv<TData, TParser, Args...>::read(data, std::move(parser));
                                   res = std::apply(func, std::move(args));
                               } else {
                                   res.response = "invalid data";
                               }
                                return res;
                           });
    }

    TResult DispatchCommand(uint32_t command, TData data) {
        auto it = commandMap.find(command);
        TResult res;
        if (it != commandMap.end()) {
            res = it->second(data);
        } else {
            res.response = "command was not registered";
        }
        return res;
    }
};

}  // namespace selenika::core::service

#endif  // SRC_COMMAND_DISPATCHER_COMMAND_DISPATCHER_HPP_
