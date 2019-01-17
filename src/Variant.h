#ifndef XDR_VARIANT_H
#define XDR_VARIANT_H

#include <string>
#include <cstddef>
#include <cstdint>

namespace xdr
{

class Variant
{
public:
    enum class Type : char
    {
        STRING, DOUBLE, INT, INT64, BOOL, VOID
    };

public:
    Variant() : type(Type::VOID) { }
    explicit Variant(const std::string& s) { *this = s; }
    explicit Variant(double d) { *this = d; }
    explicit Variant(int i) { *this = i; }
    explicit Variant(int64_t i64) { *this = i64; }
    explicit Variant(bool b) { *this = b; }

    Variant(const Variant&) = default;
    Variant(Variant&&) = default;
    ~Variant() = default;

    Variant& operator=(const Variant&) = default;
    Variant& operator=(Variant&&) = default;

public:
    inline Variant& operator=(const std::string& s);
    inline Variant& operator=(double d);
    inline Variant& operator=(int i);
    inline Variant& operator=(int64_t i64);
    inline Variant& operator=(bool b);
    inline Variant& operator=(std::nullptr_t);

    explicit operator bool() const { return this->type != Type::VOID; }

    template<typename T>
    T as() const;

private:
    std::string s;
    double d;
    int i;
    int64_t i64;
    bool b;

    Type type = Type::VOID;
};

inline Variant& Variant::operator=(const std::string& s)
{
    this->s = s;
    this->type = Type::STRING;

    return *this;
}

inline Variant& Variant::operator=(double d)
{
    this->d = d;
    this->type = Type::DOUBLE;

    return *this;
}

inline Variant& Variant::operator=(int i)
{
    this->i = i;
    this->type = Type::INT;

    return *this;
}

inline Variant& Variant::operator=(int64_t i64)
{
    this->i64 = i64;
    this->type = Type::INT64;

    return *this;
}

inline Variant& Variant::operator=(bool b)
{
    this->b = b;
    this->type = Type::BOOL;

    return *this;
}

inline Variant& Variant::operator=(std::nullptr_t)
{
    this->type = Type::VOID;

    return *this;
}

template<>
inline std::string Variant::as<std::string>() const
{
    return this->s;
}

template<>
inline double Variant::as<double>() const
{
    return this->d;
}

template<>
inline int Variant::as<int>() const
{
    return this->i;
}

template<>
inline int64_t Variant::as<int64_t>() const
{
    return this->i64;
}

template<>
inline bool Variant::as<bool>() const
{
    return this->b;
}

}

#endif