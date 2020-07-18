#include "script_engine.h"
#include <chaiscript/chaiscript.hpp>

namespace script
{

ChaiContext::ChaiContext() { vm = std::make_shared<chaiscript::ChaiScript>(); }

void ChaiContext::add_bindings(std::shared_ptr<chaiscript::Module> module) { vm->add(module); }

} // namespace script