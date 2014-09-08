#ifndef __BRICKSVM_INTERPRETER_VALUE_HPP__
# define __BRICKSVM_INTERPRETER_VALUE_HPP_

# include "core/Any.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		class Value
		{
		public:
			template<typename ScalarType>
			Value(ScalarType const scalar)
			{
				_value = bricksvm::core::Any(scalar);
			}

			~Value() {}
		public:
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
		private:
			bricksvm::core::Any	_value;
			Type				_type;
		};
	}
}

#endif