#pragma once

#include "script_engine.h"
#include <memory>

namespace script
{
std::shared_ptr<chaiscript::Module> make_glm_bindings();
}