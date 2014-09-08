#ifndef __BRICKSVM_INTERPRETER_PROGRAM_HPP__
# define __BRICKSVM_INTERPRETER_PROGRAM_HPP__

# include <istream>
# include <stack>
# include <vector>
# include <map>
# include <memory>
# include "interpreter/Instruction.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		class Program
		{
		public:

			enum State
			{
				
			};

			Program();
			~Program();

			void addInstruction(std::shared_ptr<Instruction> const &instruction);

			void addSubProgram(std::string const &progId, std::shared_ptr<Program> const &subProgram);

			std::shared_ptr<Instruction>	nextInstruction();

			void call(std::string const &name);

			void reset();
		private:
			typedef std::map<std::string, std::shared_ptr<Program> >	SubProgramContainerType;
			typedef std::vector<std::shared_ptr<Instruction> >			InstructionContainerType;
			typedef std::stack<std::weak_ptr<Program> >					StackCallContainerType;
			
			SubProgramContainerType		_subPrograms;
			InstructionContainerType	_instructions;
			StackCallContainerType		_calls;
			unsigned int				_currentIndex;
			
		};
	}
}

#endif