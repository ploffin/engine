#ifndef ML_GAME_EVENT_TYPE_HPP
#define ML_GAME_EVENT_TYPE_HPP

#include <spdlog/spdlog.h>
#include <json/json_fwd.hpp>
#include <string>
#include <iostream>

enum class game_event_type
{
    gamesync,
    ballsync,
    player_joined,
    player_left,
    chat,
    teamchat,
    honk,
    ball_respawn,
    ball_popped,
    ball_boosted,
    ball_score,
    ball_portal,
    ball_powerup,
    ball_rb_explode,
    booster_respawn,
    powerup_respawn,
    portal_respawn,
    bomb_respawn,
    bomb_explosion,
    flag_grabbed,
    // flag_transferred, // neutral flag
    toggle_on,
    toggle_off,
    game_finished,
    game_stats,
    vote_player,
};

std::string to_string(const game_event_type m);

#endif

