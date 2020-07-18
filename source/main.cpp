#include <array>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <type_traits>
#include <vector>
#include <fstream>

#include "scene.h"
#include "components.h"

int main()
{
    std::cout << "Running simulation." << std::endl;

    Scene scene;

    float dt = 0.05f;
    float initial_a = 50.f;
    float accel_phase = 1.f;
    float total_duration = 10.f;

    float t = 0.f;

    size_t num_ent = scene.get_registry().size();
    float alpha = glm::radians(15.f);

    scene.get_registry().view<CRigid>().each([&alpha,initial_a](auto, auto& cr)
    {
        glm::vec2 dir = {cos(alpha), sin(alpha)};
        cr.acceleration = initial_a*dir;
        alpha += glm::radians(5.f);
    });

    for(int ii = 0; t < accel_phase; ++ii)
    {
        scene.update(dt);
        t += dt;
    }

    // stop accelerating after 10 frames
    scene.get_registry().view<CRigid>().each([](auto, auto& cr) { cr.acceleration = {0.f, 0.f}; });

    for(int ii = 0; t < total_duration; ++ii)
    {
        scene.update(dt);
        t += dt;
    }

    std::cout << "Done." << std::endl;

    // Export data
    std::cout << "Saving data." << std::endl;

    const auto& history = scene.get_history();

    std::ofstream ofs("data.json");
    ofs << "{\n";
    ofs << "\"dt\": " << dt << ",\n";
    ofs << "\"entities\": [\n";

    size_t cur_ent = 0;
    for(auto&& [e, points]: history)
    {
        ofs << "{\n";
        ofs << "\"index\": " << e << ",\n";
        ofs << "\"position\": [\n";
        size_t cur_pt = 0;
        for(const auto& data: points)
        {
            ofs << "[" << data.r.x << "," << data.r.y << "]";

            if(cur_pt < points.size()-1)
                ofs << ",";
            ++cur_pt;
        }
        ofs << "\n]\n}";

        if(cur_ent < history.size()-1)
            ofs << ",";
        ofs << "\n";
        ++cur_ent;
    }

    ofs << "]\n}" << std::endl;
    ofs.close();

    std::cout << "Done." << std::endl;
    return 0;
}
