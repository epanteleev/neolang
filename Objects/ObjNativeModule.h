#pragma once
#include <list>

#include "Objects/Object.h"
#include "Objects/ObjNativeMethod.h"

class ObjNativeModule : public Object {
public:
    explicit ObjNativeModule(const std::string &className) :
            Object(className) {}

    ~ObjNativeModule() override = default;

    inline void addMethod(std::unique_ptr<ObjNativeMethod> &method) noexcept {
        m_methods.push_back(std::move(method));
    }

    [[nodiscard]]
    inline ObjNativeMethod* findMethod(const std::string &name) const noexcept {
        auto pred = [&](const std::unique_ptr<ObjNativeMethod> &i) { return (*i).methodName() == name; };
        return std::find_if(m_methods.begin(), m_methods.end(), pred)->get();
    }

    [[nodiscard]]
    inline const std::string &moduleName() const noexcept {
        return objectName();
    }

private:
    std::list<std::unique_ptr<ObjNativeMethod>> m_methods{};
};

class NativeModuleBuffer final {
public:
    NativeModuleBuffer() = default;
    NativeModuleBuffer(NativeModuleBuffer&) = delete;

    ~NativeModuleBuffer() = default;

    ObjNativeMethod* findMethod(const std::string& moduleName, const std::string& name) noexcept {
        const auto module = findModule(moduleName);
        if (module != nullptr) {
            return module->findMethod(name);
        } else {
            return nullptr;
        }
    }

    ObjNativeModule* findModule(const std::string& moduleName) noexcept {
        auto pred = [&](const std::unique_ptr<ObjNativeModule> &i) { return (*i).moduleName() == moduleName; };
        const auto module = std::find_if(m_methods.begin(), m_methods.end(), pred);
        if (module != m_methods.end()) {
            return module->get();
        } else {
            return nullptr;
        }
    }

    inline void addModule(std::unique_ptr<ObjNativeModule> &module) noexcept {
        m_methods.push_back(std::move(module));
    }

private:
    std::list<std::unique_ptr<ObjNativeModule>> m_methods;
};