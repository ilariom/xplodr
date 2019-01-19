#ifndef XDR_TEST_H
#define XDR_TEST_H

#include <string>

namespace xdr
{

struct TestBase { };

template<typename VersionComp = std::less<std::string>>
class Test : public TestBase
{
public:
    Test(const std::string& name, const std::string& minVer, const std::string& maxVer) : name(name), minVer(minVer), maxVer(maxVer) { }
    explicit Test(const std::string& name) : Test(name, "", "") { }

public:
    const std::string& getName() const { return this->name; }
    const std::string& getMinVersion() const { return this->minVer; }
    const std::string& getMaxVersion() const { return this->maxVer; }

    inline bool isActiveForVersion(const std::string&);

protected:
    void setMinVersion(const std::string& minVer) { this->minVer = minVer; }
    void setMaxVersion(const std::string& maxVer) { this->maxVer = maxVer; }

private:
    std::string name;
    std::string minVer;
    std::string maxVer;
};

template<typename VC>
inline bool Test<VC>::isActiveForVersion(const std::string& v)
{
    return VC()(getMinVersion(), v) && VC()(v, getMaxVersion());
}

} // xdr

#endif