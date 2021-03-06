#include "websocket_server.hpp"
#include "websocket_lobby_server.hpp"
#include <json/json.hpp>

int start_lobby_server(
    lobby_server& lobby,
    const std::uint16_t port
) {
    spdlog::get("game")->info("starting tagos lobby server on port: {0:d}", port);
    websocketpp_server srv;

    try {
        srv.set_reuse_addr(true);

        srv.clear_access_channels(websocketpp::log::alevel::all);
        srv.set_access_channels(websocketpp::log::elevel::info);

        srv.set_open_handler(bind(&handle_lobby_open, &srv, ::_1));
        srv.set_close_handler(bind(&handle_lobby_close, &srv, ::_1));
        srv.set_fail_handler(bind(&handle_lobby_fail, &srv, ::_1));
        srv.set_ping_handler(bind(&handle_lobby_ping, &srv, ::_1, ::_2));
        srv.set_pong_handler(bind(&handle_lobby_pong, &srv, ::_1, ::_2));
        srv.set_pong_timeout_handler(bind(&handle_lobby_pong_timeout, &srv, ::_1, ::_2));
        srv.set_interrupt_handler(bind(&handle_lobby_interrupt, &srv, ::_1));
        srv.set_validate_handler(bind(&handle_lobby_validate, &srv, ::_1));
        srv.set_message_handler(bind(&handle_lobby_message, &srv, ::_1, ::_2));
        srv.set_http_handler(bind(&handle_lobby_http, &srv, ::_1));

        srv.init_asio();
        srv.listen(port);
        srv.start_accept();
        srv.run();
    } catch (websocketpp::exception const & e) {
        spdlog::get("game")->error("server exception {}", e.what());
        lobby.is_alive = false;
        std::exit(EXIT_FAILURE);
        return 1;
    } catch (...) {
        spdlog::get("game")->error("unknown server exception");
        lobby.is_alive = false;
        std::exit(EXIT_FAILURE);
        return 1;
    }

    return 0;
}

void handle_lobby_open(
    websocketpp_server* srv,
    websocketpp::connection_hdl hdl
) {}

void handle_lobby_close(
    websocketpp_server* srv,
    websocketpp::connection_hdl hdl
) {}

void handle_lobby_fail(
    websocketpp_server* srv,
    websocketpp::connection_hdl hdl
) {}

bool handle_lobby_ping(
    websocketpp_server* srv,
    websocketpp::connection_hdl hdl,
    std::string str
) {
    return true;
}

bool handle_lobby_pong(
    websocketpp_server* srv,
    websocketpp::connection_hdl hdl,
    std::string str
) {
    return true;
}

void handle_lobby_pong_timeout(
    websocketpp_server* srv,
    websocketpp::connection_hdl hdl,
    std::string str
) {}

void handle_lobby_interrupt(
    websocketpp_server* srv,
    websocketpp::connection_hdl hdl
) {}

bool handle_lobby_validate(
    websocketpp_server* srv,
    websocketpp::connection_hdl hdl
) {
    // todo
    // validate if connection is valid/allowed
    
    return true;
}

void handle_lobby_message(
    websocketpp_server* srv,
    websocketpp::connection_hdl hdl,
    websocketpp_server::message_ptr msg
) {
    try {
        nlohmann::json j = nlohmann::json::parse(msg->get_payload());
        // std::cout << j.dump() << std::endl;

        if(j.at("request").get<std::string>() == "games") {
            return on_lobby_request_games(srv, hdl, msg);
        }

    } catch(...) {
        try_send(srv, hdl, websocketpp::frame::opcode::TEXT, {
            {"error", "json_parse_error"}
        });
    }
}

void handle_lobby_http(
    websocketpp_server* srv,
    websocketpp::connection_hdl hdl
) {
    auto con = srv->get_con_from_hdl(hdl);

    const lobby_server& lobby = lobby_server::get_instance();

	con->set_status(websocketpp::http::status_code::ok);
	// con->set_header("Content-Type", "application/json"); // todo - we need to add this
	nlohmann::json j = lobby_event(lobby_event_games(lobby.get_games()));
	con->set_body(j.dump());
}

void on_lobby_request_games(
    websocketpp_server* srv,
    websocketpp::connection_hdl hdl,
    websocketpp_server::message_ptr msg
) {
    const lobby_server& lobby = lobby_server::get_instance();

    try_send(srv, hdl, websocketpp::frame::opcode::TEXT,
        lobby_event(lobby_event_games(lobby.get_games()))
    );
}

