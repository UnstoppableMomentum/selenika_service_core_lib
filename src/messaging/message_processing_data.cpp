/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#include <boost/property_tree/json_parser.hpp>

#include "messaging/message_processing_data.h"
#include "websocket/sessions.h"
#include "websocket/websocket_session.hpp"

MessageProcessingData::MessageProcessingData(std::string_view message, websocket_session* ws,
  boost::shared_ptr<Sessions> sessions)
: ws_(ws)
, sessions_(sessions) {
  std::stringstream ss;
  ss << message;

  boost::property_tree::read_json(ss, pt_);
}

uint32_t MessageProcessingData::getCommand() const {
    return pt_.get<uint32_t>("cmd", -1);
}