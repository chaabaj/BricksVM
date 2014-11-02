#ifndef __BRICKSVM_CORE_STRING_HPP__
# define __BRICKSVM_CORE_STRING_HPP__

# include <string>
# include <cstdint>
# include "core/DllExport.hpp"

namespace bricksvm
{
    namespace core
    {
        enum MemorySize
        {
            KB = 1000,
            MB = KB * 1000,
            GB = MB * 1000
        };

        EXPORT_DLL uint64_t  getMemSize(std::string const &str);
    }
}

#endif