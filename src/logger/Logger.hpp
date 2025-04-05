#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace std
{

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
    
    template <typename T>
    Logger& operator<<(T obj)
    {
        os << obj << '\n';
        return *this;
    }


private:
    Tos &os;
};

extern Logger<std::ostream> dbg;