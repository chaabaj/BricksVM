#include "exception/InvalidOperationException.hpp"
#include "interpreter/Value.hpp"
#include "core/Computation.hpp"

namespace bricksvm
{
    namespace interpreter
    {
        Value::Value(Value const &other) : _value(other._value), _type(other._type), _typeSize(other._typeSize)
        {

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
            Value   result = (*this);
            
            if (_type != rhs._type)
            {
                return result + rhs.cast(_type);
            }
            result.compute<bricksvm::core::Add>(rhs);
            return result;
        }

        Value Value::operator-(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) - rhs.cast(_type);
            }
            result.compute<bricksvm::core::Substract>(rhs);
            return result;
        }

        Value Value::operator/(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) / rhs.cast(_type);
            }
            result.compute<bricksvm::core::Divide>(rhs);
            return result;
        }

        Value Value::operator*(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) * rhs.cast(_type);
            }
            result.compute<bricksvm::core::Multiply>(rhs);
            return result;
        }

        Value Value::operator%(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) * rhs.cast(_type);
            }
            result.compute<bricksvm::core::Modulo>(rhs);
            return result;
        }

        Value Value::operator|(Value const &rhs) const
        {
            Value result = (*this);

            if (_type != rhs._type)
            {
                return (*this) * rhs.cast(_type);
            }
            result.compute<bricksvm::core::BinaryOr>(rhs);
            return result;
        }

        Value Value::operator&(Value const &rhs) const
        {
            Value result = (*this);

            if (_type != rhs._type)
            {
                return (*this) >> rhs.cast(_type);
            }
            result.compute<bricksvm::core::BinaryAnd>(rhs);
            return result;
        }

        Value Value::operator>>(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) >> rhs.cast(_type);
            }
            result.compute<bricksvm::core::BinaryRightShift>(rhs);
            return result;
        }

        Value Value::operator<<(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) << rhs.cast(_type);
            }
            result.compute<bricksvm::core::BinaryLeftShift>(rhs);
            return result;
        }

        Value Value::operator^(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) ^ rhs.cast(_type);
            }
            result.compute<bricksvm::core::BinaryXor>(rhs);
            return result;
        }

        bool Value::operator==(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) == rhs.cast(_type);
            }
            result.compute<bricksvm::core::Equal>(rhs);
            return result.as<bool>();
        }

        bool Value::operator>(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) > rhs.cast(_type);
            }
            result.compute<bricksvm::core::GreaterThan>(rhs);
            return result.as<bool>();
        }

        bool Value::operator<(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) < rhs.cast(_type);
            }
            result.compute<bricksvm::core::LowerThan>(rhs);
            return result.as<bool>();
        }

        bool Value::operator>=(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) >= rhs.cast(_type);
            }
            result.compute<bricksvm::core::GreaterOrEqualThan>(rhs);
            return result.as<bool>();
        }

        bool Value::operator<=(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) <= rhs.cast(_type);
            }
            result.compute<bricksvm::core::LowerOrEqualThan>(rhs);
            return result.as<bool>();
        }


        bool Value::operator!=(Value const &rhs) const
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) != rhs.cast(_type);
            }
            result.compute<bricksvm::core::NotEqual>(rhs);
            return result.as<bool>();
        }
    }
}