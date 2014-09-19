#include "exception/StackOverflowException.hpp"

namespace bricksvm
{
	namespace exception
	{
		StackOverflowException::StackOverflowException() : std::runtime_error("Stack overflow")
		{

		}

		StackOverflowException::~StackOverflowException()
		{

		}
	}
}