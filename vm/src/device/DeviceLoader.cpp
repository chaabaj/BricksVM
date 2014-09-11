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

		std::shared_ptr<bricksvm::event::EventThread> DeviceLoader::load(std::string const &name)
		{
			typedef bricksvm::event::EventThread* (*FunctionType)();

			FunctionType fun = _loader.get<FunctionType>(name, "construct");
			return std::shared_ptr<bricksvm::event::EventThread>(fun());
		}
	}
}