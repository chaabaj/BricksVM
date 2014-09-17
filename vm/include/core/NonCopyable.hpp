#ifndef __BRICKSVM_CORE_NONCOPYABLE_HPP__
# define __BRICKSVM_CORE_NONCOPYABLE_HPP__

namespace bricksvm
{
	namespace core
	{
		class NonCopyable
		{
			NonCopyable(NonCopyable const &other) = delete;
			NonCopyable &operator=(NonCopyable const &other) = delete;
		};
	}
}

#endif