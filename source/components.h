#pragma once

#include "script_engine.h"
#include <glm/glm.hpp>
#include <string>

struct CTransform
{
    CTransform() = default;
    CTransform(float x, float y) : position(x, y) {}

    void reset();

    glm::vec2 position = {0.f, 0.f};
};

struct CRigid
{
    CRigid() = default;
    CRigid(float vx, float vy) : acceleration(0.f), speed(vx, vy) {}

    glm::vec2 acceleration = {0.f, 0.f};
    glm::vec2 speed = {0.f, 0.f};
};

struct CScript
{
    std::string source;
};

namespace script
{
template <> std::shared_ptr<chaiscript::Module> make_bindings<CTransform>();
template <> std::shared_ptr<chaiscript::Module> make_bindings<CRigid>();
} // namespace script