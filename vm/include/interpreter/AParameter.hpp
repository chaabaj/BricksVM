#ifndef __BRICKSVM_INTERPRETER_APARAMETER_HPP__
# define __BRICKSVM_INTERPRETER_APARAMETER_HPP__

namespace bricksvm
{
    namespace interpreter
    {
        class AParameter
        {
        public:
            enum Type
            {
                ValueType,
                InstructionType
            };

            AParameter(Type const &type);

            virtual ~AParameter();

            Type const &getType() const;

        protected:
            Type    _type;
        };
    }
}

#endif