#ifndef __BRICKSVM_EXCEPTION_FILENOTFOUNDEXCEPTION_HPP__
# define __BRICKSVM_EXCEPTION_FILENOTFOUNDEXCEPTION_HPP__

# include <stdexcept>

namespace bricksvm
{
	namespace exception
	{
		class FileNotFoundException : public std::runtime_error
		{
		public:
			FileNotFoundException(std::string const &error) throw();
			~FileNotFoundException() throw();
		};
	}
}

#endif