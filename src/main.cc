#include "Test.h"
#include "Variant.h"
#include "TestManager.h"

struct TestTest : public xdr::Test<>
{ 
    TestTest() : xdr::Test<>("test_test") { }
};

int main()
{
    TestTest tt;
    xdr::Variant v { "hello" };
    std::string s = v.as<std::string>();

    xdr::TestManager& tm = xdr::TestManager::getInstance();
    tm += std::make_shared<TestTest>();

    auto sp = tm.query<TestTest>();

    return 0;
}