#ifndef __BRICKSVM_CORE_ANY_HPP__
# define __BRICKSVM_CORE_ANY_HPP__

# include <iostream>
# include <memory>
# include "core/DllExport.hpp"
# include "core/Utils.hpp"

namespace bricksvm
{
    namespace core
    {
        /**
         * @interface IValue used for the implementation of type erasure
         */
        class EXPORT_DLL IValue
        {
        public:
            virtual ~IValue() {}
            virtual bool isRefWrapper() const = 0;
        };

        /**
         * @class ValueHolder
         * @tparam ValueType value type to store
         * @tparam isRefWrapper false if the value is not a std::reference_wrapper
         */
        template<typename ValueType, bool isRefWrapper>
        class EXPORT_DLL ValueHolder
        {
        public:

            typedef ValueType   ReturnType;

            ValueHolder()
            {

            }

            ValueHolder(ValueType const &value) : _value(value)
            {

            }

            ~ValueHolder()
            {

            }

            ReturnType &get()
            {
                return _value;
            }

            ReturnType const &get() const
            {
                return _value;
            }

        private:
            ValueType   _value;
        };


        /**
         * @class ValueHolder
         * @tparam ValueType value type
         *
         * @desc this is a specialisation for holding std::reference_wrapper object
         */
        template<typename ValueType>
        class EXPORT_DLL ValueHolder < ValueType, true >
        {
        public:
            typedef typename ValueType::type    ReturnType;

            ValueHolder()
            {

            }

            ValueHolder(ValueType const &value) : _value(value)
            {

            }

            ~ValueHolder()
            {

            }

            ReturnType &get()
            {
                return _value.get();
            }

            ReturnType const &get() const
            {
                return _value.get();
            }

        private:
            ValueType   _value;
        };

        /**
         * @class Value
         * @tparam ValueType value to store
         */
        template<typename ValueType>
        class EXPORT_DLL Value : public IValue
        {
        public:

            typedef ValueHolder<ValueType, TypeTraits<ValueType>::is_ref_wrapper>   ValueHolderType;
            typedef typename ValueHolderType::ReturnType                            ReturnType;


            Value(ValueType const &value) : _valueHolder(ValueHolderType(value))
            {
            }

            ~Value()
            {

            }

            bool isRefWrapper() const
            {
                return TypeTraits<ValueType>::is_ref_wrapper;
            }

            ReturnType &get()
            {
                return _valueHolder.get();
            }

            ReturnType const &get() const
            {
                return _valueHolder.get();
            }

        private:

            ValueHolderType _valueHolder;
        };


        /**
         * @class Any
         *
         * @desc Any can store any type of value. It's act like dynamic typing
         */
        class EXPORT_DLL Any
        {
        public:

            /// default constructor
            Any();

            template<typename ValueType>
            Any(ValueType const &value)
            {
                _value = std::shared_ptr<IValue>(new Value<ValueType>(value));
            }


            Any &operator=(Any const &other)
            {
                _value = other._value;
                return (*this);
            }

            ~Any();


            /// get a reference to the value
            template<typename ValueType>
            ValueType &getValue()
            {
                if (_value->isRefWrapper())
                {
                    return static_cast<Value<std::reference_wrapper<ValueType> >&>(*_value).get();
                }
                return static_cast<Value<ValueType> &>(*_value).get();
            }

            template<typename ValueType>
            ValueType const &getValue() const
            {
                if (_value->isRefWrapper())
                {
                    return static_cast<Value<std::reference_wrapper<ValueType> >&>(*_value).get();
                }
                return static_cast<Value<ValueType> &>(*_value).get();
            }

        private:
            std::shared_ptr<IValue> _value;
        };
    }
}

#endif
