#ifndef __BRICKSVM_INTERPRETER_PROGRAM_HPP__
# define __BRICKSVM_INTERPRETER_PROGRAM_HPP__

# include <istream>
# include <stack>
# include <vector>
# include <map>
# include <memory>
# include "interpreter/Instruction.hpp"
# include "interpreter/Value.hpp"
# include "interpreter/InstructionResolver.hpp"
# include "core/NewPolicy.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		class Program : public bricksvm::core::NewPolicy<Program>
		{
		public:

			enum State
			{
				ResolveInstruction,
				Execution
			};

			Program();
			~Program();

			void addInstruction(std::shared_ptr<Instruction> const &instruction);

			void addSubProgram(std::string const &progId, std::shared_ptr<Program> const &subProgram);

			std::shared_ptr<Instruction> execute(Value const &retVal);

			void call(std::string const &name);

			void reset();

		private:

			std::shared_ptr<Instruction> resolveInstruction(Value const &retVal);

			void nextInstruction();

			std::shared_ptr<Instruction> getCurrentInstruction();

		private:
			typedef std::map<std::string, std::shared_ptr<Program> >	SubProgramContainerType;
			typedef std::vector<std::shared_ptr<Instruction> >			InstructionContainerType;
			typedef std::stack<std::weak_ptr<Program> >					StackCallContainerType;
			
			SubProgramContainerType					_subPrograms;
			InstructionContainerType				_instructions;
			StackCallContainerType					_calls;
			unsigned int							_currentIndex;
			State									_state;
			std::shared_ptr<InstructionResolver>	_resolver;
			
			static const int						_maxStackSize = 100000000;
			
		};
	}
}

#endif