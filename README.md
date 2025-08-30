# Command Dispatcher
A flexible and type-safe C++ command dispatcher component for building web services and API frameworks. This header-only library provides a mechanism to register and dispatch commands with associated data parsers and handlers.

## Features
Type-Safe Command Handling: Register handlers with specific argument types

Parser Integration: Supports custom parsers for incoming data validation and transformation

Generic Design: Templated to work with various data types and command identifiers

Error Handling: Built-in validation and error response mechanism

Header-Only: Easy integration into existing projects

## Dependencies
C++11 or newer

### Standard Library components:
- ```<functional>```
- ```<map>```
- ```<tuple>```
- ```<string>```

## Usage
### Basic Setup
cpp
```
#include "command_dispatcher.hpp"

using namespace selenika::core::service;

// Define your custom parser
class MyParser {
public:
    MyParser(InputDataType data) : data_(data) {}
    
    bool Validate() {
        // Add validation logic
        return true;
    }
    
    auto Parse(InputDataType data) {
        // Parse and return tuple of arguments
        return std::make_tuple(arg1, arg2, arg3);
    }
};

// Define command handler functions
CommandResult my_command_handler(int arg1, std::string arg2, float arg3) {
    CommandResult res;
    // Your handler logic
    res.returnCode = 0;
    res.response = "Success";
    return res;
}

// Create dispatcher instance
Dispatcher<InputDataType> dispatcher;

// Register handler
dispatcher.AddHandler<MyParser>(COMMAND_ID, &my_command_handler);
```
## Template Parameters
- TData: Type of the input data to be parsed
- TResult: Type of command result (default: CommandResult)
- TCommand: Type of command identifier (default: uint32_t)

## CommandResult Structure
The default result structure contains:
- returnCode: Integer return code
- response: String response message

Custom result types can be used by specifying the TResult template parameter.

## Adding Handlers
Use the AddHandler method to register command handlers:

cpp
``` template <typename TParser, typename... Args>
void AddHandler(TCommand command, TResult (*func)(Args...))
```
- TParser: Parser class that handles data validation and parsing
- Args...: Argument types expected by the handler function
- command: Command identifier
- func: Pointer to handler function

## Dispatching Commands
cpp
```TResult result = dispatcher.DispatchCommand(command_id, input_data);
```

## Parser Requirements
- Custom parsers must implement:
- Constructor that accepts TData
- Validate() method returning bool
- Parse() method returning std::tuple of arguments matching the handler's signature

## Example
``` cpp
// Define a JSON parser
class JsonParser {
public:
    JsonParser(std::string json) : json_(json) {}
    
    bool Validate() {
        // Validate JSON structure
        return true;
    }
    
    auto Parse(std::string json) {
        // Parse JSON and extract parameters
        return std::make_tuple(42, "example", 3.14f);
    }
};

// Handler function
CommandResult handle_example(int id, std::string name, float value) {
    CommandResult res;
    // Process command
    res.returnCode = 0;
    res.response = "Processed: " + name;
    return res;
}

// Registration
dispatcher.AddHandler<JsonParser>(1001, &handle_example);

// Dispatch
std::string json_data = R"({"id": 42, "name": "test", "value": 3.14})";
CommandResult result = dispatcher.DispatchCommand(1001, json_data);
```

## Error Handling
The dispatcher provides default error responses:
- "invalid data" when parser validation fails
- "command was not registered" when no handler is found for a command

## Integration
This component is designed to be integrated into larger web service frameworks. It can be used as the core of:
- HTTP request routers
- RPC systems
- Message queue processors
- API gateways

## License
Copyright (c) 2025 Selenika.