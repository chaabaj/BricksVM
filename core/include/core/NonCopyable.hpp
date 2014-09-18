#ifndef __BRICKSVM_CORE_NONCOPYABLE_HPP__
# define __BRICKSVM_CORE_NONCOPYABLE_HPP__

# include "core/DllExport.hpp"

namespace bricksvm
{
	namespace core
	{
		class EXPORT_DLL NonCopyable
		{
			NonCopyable() = default;
			NonCopyable(NonCopyable const &other) = delete;
			NonCopyable &operator=(NonCopyable const &other) = delete;
		};
	}
}

#endif