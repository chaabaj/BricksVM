#ifndef __BRICKSVM_EXCEPTION_STACKOVERFLOW_HPP__
# define __BRICKSVM_EXCEPTION_STACKOVERFLOW_HPP__

# include <stdexcept>

namespace bricksvm
{
	namespace exception
	{
		class StackOverflowException : public std::runtime_error
		{
		public:
			StackOverflowException() throw();
			~StackOverflowException();
		};
	}
}

#endif