/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef MESSAGING_RESPONSE_H_
#define MESSAGING_RESPONSE_H_

#include <string>
#include <string_view>

#include "./signaling_protocol.h"

std::string makeResponseSuccess();
std::string makeResponseError(EError error);
std::string makeResponseNop();
// TODO (SERG) connect/disconnect
std::string makeResponseSignIn();
std::string makeResponseDisonnect();
std::string makeResponseSendMessage(std::string_view from, std::string_view message);

#endif  // MESSAGING_RESPONSE_H_
