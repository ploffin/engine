#ifndef ML_GAME_EVENT_PLAYER_JOINED_HPP
#define ML_GAME_EVENT_PLAYER_JOINED_HPP

#include <string>
#include <json/json_fwd.hpp>
#include "player.hpp"

struct game_event_player_joined
{
    player* p;

    game_event_player_joined(player* p);
};

void to_json(nlohmann::json& j, const game_event_player_joined& p);

#endif

