#ifndef __BRICKSVM_INTERPRETER_INSTRUCTION_HPP__
# define __BRICKSVM_INTERPRETER_INSTRUCTION_HPP__

# include <vector>
# include <memory>
# include <string>
# include "core/IClonable.hpp"
# include "interpreter/AParameter.hpp"
# include "core/NewPolicy.hpp"

namespace bricksvm
{
    namespace interpreter
    {
        class Instruction : public bricksvm::core::IClonable<Instruction>,
                            public bricksvm::core::NewPolicy < Instruction >
        {
        public:

            typedef std::vector<std::shared_ptr<AParameter> >	ParameterContainerType;

            Instruction(unsigned const int lineNumber);
            ~Instruction();

            std::shared_ptr<Instruction> clone() const;

            void setName(std::string const &str);
            void addParameter(std::shared_ptr<AParameter> const &parameter);

            ParameterContainerType		&getParameters();

            bool						parametersIsResolved() const;

            void						resolveParameter(std::shared_ptr<AParameter> const &paramToResolve,
                                                         std::shared_ptr<AParameter> const &resolvedValue);

            std::shared_ptr<AParameter> getUnresolvedParameter();

            std::string const			&getName() const;


        private:
            bool                    _isResolved;
            std::string             _name;
            ParameterContainerType  _parameters;
            unsigned const int      _lineNumber;
        };
    }
}

#endif