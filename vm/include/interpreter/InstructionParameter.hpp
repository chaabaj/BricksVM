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
			InstructionParameter(std::shared_ptr<Instruction> &instruction);
			~InstructionParameter();

			std::shared_ptr<Instruction> getInstruction();

			std::shared_ptr<const Instruction> getInstruction() const;

		private:
			std::shared_ptr<Instruction> _instruction;
		};
	}
}

#endif