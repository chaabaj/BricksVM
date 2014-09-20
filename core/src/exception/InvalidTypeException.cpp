#include "exception/InvalidTypeException.hpp"

namespace bricksvm
{
    namespace exception
    {
        InvalidTypeException::InvalidTypeException(std::string const &error) : std::runtime_error(error)
        {

        }

        InvalidTypeException::~InvalidTypeException()
        {

        }
    }
}