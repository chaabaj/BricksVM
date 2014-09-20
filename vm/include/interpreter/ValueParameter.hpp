#ifndef __BRICKSVM_INTERPRETER_VALUEPARAMETER_HPP__
# define __BRICKSVM_INTERPRETER_VALUEPARAMETER_HPP__

# include "core/NewPolicy.hpp"
# include "interpreter/AParameter.hpp"
# include "interpreter/Value.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		class ValueParameter : public AParameter,
							   public bricksvm::core::NewPolicy<ValueParameter>
		{
		public:
			ValueParameter(Value const &value);
			ValueParameter(Value const &&value);
			~ValueParameter();


			Value const	&getValue() const;

		private:
			Value const &_value;

		};
	}
}

#endif