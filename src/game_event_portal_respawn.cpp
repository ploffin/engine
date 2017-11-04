#include "game_event_portal_respawn.hpp"

game_event_portal_respawn::game_event_portal_respawn(
    const std::size_t id,
    const b2Vec2 pos
)
: id(id)
, pos(pos)
{}

void to_json(nlohmann::json& j, const game_event_portal_respawn& p)
{
    j = nlohmann::json{
        {"id", p.id},
        {"px", p.pos.x},
        {"py", p.pos.y}
    };
}