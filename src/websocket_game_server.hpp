#ifndef ML_WEBSOCKET_GAME_SERVER_HPP
#define ML_WEBSOCKET_GAME_SERVER_HPP

#include <cstdint>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "websocket_server.hpp"
#include "lobby_server.hpp"
#include "game_event.hpp"
#include "player.hpp"
#include "user.hpp"
#include "random_util.hpp"

struct lobby_server;

void handle_game_message(
    websocketpp::server<websocketpp::config::asio>* srv,
    websocketpp::connection_hdl hdl,
    websocketpp::server<websocketpp::config::asio>::message_ptr msg
);
int start_game_server(const std::uint16_t port);

void on_game_chat(
    websocketpp::server<websocketpp::config::asio>* srv,
    websocketpp::connection_hdl hdl,
    websocketpp::server<websocketpp::config::asio>::message_ptr msg,
    const std::string& chat_msg
);

void on_game_sync(
    websocketpp::server<websocketpp::config::asio>* srv,
    websocketpp::connection_hdl hdl,
    websocketpp::server<websocketpp::config::asio>::message_ptr msg,
    const std::string& login_token
);

#endif
