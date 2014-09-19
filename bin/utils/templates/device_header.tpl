#ifndef __BRICKSVM_DEVICE_${upper_name} _HPP__
# define __BRICKSVM_DEVICE_${upper_name}_HPP__

# include "rapidjson/Document.h"
# include "core/DllExport.hpp"
# include "event/EventThread.hpp"

namespace bricksvm
{
	namespace device
	{
		class EXPORT_DLL $name : public bricksvm::event::EventThread
		{
			public:
			
				$name(rapidjson::Value *config);
				~$name();
		};
	}
}

#endif