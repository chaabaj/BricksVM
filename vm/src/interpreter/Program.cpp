#include "interpreter/Program.hpp"
#include "exception/InvalidInstructionException.hpp"
#include "exception/StackOverflowException.hpp"

#include "interpreter/ValueParameter.hpp"
#include "interpreter/InstructionParameter.hpp"

namespace bricksvm
{
    namespace interpreter
    {
        Program::Program() : _currentIndex(0), _state(Execution)
        {

        }

        Program::~Program()
        {

        }

        void Program::addInstruction(std::shared_ptr<Instruction> const &instruction)
        {
            _instructions.push_back(instruction);
        }

        void Program::jump(unsigned int index)
        {
            if (index >= _instructions.size())
            {
                throw std::out_of_range("Jump is out of range");
            }
            _currentIndex = index;
        }

        void Program::reset()
        {
            _currentIndex = 0;
        }

        std::shared_ptr<Instruction> Program::resolveInstruction(Value const &retVal)
        {
            return _resolver->resolve();
        }

        void Program::next()
        {
            ++_currentIndex;
        }

        std::shared_ptr<Instruction> Program::getCurrentInstruction() const
        {
            if (_currentIndex < _instructions.size())
            {
                return _instructions[_currentIndex];
            }
            return std::shared_ptr<Instruction>();
        }

		std::shared_ptr<Instruction> Program::execute(Value const &retVal)
		{
			std::shared_ptr<Instruction>	currentInstruction = this->getCurrentInstruction();

			if (_state == Execution
				&& currentInstruction
				&& !currentInstruction->parametersIsResolved())
			{
				_resolver = std::shared_ptr<InstructionResolver>(new InstructionResolver(currentInstruction->clone()));
				_state = ResolveInstruction;
				return _resolver->resolve();
			}
			else if (_state == ResolveInstruction)
			{
                _resolver->setResolvedValue(retVal);
				if (_resolver->isResolved())
				{
                    currentInstruction = _resolver->getResolvedInstruction();
                    this->next();
					_state = Execution;
					_resolver = nullptr;
                    return currentInstruction;
				}
				return _resolver->resolve();
			}
            else
            {
                this->next();
            }
			return currentInstruction;
		}

		/* DEBUG */
		void Program::dumpProgram()
		{
			int i = 0;
			while (i < this->_instructions.size())
			{
				dumpFunction(this->_instructions[i]);
				++i;
			}
		}

		void Program::dumpFunction(std::shared_ptr<Instruction> instr, int depth)
		{
			for (int f = depth; f > 0; --f)
			{
				std::cout << "\t";
			}
			std::cout << "INSTRUCTION:  " << instr->getName() << "()" << std::endl;
			int i = 0;

			while (i < instr->getParameters().size())
			{
				if (instr->getParameters()[i]->getType() == AParameter::Type::ValueType)
				{
					std::shared_ptr<interpreter::ValueParameter> ram = std::static_pointer_cast<interpreter::ValueParameter>(instr->getParameters()[i]);
					std::cout << "\t Float:" << ram->getValue().as<float>() << " and Int:" << ram->getValue().as<int>() << std::endl;
				}
				else
				{
					std::shared_ptr<interpreter::InstructionParameter> ram = std::static_pointer_cast<interpreter::InstructionParameter>(instr->getParameters()[i]);
					this->dumpFunction(ram->getInstruction(), depth + 1);
				}
				++i;
			}
		}
    }
}
