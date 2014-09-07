#ifndef __BRICKSVM_CORE_ANY_HPP__
# define __BRICKSVM_CORE_ANY_HPP__

# include <iostream>
# include <memory>

namespace bricksvm
{
	namespace core
	{
		class IValue
		{
		public:
			virtual ~IValue() {}
		};

		template<typename ValueType>
		class Value : public IValue
		{
		public:
			Value(ValueType &value) : _value(value)
			{
			}

			~Value()
			{

			}

			ValueType &get()
			{
				return _value;
			}

		private:
			ValueType	_value;
		};

		class Any
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
				return static_cast<Value<ValueType> &>(*_value).get();
			}

		private:
			std::shared_ptr<IValue>	_value;
		};
	}
}

#endif