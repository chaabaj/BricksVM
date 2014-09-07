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
		public:
			enum Type
			{
				Int32,
				Int64,
				Int16,
				Int8,
				Float,
				Double,
			};
		private:
			bricksvm::core::Any	_value;
			Type				_type;
		};
	}
}

#endif