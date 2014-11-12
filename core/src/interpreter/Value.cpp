#include "exception/InvalidOperationException.hpp"
#include "interpreter/Value.hpp"
#include "core/Computation.hpp"

namespace bricksvm
{
    namespace interpreter
    {
        Value::Value(Value const &other) : _type(other._type), _typeSize(other._typeSize)
        {
            _value = other._value;
        }

        Value	&Value::operator=(Value const &other)
        {
            _value = other._value;
            _type = other._type;
            _typeSize = other._typeSize;
            return (*this);
        }

        Value  Value::cast(Type const type) const
        {
            switch (_type)
            {
            case Int8:
            {
                char val = _value.getValue<char>();

                return this->cast(val, type);
            }
            case Int16:
            {
                short int val = _value.getValue<short int>();

                return this->cast(val, type);
            }
            case Int32:
            {
                int val = _value.getValue<int>();

                return this->cast(val, type);
            }
            case Int64:
            {
                long long int val = _value.getValue<long long int>();

                return this->cast(val, type);
            }
            case Float:
            {
                float val = _value.getValue<float>();

                return this->cast(val, type);
            }
            case Double:
            {
                double val = _value.getValue<double>();

                return this->cast(val, type);
            }
            default:
                throw bricksvm::exception::InvalidTypeException("Unknown type");
            }
        }

        Value Value::operator+(Value const &rhs) const
        {
            return this->compute<bricksvm::core::Add>(rhs);
        }

        Value Value::operator-(Value const &rhs) const
        {
            return this->compute<bricksvm::core::Substract>(rhs);
        }

        Value Value::operator/(Value const &rhs) const
        {
            return this->compute<bricksvm::core::Divide>(rhs);
        }

        Value Value::operator*(Value const &rhs) const
        {
            return this->compute<bricksvm::core::Multiply>(rhs);
        }

        Value Value::operator%(Value const &rhs) const
        {
            return this->compute<bricksvm::core::Modulo>(rhs);
        }

        Value Value::operator|(Value const &rhs) const
        {
            return this->compute<bricksvm::core::BinaryOr>(rhs);
        }

        Value Value::operator&(Value const &rhs) const
        {
            return this->compute<bricksvm::core::BinaryAnd>(rhs);
        }

        Value Value::operator>>(Value const &rhs) const
        {
            return this->compute<bricksvm::core::BinaryRightShift>(rhs);
        }

        Value Value::operator<<(Value const &rhs) const
        {
            return this->compute<bricksvm::core::BinaryLeftShift>(rhs);
        }

        Value Value::operator^(Value const &rhs) const
        {
            return this->compute<bricksvm::core::BinaryXor>(rhs);
        }

        bool Value::operator==(Value const &rhs) const
        {
            return this->compute<bricksvm::core::Equal>(rhs).as<bool>();
        }

        bool Value::operator>(Value const &rhs) const
        {
            return this->compute<bricksvm::core::GreaterThan>(rhs).as<bool>();
        }

        bool Value::operator<(Value const &rhs) const
        {
            return this->compute<bricksvm::core::LowerThan>(rhs).as<bool>();
        }

        bool Value::operator>=(Value const &rhs) const
        {
            return this->compute<bricksvm::core::GreaterOrEqualThan>(rhs).as<bool>();
        }

        bool Value::operator<=(Value const &rhs) const
        {
            return this->compute<bricksvm::core::LowerOrEqualThan>(rhs).as<bool>();
        }

        bool Value::operator!=(Value const &rhs) const
        {
            return this->compute<bricksvm::core::NotEqual>(rhs).as<bool>();
        }
    }
}