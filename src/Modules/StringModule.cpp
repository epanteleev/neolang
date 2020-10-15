#include <Vm/Allocator/RootSet.h>
#include "Modules/StringModule.h"

#include "Vm/Vm.h"

VmResult StringModule::concat(Vm &vm) noexcept {
    ObjStringViewer viewer0(vm.load(0));
    ObjStringViewer viewer1(vm.load(1));
    Value res = (viewer0 + viewer1).toValueAndRelease();
    RootSet::set().addRoot(res);
    vm.stack().push(res);
    return VmResult::SUCCESS;
}
