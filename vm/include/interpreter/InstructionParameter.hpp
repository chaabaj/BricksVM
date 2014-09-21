#ifndef __BRICKSVM_INTERPRETER_INSTRUCTIONPARAMETER_HPP__
# define __BRICKSVM_INTERPRETER_INSTRUCTIONPARAMETER_HPP__

# include "interpreter/Instruction.hpp"
# include "interpreter/AParameter.hpp"
# include "core/IClonable.hpp"
# include "core/NewPolicy.hpp"

namespace bricksvm
{
    namespace interpreter
    {
        class InstructionParameter : public AParameter,
                                     public bricksvm::core::IClonable<AParameter>,
                                     public bricksvm::core::NewPolicy < InstructionParameter >
        {
        public:
            InstructionParameter(std::shared_ptr<Instruction> const &instruction);
            ~InstructionParameter();

            std::shared_ptr<Instruction> getInstruction();

            std::shared_ptr<AParameter> clone() const;

            std::shared_ptr<const Instruction> getInstruction() const;

        private:
            std::shared_ptr<Instruction>    _instruction;
        };
    }
}

#endif
