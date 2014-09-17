#ifndef __BRICKSVM_CORE_ICLONABLE_HPP__
# define __BRICKSVM_CORE_ICLONABLE_HPP__

# include <memory>

namespace bricksvm
{
	namespace core
	{
		/// Used for deep copy
		template<typename T>
		class IClonable
		{
		public:
			virtual ~IClonable() {}
			virtual std::shared_ptr<T> clone() const = 0;
		};
	}
}

#endif