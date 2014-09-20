#include "interpreter/InstructionResolver.hpp"
#include "interpreter/ValueParameter.hpp"
#include "interpreter/InstructionParameter.hpp"
#include "exception/InvalidInstructionException.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		InstructionResolver::InstructionResolver(std::shared_ptr<Instruction> const &instructionToResolve) : _instructionToResolve(instructionToResolve)
		{
			this->next();
		}

		InstructionResolver::~InstructionResolver()
		{

		}

		bool InstructionResolver::isResolved() const
		{
			return _paramsToResolve.size() && _instructionToResolve->parametersIsResolved();
		}

		std::shared_ptr<Instruction> InstructionResolver::resolve()
		{
			if (_paramsToResolve.empty())
			{
				throw exception::InvalidInstructionException("No such parameter to resolve");
			}
			else
			{
				InstructionParameter	*param = dynamic_cast<InstructionParameter*>(_paramsToResolve.back().get());
				
				return param->getInstruction();
			}
		}


		void InstructionResolver::next()
		{
			if (!_paramsToResolve.empty())
			{
				InstructionParameter	*param = dynamic_cast<InstructionParameter*>(_paramsToResolve.back().get());
				auto					instruction = param->getInstruction();
				
				if (!instruction->parametersIsResolved())
				{
					auto newParam = instruction->getUnresolvedParameter();
					_paramsToResolve.push_back(newParam);
					this->next();
				}
			}
			else if (!_instructionToResolve->parametersIsResolved())
			{
				auto newParam = _instructionToResolve->getUnresolvedParameter();
				
				_paramsToResolve.push_back(newParam);
				this->next();
			}
		}

		void InstructionResolver::setResolvedValue(Value const &resolvedValue)
		{
			auto paramToResolve = _paramsToResolve.back();
			auto resolvedValueParam = std::shared_ptr<ValueParameter>(new ValueParameter(resolvedValue));
			
			_paramsToResolve.pop_back();
			if (_paramsToResolve.empty())
			{
				_instructionToResolve->resolveParameter(paramToResolve, resolvedValueParam);
			}
			else
			{
				InstructionParameter *parent = dynamic_cast<InstructionParameter*>(_paramsToResolve.back().get());

				parent->getInstruction()->resolveParameter(paramToResolve, resolvedValueParam);
			}
			this->next();
		}
	}
}