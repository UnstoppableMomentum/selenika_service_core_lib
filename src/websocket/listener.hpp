/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef LISTENER_HPP_
#define LISTENER_HPP_

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/smart_ptr.hpp>

#include <memory>
#include <string>


// TODO(serg) remove
namespace net = boost::asio;                    // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace beast = boost::beast;                 // from <boost/beast.hpp>
namespace http = beast::http;                   // from <boost/beast/http.hpp>
namespace websocket = beast::websocket;         // from <boost/beast/websocket.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>

class ICommandDispatcher;
class RequestHandler;

// Accepts incoming connections and launches the sessions
class listener : public boost::enable_shared_from_this<listener> {
    net::io_context& ioc_;
    ssl::context& ctx_;
    tcp::acceptor acceptor_;
    boost::shared_ptr<RequestHandler> requestHandler_;

    void fail(beast::error_code ec, char const* what);
    void on_accept(beast::error_code ec, tcp::socket socket);
    void do_accept();

 public:
    listener(
        std::string host,
        std::uint16_t port,
        net::io_context& ioc,
        ssl::context& ctx,
        boost::shared_ptr<ICommandDispatcher> commandDispatcher);

    // Start accepting incoming connections
    void run();
};

#endif  // LISTENER_HPP_

