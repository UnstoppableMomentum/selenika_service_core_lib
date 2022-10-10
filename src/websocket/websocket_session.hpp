/////////////////////////////////
//                             //
// Copyright (c) 2022 Selenika //
//                             //
/////////////////////////////////

#ifndef WEBSOCKET_SESSION_HPP_
#define WEBSOCKET_SESSION_HPP_

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>
#include <utility>

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>


// TODO(serg) remove
namespace net = boost::asio;                    // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace beast = boost::beast;                 // from <boost/beast.hpp>
namespace http = beast::http;                   // from <boost/beast/http.hpp>
namespace websocket = beast::websocket;         // from <boost/beast/websocket.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>

class RequestHandler;

/** Represents an active WebSocket connection to the server
*/
class websocket_session : public
    boost::enable_shared_from_this<websocket_session> {
    beast::flat_buffer buffer_;
    websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws_;
    boost::shared_ptr<RequestHandler> requestHandler_;
    std::vector<boost::shared_ptr<std::string const>> queue_;

    void fail(beast::error_code ec, char const* what);
    void on_accept(beast::error_code ec);
    void on_read(beast::error_code ec, std::size_t bytes_transferred);
    void on_write(beast::error_code ec, std::size_t bytes_transferred);

 public:
    websocket_session(
        tcp::socket&& socket,
        ssl::context& ctx,
        boost::shared_ptr<RequestHandler> const& requestHandler);

    ~websocket_session();

    template<class Body, class Allocator>
    void run(http::request<Body, http::basic_fields<Allocator>> req);
    void run();
    void on_run();
    void on_handshake(beast::error_code ec);

    // Send a message
    void send(boost::shared_ptr<std::string const> const& ss);
    void setId(const std::string& id) { id_ = std::move(id); }
    const std::string& getId() const { return id_; }
 private:
    void on_send(boost::shared_ptr<std::string const> const& ss);
    std::string id_;
};

template<class Body, class Allocator>
void websocket_session::run(
    http::request<Body, http::basic_fields<Allocator>> req) {

    // Set the timeout.
    beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));

    // Perform the SSL handshake
    ws_.next_layer().async_handshake(
        ssl::stream_base::server,
        beast::bind_front_handler(
            &websocket_session::on_handshake,
            shared_from_this()));
}

#endif  // WEBSOCKET_SESSION_HPP_

