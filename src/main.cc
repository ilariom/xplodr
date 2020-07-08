#include <xplodr.h>
#include <iostream>
#include <chrono>

int main()
{
    /*
     * AB Tests definitions should be placed in files using the same DSL of examples and added to the tests.h file.
     * After that, use the TestManager and Test interface to choose behaviors based on what your app needs are.
     * All tests are automatically placed under the "abtest" namespace.
     * Randomized assignment and timestamp are not provided by the library as they are already present in std. Also,
     * different projects may have different requirements.
     */

    xdr::TestManager& tm = xdr::TestManager::getInstance();
    xdr::Persistor persistor;

    persistor.deserializer = [&tm] {
        // Builds test instances and attach them to the manager
        tm += xdr::make_test<abtest::Example>();
        tm += xdr::make_test<abtest::ComplexExample>();

        // Queries tests from manager
        auto& ex = *tm.query<abtest::Example>();
        auto& cex = *tm.query<abtest::ComplexExample>();

        // Translates integer serialization to typed presets (0 and 1 are example values)
        // If they are saved somewhere, use them. Otherwise this may be a good place to pick one.
        auto pEx = ex[0];
        auto pCex = cex[1];

        // Assigns presets to instances
        tm.assign<abtest::Example>(pEx);
        tm.assign<abtest::ComplexExample>(pCex);
    };

    persistor.serializer = [] (const xdr::SerializableTest& test) {
        std::cout << "Test name: " << test.name << ", test value: " << test.preset << std::endl;
    };

    tm.setPersistor(persistor);
    tm.load();

    // Gets preset assigned from TestManager
    abtest::ComplexExample::presets preset = tm.preset<abtest::ComplexExample>();

    // Gets the mapping from the previously assigned preset
    xdr::Variant m1 = tm.ask<abtest::ComplexExample>();

    // This is the same as the previous line
    xdr::Variant m2 = tm.ask<abtest::ComplexExample>(preset);

    // Gets the mapping from a specific preset
    xdr::Variant v = tm.ask<abtest::ComplexExample>(abtest::ComplexExample::presets::ROYAL);
    std::cout << v.as<bool>() << std::endl;

    // Retrieves the test instance
    auto& cex = *tm.query<abtest::ComplexExample>();

    // Checks if test is expired. It takes the timestamp for NOW in input
    bool isExpired = cex.isExpired(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
    );

    // Checks if the test is valid for the version in input (is inside the range specified at test definition)
    bool isActive = cex.isActiveForVersion("1.43.0");

    std::cout << isActive << std::endl;

    tm.save();
}