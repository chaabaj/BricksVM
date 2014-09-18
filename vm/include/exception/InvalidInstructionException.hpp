#ifndef __BRICKSVM_EXCEPTION_INVALIDINSTRUCTIONEXCEPTION_HPP__
# define __BRICKSVM_EXCEPTION_INVALIDINSTRUCTIONEXCEPTION_HPP_

# include <stdexcept>

namespace bricksvm
{
	namespace exception
	{
		class InvalidInstructionException : public std::runtime_error
		{
		public:
			InvalidInstructionException(std::string const &error) throw();
			~InvalidInstructionException();
		};
	}
}

#endif