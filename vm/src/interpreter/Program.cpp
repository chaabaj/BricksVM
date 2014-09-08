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

		std::shared_ptr<Instruction>	Program::nextInstruction()
		{
			if (_calls.empty())
			{
				if (_currentIndex < _instructions.size())
				{
					return _instructions[_currentIndex++];
				}
				return std::shared_ptr<Instruction>(nullptr);
			}
			else
			{
				std::weak_ptr<Program>			subProgram = _calls.top();
				std::shared_ptr<Instruction>	instruction;

				instruction = subProgram.lock()->nextInstruction();
				if (instruction == nullptr)
				{
					subProgram.lock()->reset();
					_calls.pop();
					return this->nextInstruction();
				}
				return instruction;
			}
		}
	}
}