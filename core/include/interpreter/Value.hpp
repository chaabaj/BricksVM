#ifndef __BRICKSVM_INTERPRETER_VALUE_HPP__
# define __BRICKSVM_INTERPRETER_VALUE_HPP__

# include <assert.h>
# include "core/Any.hpp"
# include "core/DllExport.hpp"
# include "exception/InvalidTypeException.hpp"

namespace bricksvm
{
    namespace interpreter
    {
        enum EXPORT_DLL Type
        {
            Int8,
            Int16,
            Int32,
            Float,
            Double,
            Int64,
        };

        template<typename ScalarType, int size>
        struct EXPORT_DLL DetectType;

        template<typename ScalarType>
        struct EXPORT_DLL DetectType < ScalarType, sizeof(int) >
        {
            static const int type = Int32;
        };

        template<typename ScalarType>
        struct DetectType < ScalarType, sizeof(long long int) >
        {
            static const int type = Int64;
        };

        template<typename ScalarType>
        struct DetectType < ScalarType, sizeof(short int) >
        {
            static const int type = Int16;
        };

        template<typename ScalarType>
        struct DetectType < ScalarType, sizeof(char) >
        {
            static const int type = Int8;
        };

        template<>
        struct DetectType < float, sizeof(float) >
        {
            static const int type = Float;
        };

        template<>
        struct DetectType < double, sizeof(double) >
        {
            static const int type = Double;
        };


        template<typename T>
        class EXPORT_DLL TypeTraits
        {
        public:
            static const int type = DetectType<T, sizeof(T)>::type;
        };


        class EXPORT_DLL Value
        {
        public:

            template<typename ScalarType>
            Value(ScalarType const scalar)
            {
                static_assert(std::is_scalar<ScalarType>::value, "T must be a scalar");
                _value = bricksvm::core::Any(scalar);
                _type = static_cast<Type>(TypeTraits<ScalarType>::type);
                _typeSize = sizeof(ScalarType);
            }

            Value(Value const &other);

            Value &operator=(Value const &other);


            template<typename T>
            inline operator const T() const
            {
                static_assert(std::is_scalar<T>::value, "T must be a scalar");
                if (_type != TypeTraits<T>::type)
                {
                    return this->cast(static_cast<Type>(TypeTraits<T>::type));
                }
                return _value.getValue<T>();
            }

            template<typename T>
            inline T const as() const
            {
                static_assert(std::is_scalar<T>::value, "T must be a scalar");
                if (_type != TypeTraits<T>::type)
                {
                    return this->cast(static_cast<Type>(TypeTraits<T>::type));
                }
                return _value.getValue<T>();
            }

            Value operator+(Value const &rhs);
            Value operator-(Value const &rhs);
            Value operator/(Value const &rhs);
            Value operator*(Value const &rhs);
            Value operator%(Value const &rhs);
            Value operator|(Value const &rhs);
            Value operator&(Value const &rhs);
            Value operator>>(Value const &rhs);
            Value operator<<(Value const &rhs);
            Value operator^(Value const &rhs);

            ~Value() {}

            Value cast(Type const type) const;

        private:

            template<typename ScalarType>
            Value cast(ScalarType scalar, Type const destType) const
            {
                switch (destType)
                {
                case Int8:
                    return Value(static_cast<char>(scalar));
                case Int16:
                    return Value(static_cast<short int>(scalar));
                case Int32:
                    return Value(static_cast<int>(scalar));
                case Int64:
                    return Value(static_cast<long long int>(scalar));
                case Float:
                    return Value(static_cast<float>(scalar));
                case Double:
                    return Value(static_cast<double>(scalar));
                default:
                    throw bricksvm::exception::InvalidTypeException("Unknown type");
                }
            }

            template<typename OperationFunction>
            void doOperation(Value const &rhs, OperationFunction const &&op)
            {

                switch (_type)
                {
                case Int8:
                {
                    char lhsVal = _value.getValue<char>();
                    char rhsVal = rhs._value.getValue<char>();
                    char result = op(lhsVal, rhsVal);

                    _value = bricksvm::core::Any(result);
                }
                case Int16:
                {
                    short int lhsVal = _value.getValue<short int>();
                    short int rhsVal = rhs._value.getValue<short int>();
                    short int result = op(lhsVal, rhsVal);

                    _value = bricksvm::core::Any(result);
                }
                case Int32:
                {
                    int lhsVal = _value.getValue<int>();
                    int rhsVal = rhs._value.getValue<int>();
                    int result = op(lhsVal, rhsVal);

                    _value = bricksvm::core::Any(result);
                }
                case Int64:
                {
                    long long int lhsVal = _value.getValue<long long int>();
                    long long int rhsVal = rhs._value.getValue<long long int>();
                    long long int result = op(lhsVal, rhsVal);

                    _value = bricksvm::core::Any(result);
                }
                case Float:
                {
                    float lhsVal = _value.getValue<float>();
                    float rhsVal = rhs._value.getValue<float>();
                    float result = op(lhsVal, rhsVal);

                    _value = bricksvm::core::Any(result);
                }
                case Double:
                {
                    double lhsVal = _value.getValue<double>();
                    double rhsVal = rhs._value.getValue<double>();
                    double result = op(lhsVal, rhsVal);

                    _value = bricksvm::core::Any(result);
                }
                default:
                    throw bricksvm::exception::InvalidTypeException("Unknown type");
                }
            }

        private:
            bricksvm::core::Any _value;
            Type                _type;
            unsigned int        _typeSize;
        };

    }

}

#endif
