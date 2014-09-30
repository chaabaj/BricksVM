#ifndef __BRICKSVM_PARSER_PARSER_HPP__
# define __BRICKSVM_PARSER_PARSER_HPP__

# include <memory>
# include "interpreter/Program.hpp"

namespace bricksvm
{
	namespace parser
	{
		class Parser
		{
		public:
			Parser();
			std::shared_ptr<interpreter::Program> generateProgramFromFile(std::string const &fileName);
		};
	}
}

#endif