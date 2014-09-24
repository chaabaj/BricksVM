#include "interpreter/Program.hpp"
#include "exception/InvalidInstructionException.hpp"
#include "exception/StackOverflowException.hpp"

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
                if (_resolver->isResolved())
                {
                    _state = Execution;
                    _resolver = nullptr;
                    return this->execute(retVal);
                }
                _resolver->setResolvedValue(retVal);
                return _resolver->resolve();
            }
            return currentInstruction;
        }
    }
}
