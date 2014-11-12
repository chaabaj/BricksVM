#ifndef __BRICKSVM_CORE_WINCONSOLE_HPP__
# define __BRICKSVM_CORE_WINCONSOLE_HPP__

# include <ostream>
# include <string>
# include "DllExport.hpp"

namespace bricksvm
{
    namespace core
    {
        class EXPORT_DLL WinConsole
        {
        public:
            static std::ostream &success(std::string const &deviceName);
            static std::ostream &log(std::string const &deviceName);
            static std::ostream &error(std::string const &deviceName);
        };
    }
}

#endif