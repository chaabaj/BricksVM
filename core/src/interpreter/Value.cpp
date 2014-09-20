#include "interpreter/Value.hpp"

namespace bricksvm
{
    namespace interpreter
    {
        Value::Value(Value const &other) : _value(other._value), _type(other._type)
        {

        }

        Value	&Value::operator=(Value const &other)
        {
            _value = other._value;
            _type = other._type;
            return (*this);
        }

    }
}