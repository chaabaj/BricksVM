#include "interpreter/ValueParameter.hpp"

namespace bricksvm
{
    namespace interpreter
    {
        ValueParameter::ValueParameter(Value const &value) : AParameter(AParameter::ValueType), _value(value)
        {

        }

        ValueParameter::~ValueParameter()
        {

        }

        ValueParameter::ValueParameter(Value const &&value) : AParameter(AParameter::ValueType), _value(value)
        {

        }

        Value const &ValueParameter::getValue() const
        {
            return _value;
        }
    }
}