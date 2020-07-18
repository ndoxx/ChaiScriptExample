#include "scene.h"
#include "components.h"
#include "glm_bindings.h"
#include <chaiscript/chaiscript.hpp>
#include <glm/gtx/string_cast.hpp>

struct RemovedTag{};

Scene::Scene()
{
    // Initialize ChaiScript context (VM) with application bindings
    chai_.add_bindings(script::make_glm_bindings());
    chai_.add_bindings(script::make_bindings<CTransform>());
    chai_.add_bindings(script::make_bindings<CRigid>());
    chai_.add_bindings(script::make_bindings<Scene>());
    chai_->add_global(chaiscript::var(std::ref(*this)), "Scene");

    // "Load" scene

    for(size_t ii = 0; ii < 16; ++ii)
    {
        auto e = registry_.create();

        registry_.emplace<CTransform>(e, 0.f, 0.f);
        auto& cr = registry_.emplace<CRigid>(e);
        auto& cs = registry_.emplace<CScript>(e);

        cs.source = "../source/ballistics.chai";
        chai_->use(cs.source);
    }

    // Setup history
    registry_.view<CTransform, CRigid>().each([this](auto e, const auto& ct, auto& cr) {
        history_[size_t(e)] = {{0.f, cr.acceleration, cr.speed, ct.position}};
    });
}

CTransform& Scene::get_transform(entt::entity e) { return registry_.get<CTransform>(e); }
CRigid& Scene::get_rigid(entt::entity e) { return registry_.get<CRigid>(e); }

// Example of an entity system that handles script components
void Scene::update(float dt)
{
    t_ += dt;
    registry_.view<CScript, CTransform, CRigid>(/*entt::exclude<RemovedTag>*/)
        .each([this, dt](auto e, const auto& /*cs*/, auto& ct, auto& cr) {
            if(registry_.has<RemovedTag>(e)) // entt::exclude does not seem to work here
                return;

            // call script method
            auto func = chai_->eval<std::function<void(entt::entity, float)>>("update");
            func(e, dt);

            // stop simulating entity if it went below y=0
            if(ct.position.y < 0.f)
                registry_.emplace<RemovedTag>(e);

            // save entity data point
            history_[size_t(e)].push_back({t_, cr.acceleration, cr.speed, ct.position});
        });
}

namespace script
{
template <> std::shared_ptr<chaiscript::Module> make_bindings<Scene>()
{
    auto module = std::make_shared<chaiscript::Module>();

    ADD_CLASS(Scene);
    ADD_FUN(Scene, get_transform);
    ADD_FUN(Scene, get_rigid);

    // ECS bindings
    module->add(chaiscript::user_type<entt::entity>(), "EntityID");

    return module;
}
} // namespace script