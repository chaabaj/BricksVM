#ifndef __BRICKSVM_CORE_CONSOLE_HPP__
# define __BRICKSVM_CORE_CONSOLE_HPP__

# include <type_traits>
# include "core/constants.hpp"

namespace bricksvm
{
    namespace core
    {
        class WinConsole;
        class UnixConsole;
    }
}

# ifdef WIN32 
#  include "core/WinConsole.hpp"
# elif
#  include "core/UnixConsole.hpp"
# endif

namespace bricksvm
{
    namespace core
    {
        typedef std::conditional<WINDOWS, WinConsole, UnixConsole>::type   Console;
    }
}

#endif