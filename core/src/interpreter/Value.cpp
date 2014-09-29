#include "exception/InvalidOperationException.hpp"
#include "interpreter/Value.hpp"
#include "core/Computation.hpp"

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
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return result + rhs.cast(_type);
            }
            result.doOperation<bricksvm::core::Add>(rhs);
            return result;
        }

        Value Value::operator-(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return result - rhs.cast(_type);
            }
            result.doOperation<bricksvm::core::Substract>(rhs);
            return result;
        }

        Value Value::operator/(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return result / rhs.cast(_type);
            }
            result.doOperation<bricksvm::core::Divide>(rhs);
            return result;
        }

        Value Value::operator*(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) * rhs.cast(_type);
            }
            result.doOperation<bricksvm::core::Multiply>(rhs);
            return result;
        }

        Value Value::operator%(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) * rhs.cast(_type);
            }
            result.doOperation<bricksvm::core::Modulo>(rhs);
            return result;
        }

        Value Value::operator|(Value const &rhs) const
        {
            Value result = (*this);

            if (_type != rhs._type)
            {
                return (*this) * rhs.cast(_type);
            }
            result.doOperation<bricksvm::core::BinaryOr>(rhs);
            return result;
        }

        Value Value::operator&(Value const &rhs) const
        {
            Value result = (*this);

            if (_type != rhs._type)
            {
                return (*this) >> rhs.cast(_type);
            }
            else
            {
                result.doOperation<bricksvm::core::BinaryAnd>(rhs);
            }
            return result;
        }

        Value Value::operator>>(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) >> rhs.cast(_type);
            }
            else
            {
                result.doOperation<bricksvm::core::BinaryRightShift>(rhs);
            }
            return result;
        }

        Value Value::operator<<(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) << rhs.cast(_type);
            }
            else
            {
                result.doOperation<bricksvm::core::BinaryLeftShift>(rhs);
            }
            return result;
        }

        Value Value::operator^(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) ^ rhs.cast(_type);
            }
            else
            {
                result.doOperation<bricksvm::core::BinaryXor>(rhs);
            }
            return result;
        }

        bool Value::operator==(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) == rhs.cast(_type);
            }
            result.doOperation<bricksvm::core::Equal>(rhs);
            return result.as<bool>();
        }

        bool Value::operator>(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) > rhs.cast(_type);
            }
            result.doOperation<bricksvm::core::GreaterThan>(rhs);
            return result.as<bool>();
        }

        bool Value::operator<(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) < rhs.cast(_type);
            }
            result.doOperation<bricksvm::core::LowerThan>(rhs);
            return result.as<bool>();
        }

        bool Value::operator>=(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) >= rhs.cast(_type);
            }
            result.doOperation<bricksvm::core::GreaterOrEqualThan>(rhs);
            return result.as<bool>();
        }

        bool Value::operator<=(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) <= rhs.cast(_type);
            }
            result.doOperation<bricksvm::core::LowerOrEqualThan>(rhs);
            return result.as<bool>();
        }


        bool Value::operator!=(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) != rhs.cast(_type);
            }
            result.doOperation<bricksvm::core::NotEqual>(rhs);
            return result.as<bool>();
        }
    }
}