#ifndef __BRICKSVM_INTERPRETER_INSTRUCTIONRESOLVER_HPP__
# define __BRICKSVM_INTERPRETER_INSTRUCTIONRESOLVER_HPP__

# include <list>
# include <memory>
# include "interpreter/Value.hpp"
# include "interpreter/AParameter.hpp"
# include "interpreter/Instruction.hpp"
# include "core/NewPolicy.hpp"

namespace bricksvm
{
    namespace interpreter
    {
        class InstructionResolver : public bricksvm::core::NewPolicy < InstructionResolver >
        {
        public:
            InstructionResolver(std::shared_ptr<Instruction> const &instructionToResolve);
            ~InstructionResolver();

            void setResolvedValue(Value const &resolvedValue);

            std::shared_ptr<Instruction> resolve();

            bool isResolved() const;

        private:

            void next();


        private:

            typedef std::list<std::shared_ptr<AParameter> >	ParameterContainerType;

            ParameterContainerType          _paramsToResolve;
            std::shared_ptr<Instruction>    _instructionToResolve;

        };
    }
}

#endif