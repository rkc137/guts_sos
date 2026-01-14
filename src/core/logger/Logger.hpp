#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace std
{

inline ostream& operator<<(ostream& os, const sf::String& str)
{
    os << str.toAnsiString();
    return os;
}

template <typename T>
ostream& operator<<(ostream &os, sf::Vector2<T> vec)
{
    os << '{' << vec.x << ':' << vec.y << '}';
    return os;
}

}

template <typename Tos>
class Logger
{
public:
    Logger(Tos& os) : os(os)
    {
        os << "\n";
    }

    class Proxy
    {
    public:
        Proxy(Tos& os) : os(os) {}
        ~Proxy()
        {
            os << '\n';
        }

        template <typename T>
        Proxy& operator<<(const T& obj)
        {
            os << obj << ' ';
            first = false;
            return *this;
        }

    private:
        Tos& os;
        bool first = true;
    };

    Proxy operator<<(std::ostream& (*pf)(std::ostream&))
    {
        os << pf;
        return Proxy(os);
    }

    Proxy start()
    {
        return Proxy(os);
    }

private:
    Tos &os;
};

Logger<std::ostream>::Proxy dbg();