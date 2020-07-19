#pragma once

#include "script_engine.h"
#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <map>
#include <vector>

namespace script
{
struct ChaiContext;
}

struct CTransform;
struct CRigid;

struct DataPoint
{
    float t;
    glm::vec2 a;
    glm::vec2 v;
    glm::vec2 r;
};

class Scene
{
public:
    Scene();

    CTransform& get_transform(int e);
    CRigid& get_rigid(int e);

    inline entt::registry& get_registry() { return registry_; }

    void update(float dt);

    inline const auto& get_history() { return history_; }

private:
    entt::registry registry_;
    script::ChaiContext chai_;

    std::map<size_t, std::vector<DataPoint>> history_;
    float t_ = 0.f;
};

namespace script
{
template <> std::shared_ptr<chaiscript::Module> make_bindings<Scene>();
}