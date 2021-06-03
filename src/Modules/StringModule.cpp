#include <Vm/Allocator/RootSet.h>
#include "Modules/StringModule.h"

#include "Vm/Vm.h"

VmResult StringModule::concat(Environment &env) noexcept {
    ObjStringViewer viewer0(env.locals().load(0));
    ObjStringViewer viewer1(env.locals().load(1));
    Value res = (viewer0 + viewer1).toValueAndRelease();
    RootSet::set().addRoot(res);
    env.stack().push(res);
    return VmResult::SUCCESS;
}
