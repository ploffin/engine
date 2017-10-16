#include "game.hpp"

game::game(const std::uint16_t port, map* m)
: port(port)
, m(m)
, max_points(3)
, max_length(15*60)
, world(nullptr)
{
    world = m->init_world();

    std::thread phys_thread(
        &game::run_physics,
        this
    );
    phys_thread.detach();
}

void game::run_physics()
{
    while(true) {
        // std::cout << "." << std::flush;
        // world->Step(1/60.0, 8, 3);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void to_json(nlohmann::json& j, const game& p)
{
    // todo
    // we want score and time remaining here as well
    j = nlohmann::json{
        {"port",         p.port},
        {"max_points",   p.max_points},
        {"max_length",   p.max_length},
        {"map_name",     p.m->name},
        {"map_author",   p.m->author},
        {"player_count", p.m->balls.size()}
    };
}