#include "exception/FileNotFoundException.hpp"

namespace bricksvm
{
    namespace exception
    {
        FileNotFoundException::FileNotFoundException(std::string const &error) throw() : std::runtime_error(error)
        {

        }

        FileNotFoundException::~FileNotFoundException()
        {

        }
    }
}
