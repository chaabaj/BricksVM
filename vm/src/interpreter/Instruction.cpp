#include <algorithm>
#include "interpreter/Instruction.hpp"
#include "interpreter/InstructionParameter.hpp"
#include "core/Utils.hpp"
#include "core/Console.hpp"

namespace bricksvm
{
    namespace interpreter
    {
        Instruction::Instruction(unsigned const int lineNumber) : _isResolved(true), _lineNumber(lineNumber)
        {
        }

        Instruction::~Instruction()
        {

        }

        std::shared_ptr<Instruction> Instruction::clone() const
        {
            std::shared_ptr<Instruction>	clonedInstruction = std::shared_ptr<Instruction>(new Instruction(_lineNumber));

            clonedInstruction->_isResolved = _isResolved;
            for (std::shared_ptr<AParameter> param : _parameters)
            {
                InstructionParameter *instructionParam;

                if (param->getType() == AParameter::InstructionType)
                {
                    instructionParam = dynamic_cast<InstructionParameter*>(param.get());
                    clonedInstruction->addParameter(instructionParam->clone());
                }
                else
                {
                    /// Don't need to clone a value just keep a reference to the value
                    clonedInstruction->addParameter(param);
                }

            }
            clonedInstruction->_name = _name;
            return clonedInstruction;
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
            if (!this->getUnresolvedParameter())
            {
                _isResolved = true;
            }
            bricksvm::core::throwIf<std::runtime_error>(!isResolved, "No such parameter to resolve");
        }

        Instruction::ParameterContainerType &Instruction::getParameters()
        {
            return _parameters;
        }
    }
}