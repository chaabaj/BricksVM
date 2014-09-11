#include "interpreter/Program.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		Program::Program() : _currentIndex(0)
		{
			
		}

		Program::~Program()
		{

		}
		
		void Program::addInstruction(std::shared_ptr<Instruction> const &instruction)
		{
			_instructions.push_back(instruction);
		}

		void Program::addSubProgram(std::string const &progId, std::shared_ptr<Program> const &subProgram)
		{
			_subPrograms[progId] = subProgram;
		}

		void Program::call(std::string const &name)
		{
			Program::SubProgramContainerType::const_iterator	it;

			if ((it = _subPrograms.find(name)) == _subPrograms.end())
			{
				throw std::runtime_error("No such label : " + name);
			}
			_calls.push(std::weak_ptr<Program>(it->second));
		}

		void Program::reset()
		{
			_currentIndex = 0;
		}

		std::shared_ptr<Instruction> Program::resolveInstruction(Value const &retVal)
		{
			return _resolver->resolve();
		}

		
		std::shared_ptr<Instruction> Program::getCurrentInstruction()
		{
			std::shared_ptr<Instruction>	instruction;

			if (_calls.empty())
			{
				if (_currentIndex < _instructions.size())
				{
					instruction = _instructions[_currentIndex];
				}
				else
				{
					std::cout << "Program finished" << std::endl;
				}
			}
			else
			{
				std::weak_ptr<Program>			subProgram = _calls.top();

				instruction = subProgram.lock()->getCurrentInstruction();
				if (instruction == nullptr)
				{
					subProgram.lock()->reset();
					_calls.pop();

					return this->getCurrentInstruction();
				}
			}
			return instruction;
		}

		void Program::nextInstruction()
		{
			if (_calls.empty())
			{
				++_currentIndex;
			}
			else
			{
				std::weak_ptr<Program>			subProgram = _calls.top();

				subProgram.lock()->nextInstruction();
			}
		}

		std::shared_ptr<Instruction> Program::execute(Value const &retVal)
		{
			std::shared_ptr<Instruction>	currentInstruction = this->getCurrentInstruction();

			if (_state == Execution 
				&& currentInstruction 
				&& !currentInstruction->parametersIsResolved())
			{
				_resolver = std::shared_ptr<InstructionResolver>(new InstructionResolver(*currentInstruction));
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
			else
			{
				this->nextInstruction();
			}
			return currentInstruction;
		}
	}
}