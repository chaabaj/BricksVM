#ifndef __BRICKSVM_EXCEPTION_INVALIDOPERATION_HPP__
# define __BRICKSVM_EXCEPTION_INVALIDOPERATION_HPP__

# include <stdexcept>
# include <string>
# include "core/DllExport.hpp"

namespace bricksvm
{
    namespace exception
    {
        class EXPORT_DLL InvalidOperationException : public std::runtime_error
        {
        public:
            InvalidOperationException(std::string const &error) throw();
            ~InvalidOperationException();

        };
    }
}

#endif