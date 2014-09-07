#ifndef __BRICKSVM_INTERPRETER_PROGRAM_HPP__
# define __BRICKSVM_INTERPRETER_PROGRAM_HPP__

# include "interpreter/Instruction.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		class Program
		{
		public:
			
			

		private:

			std::unique_ptr<Instruction>	_instruction;

		};
	}
}

#endif