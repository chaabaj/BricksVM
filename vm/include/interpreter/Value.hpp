#ifndef __BRICKSVM_INTERPRETER_VALUE_HPP__
# define __BRICKSVM_INTERPRETER_VALUE_HPP__

# include <assert.h>
# include "core/Any.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		enum Type
		{
			Int32,
			Int64,
			Int16,
			Int8,
			Float,
			Double,
			String
		};

		template<typename ScalarType>
		struct TypeTraits
		{

		private:
			template<typename ScalarType, int size>
			struct DetectType;

			template<typename ScalarType>
			struct DetectType < ScalarType, sizeof(int) >
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

			template<>
			struct DetectType < std::string, sizeof(std::string) >
			{
				static const int type = String;
			};

		public:
			static const int type = DetectType<ScalarType, sizeof(ScalarType)>::type;
		};

		
		class Value
		{
		public:

			template<typename ScalarType>
			Value(ScalarType const scalar)
			{
				_value = bricksvm::core::Any(scalar);
				_type = static_cast<Type>(TypeTraits<ScalarType>::type);
			}

			Value(Value const &other);

			Value &operator=(Value const &other);

			template<typename T>
			inline operator T&()
			{
				assert(_type == TypeTraits<ScalarType>::type);
				return _value.getValue<T>();
			}

			~Value() {}
		private:
			bricksvm::core::Any	_value;
			Type				_type;
		};

		

	}

}

#endif