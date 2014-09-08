#ifndef __BRICKSVM_INTERPRETER_INSTRUCTIONPARAMETER_HPP__
# define __BRICKSVM_INTERPRETER_INSTRUCTIONPARAMETER_HPP__

# include "interpreter/Instruction.hpp"
# include "interpreter/AParameter.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		class InstructionParameter : public AParameter
		{
		public:
			InstructionParameter(Instruction const &instruction);
			~InstructionParameter();

			Instruction const &getInstruction() const;

		private:
			Instruction const	&_instruction;
		};
	}
}

#endif