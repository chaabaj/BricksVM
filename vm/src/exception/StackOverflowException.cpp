#include "exception/StackOverflowException.hpp"

namespace bricksvm
{
    namespace exception
    {
        StackOverflowException::StackOverflowException() throw() : std::runtime_error("Stack overflow")
        {

        }

        StackOverflowException::~StackOverflowException()
        {

        }
    }
}
