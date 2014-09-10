#include "interpreter/Instruction.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		Instruction::Instruction(unsigned const int lineNumber) : _lineNumber(lineNumber)
		{

		}

		Instruction::~Instruction()
		{

		}

		void Instruction::setName(std::string const &name)
		{
			_name = name;
		}
		
		std::string const &Instruction::getName() const
		{
			return _name;
		}

		void Instruction::addParameter(std::shared_ptr<AParameter> const &param)
		{
			_parameters.push_back(param);
		}

		Instruction::ParameterContainerType &Instruction::getParameters()
		{
			return _parameters;
		}
	}
}