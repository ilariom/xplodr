#ifndef XDR_TEST_MANAGER_H
#define XDR_TEST_MANAGER_H

#include "Test.h"
#include <unordered_map>
#include <functional>
#include <memory>

namespace xdr
{

struct SerializableTest
{
    std::string name;
    int preset;
};

struct Persistor
{
    std::function<void(const SerializableTest&)> serializer = nullptr;
    std::function<void()> deserializer = nullptr;
};

class TestManager
{
public:
    inline static TestManager& getInstance();

    TestManager(const TestManager&) = delete;
    TestManager(TestManager&&) = delete;

    TestManager& operator=(const TestManager&) = delete;
    TestManager& operator=(TestManager&&) = delete;

public:
    template<typename TestType>
    inline void operator+=(std::shared_ptr<TestType> test);

    template<typename TestType>
    inline std::shared_ptr<TestType> query();

    template<typename TestType>
    inline Variant ask();

    template<typename TestType>
    inline Variant ask(typename TestType::presets);

    template<typename TestType>
    inline void assign(typename TestType::presets);

    template<typename TestType>
    inline typename TestType::presets preset();

    void setPersistor(const Persistor& p) { this->persistor = p; }

    inline void load();
    inline void save();

private:
    TestManager() = default;
    ~TestManager() = default;

private:
    std::unordered_map<std::string, std::shared_ptr<TestBase>> tests;
    std::unordered_map<std::string, int> testValues;
    Persistor persistor;
};

inline TestManager& TestManager::getInstance()
{
    static TestManager tm;
    return tm;
}

template<typename T>
inline void TestManager::operator+=(std::shared_ptr<T> test)
{
    this->tests[test->getName()] = test;
}

template<typename TestType>
inline std::shared_ptr<TestType> TestManager::query()
{
    TestType tt;
    return std::static_pointer_cast<TestType>(this->tests[tt.getName()]);
}

template<typename TestType>
inline Variant TestManager::ask(typename TestType::presets p)
{
    auto sp = query<TestType>();

    if (!sp)
        return {};

    return (*sp)(p);
}

template<typename TestType>
inline Variant TestManager::ask()
{
    auto sp = query<TestType>();

    if (!sp)
        return {};

    return ask<TestType>(
        (*sp)[this->testValues[sp->getName()]]
    );
}

template<typename TestType>
inline void TestManager::assign(typename TestType::presets p)
{
    auto sp = query<TestType>();

    if (!sp)
        return;

    this->testValues[sp->getName()] = (*sp)[p];
}

template<typename TestType>
inline typename TestType::presets TestManager::preset()
{
    auto sp = query<TestType>();

    if (!sp)
        return {};

    return (*sp)[this->testValues[sp->getName()]];
}

inline void TestManager::load()
{
    if (this->persistor.deserializer)
        this->persistor.deserializer();
}

inline void TestManager::save()
{
    if (this->persistor.deserializer)
        for (const auto& test : this->tests)
            this->persistor.serializer(SerializableTest {
                test.first,
                this->testValues[test.first]
            });
}

} // namespace xdr

#endif