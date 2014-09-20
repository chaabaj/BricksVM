#include <memory>
#include "${name}/${name}.hpp"

extern "C"
{
    bricksvm::event::EventThread *construct(rapidjson::Value *config)
	{
		return new bricksvm::device::$name(config);
	}
}

namespace bricksvm
{
	namespace device
	{
		$name::$name(rapidjson::Value *config) : bricksvm::event::EventThread("$name")
		{
		}
		
		$name::~$name()
		{
		}
	}
}