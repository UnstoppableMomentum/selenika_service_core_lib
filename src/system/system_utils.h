/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef SERVICE_SYSTEM_UTILS_H_
#define SERVICE_SYSTEM_UTILS_H_


#include <boost/asio.hpp>
#include <boost/asio/signal_set.hpp>

void runAsService(boost::asio::io_context& ioc, boost::asio::signal_set& signals, const char *output);

#endif  // SERVICE_SYSTEM_UTILS_H_
