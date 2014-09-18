#include "exception/FileNotFoundException.hpp"

namespace bricksvm
{
	namespace exception
	{
		FileNotFoundException::FileNotFoundException(std::string const &error) : std::runtime_error(error)
		{

		}

		FileNotFoundException::~FileNotFoundException()
		{

		}
	}
}