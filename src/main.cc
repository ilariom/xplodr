#include <xplodr.h>
#include <iostream>

int main()
{
    xdr::TestManager& tm = xdr::TestManager::getInstance();
    tm += std::make_shared<abtests::Example>();
    tm += std::make_shared<abtests::ComplexExample>();

    xdr::Variant v = tm.ask<abtests::ComplexExample>(abtests::ComplexExample::presets::ROYAL);
    std::cout << v.as<bool>() << std::endl;
}