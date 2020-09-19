#include "ModuleBuffer.h"

ObjMethodBase *ModuleBuffer::findMethod(const std::string &moduleName, const std::string &name) noexcept {
    const auto module = findModule(moduleName);
    if (module != nullptr) {
        return (*module).findMethod(name);
    } else {
        return nullptr;
    }
}

ObjModuleBase *ModuleBuffer::findModule(const std::string &moduleName) noexcept {
    auto pred = [&](const std::unique_ptr<ObjModuleBase> &i) { return (*i).moduleName() == moduleName; };
    const auto module = std::find_if(m_modules.begin(), m_modules.end(), pred);
    if (module != m_modules.end()) {
        return module->get();
    } else {
        return nullptr;
    }
}