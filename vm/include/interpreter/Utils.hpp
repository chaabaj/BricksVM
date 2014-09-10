#ifndef __BRICKSVM_INTERPRETER_UTILS_HPP__
# define __BRICKSVM_INTERPRETER_UTILS_HPP__

# include <vector>
# include <memory>
# include "interpreter/Instruction.hpp"
# include "interpreter/ValueParameter.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		template<typename ... Args>
		Instruction::ParameterContainerType	makeParameters(Args&& ... args)
		{
			Instruction::ParameterContainerType	params;

			makeParameters(params, args...);
			return params;
		}

		template<typename ArgType, typename ... Args>
		void makeParameters(Instruction::ParameterContainerType &params, ArgType &&arg, Args&& ... args)
		{
			auto newParam = std::shared_ptr<AParameter>(new ValueParameter(Value(arg)));

			params.push_back(newParam);
			makeParameters(params, args...);
		}

		template<typename ArgType>
		void makeParameters(Instruction::ParameterContainerType &params, ArgType &&arg)
		{
			auto newParam = std::shared_ptr<AParameter>(new ValueParameter(Value(arg)));

			params.push_back(newParam);
		}
	}
}

#endif