#ifndef XDR_LANGDEF_H
#define XDR_LANGDEF_H

#include "Test.h"
#include "Variant.h"
#include <string>
#include <unordered_map>

#define BEGIN namespace abtests {
#define END public: \
    int operator[](presets p) { return static_cast<int>(p); }   \
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