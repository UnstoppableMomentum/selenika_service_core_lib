/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef MESSAGING_SIGNALING_PROTOCOL_H_
#define MESSAGING_SIGNALING_PROTOCOL_H_

enum class EResult {
    OK    = 0,
    ERROR = 1
};

enum class EError {
    invalidRequest = 0,
    internalError  = 1,
    recipientNotFound = 2,
    idIsEmpty = 3,
    idIsAlreadyConnected = 4,
    maxNumConnectionsReached = 5
};

#endif  // MESSAGING_SIGNALING_PROTOCOL_H_
