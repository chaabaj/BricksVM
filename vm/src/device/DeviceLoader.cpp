#include "device/DeviceLoader.hpp"

namespace bricksvm
{
	namespace device
	{
		DeviceLoader::DeviceLoader()
		{

		}

		DeviceLoader::~DeviceLoader()
		{

		}

		std::shared_ptr<bricksvm::event::EventThread> DeviceLoader::load(std::string const &name, rapidjson::Value *val)
		{
			typedef bricksvm::event::EventThread* (*FunctionType)(rapidjson::Value *val);

			FunctionType fun = _loader.get<FunctionType>(name, "construct");
			return std::shared_ptr<bricksvm::event::EventThread>(fun(val));
		}
	}
}