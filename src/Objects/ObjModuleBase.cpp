#include "Objects/ObjModuleBase.h"
#include "Objects/ObjMethodBase.h"
#include "Objects/ObjNativeMethod.h"

ObjMethodBase *ObjModuleBase::findMethod(const ObjString &name) const noexcept {
    auto pred = [&](const std::unique_ptr<ObjMethodBase> &i) { return (*i).methodName() == name; };
    return std::find_if(m_methods.begin(), m_methods.end(), pred)->get();
}