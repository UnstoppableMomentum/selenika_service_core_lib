/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef SRC_SERVER_SSH_WEBSOCKET_SERVER_H_
#define SRC_SERVER_SSH_WEBSOCKET_SERVER_H_

#include <boost/smart_ptr.hpp>

#include "command_line/cmd_line_options.h"
#include "interfaces/i_command_dispatcher.h"

class SshWebSocketServer {
  const CommandLineOptions & commandLineOptions_;
  boost::shared_ptr<ICommandDispatcher> commandDispatcher_;
 public:
  explicit SshWebSocketServer(const CommandLineOptions & commandLineOptions, boost::shared_ptr<ICommandDispatcher> commandDispatcher);
  ~SshWebSocketServer();
  int Run();
  void Stop();
};

#endif  // SRC_SERVER_SSH_WEBSOCKET_SERVER_H_

