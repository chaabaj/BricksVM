#include "interpreter/InstructionParameter.hpp"

namespace bricksvm
{
    namespace interpreter
    {
        InstructionParameter::InstructionParameter(std::shared_ptr<Instruction> &instruction) : AParameter(AParameter::InstructionType), _instruction(instruction)
        {

        }

        InstructionParameter::~InstructionParameter()
        {

        }

        std::shared_ptr<AParameter> InstructionParameter::clone() const
        {
            return std::shared_ptr<AParameter>(new InstructionParameter(_instruction->clone()));
        }

        std::shared_ptr<Instruction> InstructionParameter::getInstruction()
        {
            return _instruction;
        }

        std::shared_ptr<const Instruction> InstructionParameter::getInstruction() const
        {
            return _instruction;
        }
    }
}