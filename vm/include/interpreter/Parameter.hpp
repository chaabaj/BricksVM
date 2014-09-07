#ifndef __BRICKSVM_INTERPRETER_PARAMETER_HPP__
# define __BRICKSVM_INTERPRETER_PARAMETER_HPP__

# include "interpreter/Value.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		class IParameter
		{
		public:
			enum Type
			{
				Value,
				Instruction
			};

			~IParameter() {}

		};

		class ValueParameter
		{
		public:
			ValueParameter(Value const &value);
			~ValueParameter();

			Value const	&getValue() const;
		
		private:
			Value const &value;

		};

		class InstructionParameter
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