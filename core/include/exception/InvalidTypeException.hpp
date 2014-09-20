#ifndef __BRICKSVM_CORE_INVALIDTYPEEXCEPTION_HPP__
# define __BRICKSVM_CORE_INVALIDTYPEEXCEPTION_HPP__

# include <stdexcept>
# include "core/DllExport.hpp"

namespace bricksvm
{
    namespace exception
    {
        class EXPORT_DLL InvalidTypeException : public std::runtime_error
        {
        public:
            InvalidTypeException(std::string const &error) throw();
            ~InvalidTypeException();

        };
    }
}

#endif