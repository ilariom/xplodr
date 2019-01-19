#include <xplodr.h>
#include <iostream>

int main()
{
    xdr::TestManager& tm = xdr::TestManager::getInstance();
    tm += std::make_shared<abtests::Example>();

    auto sp = tm.query<abtests::Example>();
    std::cout << (*sp)(abtests::Example::presets::BASIC).as<std::string>() << std::endl;
}