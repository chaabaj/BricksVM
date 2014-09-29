#include "exception/InvalidOperationException.hpp"

namespace bricksvm
{
    namespace exception
    {
        InvalidOperationException::InvalidOperationException(std::string const &error) throw() : std::runtime_error(error)
        {

        }

        InvalidOperationException::~InvalidOperationException()
        {

        }
    }
}
