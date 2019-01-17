#ifndef XDR_TEST_MANAGER_H
#define XDR_TEST_MANAGER_H

#include "Test.h"
#include <unordered_map>
#include <memory>

namespace xdr
{

class TestManager
{
public:
    inline static TestManager& getInstance();

    TestManager(const TestManager&) = delete;
    TestManager(TestManager&&) = delete;

    TestManager& operator=(const TestManager&) = delete;
    TestManager& operator=(TestManager&&) = delete;

public:
    template<typename T = std::less<std::string>>
    inline void operator+=(std::shared_ptr<T> test);

    template<typename TestType>
    inline std::shared_ptr<TestType> query();

private:
    TestManager() = default;
    ~TestManager() = default;

private:
    std::unordered_map<std::string, std::shared_ptr<TestBase>> tests;
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

}

#endif