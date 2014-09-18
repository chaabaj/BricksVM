#include "exception/InvalidInstructionException.hpp"

namespace bricksvm
{
	namespace exception
	{
		InvalidInstructionException::InvalidInstructionException(std::string const &error) : std::runtime_error(error)
		{

		}

		InvalidInstructionException::~InvalidInstructionException()
		{

		}
	}
}