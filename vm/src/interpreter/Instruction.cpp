#include <algorithm>
#include "interpreter/Instruction.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		Instruction::Instruction(unsigned const int lineNumber) : _lineNumber(lineNumber), _isResolved(true)
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

		bool Instruction::parametersIsResolved() const
		{
			return _isResolved;
		}

		void Instruction::addParameter(std::shared_ptr<AParameter> const &param)
		{
			if (param->getType() == AParameter::InstructionType)
			{
				_isResolved = false;
			}
			_parameters.push_back(param);
		}

		std::shared_ptr<AParameter>	Instruction::getUnresolvedParameter()
		{
			auto it = std::find_if(_parameters.begin(), _parameters.end(), [](std::shared_ptr<AParameter> const &param)
			{
				if (param->getType() == AParameter::InstructionType)
				{
					return true;
				}
				return false;
			});
			if (it != _parameters.end())
			{
				return *it;
			}
			return std::shared_ptr<AParameter>();
		}

		void Instruction::resolveParameter(std::shared_ptr<AParameter> const &paramToResolve,
										   std::shared_ptr<AParameter> const &resolvedParam)
		{
			bool isResolved = false;

			for (unsigned int i = 0; i < _parameters.size(); ++i)
			{
				if (_parameters[i] == paramToResolve)
				{
					_parameters[i] = resolvedParam;
					isResolved = true;
				}
			}
			if (!isResolved)
			{
				throw std::runtime_error("No such parameter to resolve");
			}
		}

		Instruction::ParameterContainerType &Instruction::getParameters()
		{
			return _parameters;
		}
	}
}