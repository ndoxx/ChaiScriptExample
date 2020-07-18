#include "components.h"
#include <chaiscript/chaiscript.hpp>

void CTransform::reset() { position = {0.f, 0.f}; }

namespace script
{
template <> std::shared_ptr<chaiscript::Module> make_bindings<CTransform>()
{
    auto module = std::make_shared<chaiscript::Module>();

    ADD_CLASS(CTransform);
    ADD_FUN(CTransform, reset);
    ADD_FUN(CTransform, position);

    return module;
}

template <> std::shared_ptr<chaiscript::Module> make_bindings<CRigid>()
{
    auto module = std::make_shared<chaiscript::Module>();

    ADD_CLASS(CRigid);
    ADD_FUN(CRigid, acceleration);
    ADD_FUN(CRigid, speed);

    return module;
}
} // namespace script