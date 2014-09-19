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
		class EXPORT_DLL IValue
		{
		public:
			virtual ~IValue() {}
			virtual bool isRefWrapper() const = 0;
		};

		template<typename ValueType, bool isRefWrapper>
		class EXPORT_DLL ValueHolder
		{
		public:

			typedef ValueType	ReturnType;

			ValueHolder()
			{

			}

			ValueHolder(ValueType &value) : _value(value)
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
			ValueType	_value;
		};

		template<typename ValueType>
		class EXPORT_DLL ValueHolder <ValueType, true>
		{
		public:
			typedef typename ValueType::type ReturnType;

			ValueHolder()
			{

			}

			ValueHolder(ValueType &value) : _value(value)
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
			ValueType	_value;
		};

		template<typename ValueType>
		class EXPORT_DLL Value : public IValue
		{
		public:

			typedef ValueHolder<ValueType, TypeTraits<ValueType>::is_ref_wrapper>	ValueHolderType;
			typedef typename ValueHolderType::ReturnType							ReturnType;


			Value(ValueType &value) : _valueHolder(ValueHolderType(value))
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
			
			ValueHolderType	_valueHolder;
		};

		class EXPORT_DLL Any
		{
		public:

			Any()
			{

			}

			template<typename ValueType>
			Any(ValueType &value)
			{
				_value = std::shared_ptr<IValue>(new Value<ValueType>(value));
			}

			Any(Any const &&other) : _value(other._value)
			{

			}

			Any(Any const &other) : _value(other._value)
			{
			
			}

			Any &operator=(Any const &other)
			{
				_value = other._value;
				return (*this);
			}

			~Any()
			{

			}


			template<typename ValueType>
			ValueType &getValue()
			{
				if (_value->isRefWrapper())
				{
					return static_cast<Value<std::reference_wrapper<ValueType> >&>(*_value).get();
				}
				return static_cast<Value<ValueType> &>(*_value).get();
			}

		private:
			std::shared_ptr<IValue>	_value;
		};
	}
}

#endif