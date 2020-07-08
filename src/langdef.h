#ifndef XDR_LANGDEF_H
#define XDR_LANGDEF_H

#include "Test.h"
#include "Variant.h"
#include <string>
#include <unordered_map>

#define SECONDS(x) x
#define MINUTES(x) (x * SECONDS(60))
#define HOURS(x) (x * MINUTES(60))
#define DAYS(x) (x * HOURS(24))
#define WEEKS(x) (x * DAYS(7))
#define MONTHS(x) (x * WEEKS(4))
#define YEARS(x) (x * MONTHS(12))

#define BEGIN namespace abtest {
#define END public: \
    int operator[](presets p) { return static_cast<int>(p); }   \
    presets operator[](int p) { return static_cast<presets>(p); }   \
    xdr::Variant operator()(presets p)  \
    {   \
        if(this->variants.find(p) == this->variants.end())  \
            return {};  \
\
        return this->variants[p];   \
    }   \
};}

#define CREATE_TEST(x) class x : public xdr::Test<> { public: x() : xdr::Test<>(#x) {
#define CREATE_TEST_AND_USE_COMPARATOR(x, cmp) class x : public xdr::Test<cmp> { public: x() : xdr::Test<cmp>(#x) {
#define WITH_MIN_VERSION(x) setMinVersion(#x);
#define WITH_MAX_VERSION(x) setMaxVersion(#x);
#define STARTING_FROM_TIMESTAMP(x) setExpirationTime(getExpirationTime() + (x));
#define THAT_EXPIRES_IN(x) setExpirationTime(getExpirationTime() + (x));
#define AS }
#define WITH_PRESETS(...) public: enum class presets { __VA_ARGS__ };
#define WHERE private: std::unordered_map<presets, xdr::Variant> variants = {
#define NOTHING_IS_MAPPED
#define MAP(p, v) { presets::p, xdr::Variant { v } }
#define AND ,
#define END_MAPPING };  
#define INTERFACE public
#define IMPLEMENTATION_DETAILS private

#endif