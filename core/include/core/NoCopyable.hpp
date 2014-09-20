#ifndef __BRICKSVM_CORE_NONCOPYABLE_HPP__
# define __BRICKSVM_CORE_NONCOPYABLE_HPP__

# include "core/DllExport.hpp"

namespace bricksvm
{
	namespace core
	{
		class EXPORT_DLL NoCopyable
		{
			NoCopyable() = default;
			NoCopyable(NoCopyable const &other) = delete;
			NoCopyable &operator=(NoCopyable const &other) = delete;
		};
	}
}

#endif