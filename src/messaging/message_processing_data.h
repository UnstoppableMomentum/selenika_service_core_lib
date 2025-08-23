/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef MESSAGING_MESSAGE_PROCESSING_DATA_H_
#define MESSAGING_MESSAGE_PROCESSING_DATA_H_

#include <string_view>

#include <boost/smart_ptr.hpp>

#include <boost/property_tree/ptree.hpp>

class websocket_session;
class Sessions;

class MessageProcessingData {
 public:
  MessageProcessingData() {}
  MessageProcessingData(std::string_view message, websocket_session* ws, boost::shared_ptr<Sessions> sessions);

  uint32_t getCommand() const;
  boost::property_tree::ptree pt_;
  websocket_session* ws_;
  boost::shared_ptr<Sessions> sessions_;
};

#endif  // MESSAGING_MESSAGE_PROCESSING_DATA_H_
