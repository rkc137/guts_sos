#include "Logger.hpp"

Logger<std::ostream>::Proxy dbg()
{
    return Logger(std::cerr).start();
}