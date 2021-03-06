#ifndef __BRICKSVM_INTERPRETER_VALUE_HPP__
# define __BRICKSVM_INTERPRETER_VALUE_HPP__

# include <iostream>
# include "core/Any.hpp"
# include "core/DllExport.hpp"
# include "exception/InvalidTypeException.hpp"

namespace bricksvm
{
    namespace interpreter
    {
        enum EXPORT_DLL Type
        {
            Int8 = 0,
            Int16 = 1,
            Int32 = 2,
            Int64 = 3,
            Float = 4,
            Double = 5,
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
        class EXPORT_DLL ValueTraits
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
                _type = static_cast<Type>(ValueTraits<ScalarType>::type);
                _typeSize = sizeof(ScalarType);
            }

            Value(Value const &other);

            Value &operator=(Value const &other);

            inline Type    type() const
            {
                return _type;
            }

            inline uint32_t size() const
            {
                return _typeSize;
            }

            std::string toString() const;

            template<typename T>
            inline operator const T() const
            {
                static_assert(std::is_scalar<T>::value, "T must be a scalar");
                if (_type != ValueTraits<T>::type)
                {
                    return this->cast(static_cast<Type>(ValueTraits<T>::type));
                }
                return _value.getValue<T>();
            }

            template<typename T>
            inline T const as() const
            {
                static_assert(std::is_scalar<T>::value, "T must be a scalar");
                if (_type != ValueTraits<T>::type)
                {
                    return this->cast(static_cast<Type>(ValueTraits<T>::type));
                }
                return _value.getValue<T>();
            }

            Value operator+(Value const &rhs) const;
            Value operator-(Value const &rhs) const;
            Value operator/(Value const &rhs) const;
            Value operator*(Value const &rhs) const;
            Value operator%(Value const &rhs) const;
            Value operator|(Value const &rhs) const;
            Value operator&(Value const &rhs) const;
            Value operator>>(Value const &rhs) const;
            Value operator<<(Value const &rhs) const;
            Value operator^(Value const &rhs) const;

            bool operator==(Value const &rhs) const;
            bool operator>(Value const &rhs) const;
            bool operator<(Value const &rhs) const;
            bool operator>=(Value const &rhs) const;
            bool operator<=(Value const &rhs) const;
            bool operator!=(Value const &rhs) const;

            ~Value() {}

            Value cast(Type const destType) const;

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


            template<template<typename> class Operation>
            Value compute(Value const &rhs) const
            {

                if (_type > rhs._type)
                {
                    return this->compute<Operation>(rhs.cast(_type));
                }
                else if (_type < rhs._type)
                {
                    Value lhs = (*this);

                    return lhs.cast(rhs._type).compute<Operation>(rhs);
                }
                else
                {
                    switch (_type)
                    {
                    case Int8:
                    {
                        char lhsVal = _value.getValue<char>();
                        char rhsVal = rhs._value.getValue<char>();
                        char result = Operation<char>::compute(lhsVal, rhsVal);

                        return Value(result);
                    }
                    case Int16:
                    {
                        short int lhsVal = _value.getValue<short int>();
                        short int rhsVal = rhs._value.getValue<short int>();
                        short int result = Operation<short int>::compute(lhsVal, rhsVal);

                        return Value(result);
                    }
                    case Int32:
                    {
                        int lhsVal = _value.getValue<int>();
                        int rhsVal = rhs._value.getValue<int>();
                        int result = Operation<int>::compute(lhsVal, rhsVal);

                        return Value(result);
                    }
                    case Int64:
                    {
                        long long int lhsVal = _value.getValue<long long int>();
                        long long int rhsVal = rhs._value.getValue<long long int>();
                        long long int result = Operation<long long int>::compute(lhsVal, rhsVal);

                        return Value(result);
                    }
                    case Float:
                    {
                        float lhsVal = _value.getValue<float>();
                        float rhsVal = rhs._value.getValue<float>();
                        float result = Operation<float>::compute(lhsVal, rhsVal);

                        return Value(result);
                    }
                    case Double:
                    {
                        double lhsVal = _value.getValue<double>();
                        double rhsVal = rhs._value.getValue<double>();
                        double result = Operation<double>::compute(lhsVal, rhsVal);

                        return Value(result);
                    }
                    default:
                        throw bricksvm::exception::InvalidTypeException("Unknown type");
                    }
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
