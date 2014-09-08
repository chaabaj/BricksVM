#ifndef __BRICKSVM_INTERPRETER_VALUEPARAMETER_HPP__
# define __BRICKSVM_INTERPRETER_VALUEPARAMETER_HPP__

# include "interpreter/AParameter.hpp"
# include "interpreter/Value.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		class ValueParameter : public AParameter
		{
		public:
			ValueParameter(Value const &value);
			~ValueParameter();

			Value const	&getValue() const;

		private:
			Value const &_value;

		};
	}
}

#endif