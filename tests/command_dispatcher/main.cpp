/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#include <iostream>
#include <string>

#include "../../src/command_dispatcher/command_dispatcher.hpp"

class CommandOneParser {
    std::string commandString_;
 public:
    explicit CommandOneParser(std::string commandString)
        : commandString_(commandString) {
    }
    bool Validate() {
        return true;
    }

    std::tuple<int, std::string> Parse(std::string command) {
        std::cout << __FUNCTION__ << " PARSE COMMAND 'ONE' STRING:" << command << std::endl;
        int param0 = 123;
        std::string param1 = "param1 is some string";
        return std::make_tuple(param0, param1);
    }
};

class CommandTwoParser {
    std::string commandString_;
 public:
    explicit CommandTwoParser(std::string commandString)
        : commandString_(commandString) {
    }
    bool Validate() {
        return true;
    }

    std::tuple<int, std::string, bool> Parse(std::string command) {
        std::cout << __FUNCTION__ << " PARSE COMMAND 'ONE' STRING:" << command << std::endl;
        int param0 = 123;
        std::string param1 = "param1 is some string";
        bool param2 = true;
        return std::make_tuple(param0, param1, param2);
    }
};

selenika::core::service::CommandResult CommandOneHandler(int param0, std::string param1) {
    std::cout << __FUNCTION__
        << " param0:" << param0
        << " param1:" << param1
        << " ... DO SOME WORK"
        << std::endl;
    selenika::core::service::CommandResult res;
    res.returnCode = 123;
    return res;
}

selenika::core::service::CommandResult CommandTwoHandler(int param0, std::string param1, bool param2) {
    std::cout << __FUNCTION__
        << " param0:" << param0
        << " param1:" << param1
        << " param2:" << param2
        << " ... DO SOME WORK"
        << std::endl;
    selenika::core::service::CommandResult res;
    res.returnCode = 3456;
    return res;
}


int main(int argc, char *argv[]) {
    const int commandOneId = 12345;
    const int commandTwoId = 67890;

    selenika::core::service::Dispatcher<std::string> commandDispatcher;
    commandDispatcher.AddHandler<CommandOneParser>(commandOneId, CommandOneHandler);
    commandDispatcher.AddHandler<CommandTwoParser>(commandTwoId, CommandTwoHandler);

    selenika::core::service::CommandResult dispatchResult  = commandDispatcher.DispatchCommand(commandOneId , "param1 param2 anything ...");

    auto commandTwoReslut = commandDispatcher.DispatchCommand(commandTwoId , "param1 param2 anything ...");
   
    std::cout << " command one result: " << dispatchResult.returnCode << std::endl;
    std::cout << " command two result: " << commandTwoReslut.returnCode << std::endl;
    return 0;
}
