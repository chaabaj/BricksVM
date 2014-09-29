#include "exception/InvalidOperationException.hpp"
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

        Value Value::operator+(Value const &rhs)
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return result + rhs.cast(_type);
            }
            else if (_type != Float && _type != Double)
            {
                this->doOperation(rhs, [](long long int a, long long int b)
                {
                    return a + b;
                });
            }
            else
            {
                this->doOperation(rhs, [](double a, double b)
                {
                    return a + b;
                });
            }
            
            return result;
        }

        Value Value::operator-(Value const &rhs)
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return result - rhs.cast(_type);
            }
            else if (_type != Float && _type != Double)
            {
                this->doOperation(rhs, [](long long int a, long long int b)
                {
                    return a - b;
                });
            }
            else
            {
                this->doOperation(rhs, [](double a, double b)
                {
                    return a - b;
                });
            }
            return result;
        }

        Value Value::operator/(Value const &rhs)
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return result / rhs.cast(_type);
            }
            else if (_type != Float && _type != Double)
            {
                this->doOperation(rhs, [](long long int a, long long int b)
                {
                    return a / b;
                });
            }
            else
            {
                this->doOperation(rhs, [](double a, double b)
                {
                    return a / b;
                });
            }
            return result;
        }

        Value Value::operator*(Value const &rhs)
        {
            Value   result = (*this);

            if (_type != rhs._type)
            {
                return (*this) * rhs.cast(_type);
            }
            else if (_type != Float && _type != Double)
            {
                this->doOperation(rhs, [](long long int a, long long int b)
                {
                    return a * b;
                });
            }
            else
            {
                this->doOperation(rhs, [](double a, double b)
                {
                    return a * b;
                });
            }
            return result;
        }

        Value Value::operator%(Value const &rhs)
        {
            Value   result = (*this);

            if (_type == Float || _type == Double)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do modulo on float/double type");
            }
            else if (_type != rhs._type)
            {
                return (*this) % rhs.cast(_type);
            }
            else
            {
                this->doOperation(rhs, [](long long int a, long long int b)
                {
                    return a % b;
                });
            }
            return result;
        }

        Value Value::operator|(Value const &rhs)
        {
            Value result = (*this);

            if (_type == Float || _type == Double)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do modulo on float/double type");
            }
            else if (_type != rhs._type)
            {
                return (*this) | rhs.cast(_type);
            }
            else
            {
                this->doOperation(rhs, [](long long int a, long long int b)
                {
                    return a | b;
                });
            }
            return result;
        }

        Value Value::operator&(Value const &rhs)
        {
            Value result = (*this);

            if (_type == Float || _type == Double)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do modulo on float/double type");
            }
            else if (_type != rhs._type)
            {
                return (*this) & rhs.cast(_type);
            }
            else
            {
                this->doOperation(rhs, [](long long int a, long long int b)
                {
                    return a & b;
                });
            }
            return result;
        }

        Value Value::operator>>(Value const &rhs)
        {
            Value   result = (*this);

            if (_type == Float || _type == Double)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do modulo on float/double type");
            }
            else if (_type != rhs._type)
            {
                return (*this) >> rhs.cast(_type);
            }
            else
            {
                this->doOperation(rhs, [](long long int a, long long int b)
                {
                    return a >> b;
                });
            }
            return result;
        }

        Value Value::operator<<(Value const &rhs)
        {
            Value   result = (*this);

            if (_type == Float || _type == Double)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do modulo on float/double type");
            }
            else if (_type != rhs._type)
            {
                return (*this) << rhs.cast(_type);
            }
            else
            {
                this->doOperation(rhs, [](long long int a, long long int b)
                {
                    return a << b;
                });
            }
            return result;
        }

        Value Value::operator^(Value const &rhs)
        {
            Value   result = (*this);

            if (_type == Float || _type == Double)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do modulo on float/double type");
            }
            else if (_type != rhs._type)
            {
                return (*this) ^ rhs.cast(_type);
            }
            else
            {
                this->doOperation(rhs, [](long long int a, long long int b)
                {
                    return a ^ b;
                });
            }
            return result;
        }

    }
}