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
        class Program : public bricksvm::core::NewPolicy < Program >
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

            std::shared_ptr<Instruction> execute(Value const &retVal);

            void next();

            void jump(unsigned int index);

            void reset();

        private:

            std::shared_ptr<Instruction> resolveInstruction(Value const &retVal);

            std::shared_ptr<Instruction> getCurrentInstruction() const;

        private:
            typedef std::vector<std::shared_ptr<Instruction> >			InstructionContainerType;

            InstructionContainerType                _instructions;
            unsigned int                            _currentIndex;
            State                                   _state;
            std::shared_ptr<InstructionResolver>    _resolver;

			/* DEBUT */
		public:
			void dumpProgram();
			void dumpFunction(std::shared_ptr<Instruction> instr);

        };
    }
}

#endif