#ifndef __BRICKSVM_CORE_NEWPOLICY_HPP__
# define __BRICKSVM_CORE_NEWPOLICY_HPP__

# include <memory>

namespace bricksvm
{
	namespace core
	{
		template<typename T>
		struct NewPolicy
		{
			template<typename ... Args>
			static std::shared_ptr<T> New(Args&& ... args)
			{
				return std::shared_ptr<T>(new T(args...));
			}
		};
	}
}

#endif