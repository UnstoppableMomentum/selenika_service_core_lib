/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

// Peer connection server, multi-threaded
// This implements a peer connection server using WebSocket.
// The `io_context` runs on any number of threads, specified at the command line.

#include <boost/smart_ptr.hpp>

#include "command_line/cmd_line_options.h"
#include "server/ssh_websocket_server.cpp"

#include "command_dispatcher/command_dispatcher_base.h"
#include "command_handler_send_message.h"
#include "command_parser_send_message.h"


int main(int argc, char *argv[]) {
    const CommandLineOptions clo(argc, argv);
    if (clo.HelpMode()) {
        clo.ShowHelp();
        return EXIT_SUCCESS;
    }

    CommandDispatcherBase commandDispatcher;
    commandDispatcher.AddHandler<CmdParserSendMessage>("3", sendMessage);
 
    SshWebSocketServer sshWebSocketServer(clo, boost::make_shared<CommandDispatcherBase>(commandDispatcher));
    int ret = sshWebSocketServer.Run();
    return ret;
}
