#ifndef __BRICKSVM_CORE_UTILS_HPP__
#define __BRICKSVM_CORE_UTILS_HPP__

namespace bricksvm
{
	namespace core
	{
		template<typename Signature>
		struct CountArgs;

		template<typename ResultType, typename ... Args>
		struct CountArgs<ResultType(Args...) >
		{
			static const int value = sizeof...(Args);
		};
	}
}

#endif