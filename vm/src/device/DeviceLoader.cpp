#include "device/DeviceLoader.hpp"
#include "core/Console.hpp"

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

        std::shared_ptr<bricksvm::event::EventThread> DeviceLoader::load(std::string const &name, rapidjson::Value *config)
        {
	  using namespace bricksvm;
            typedef bricksvm::event::EventThread* (*FunctionType)(rapidjson::Value *config);

	    std::string libName = name + core::LibraryLoader::getExtension();

            core::Console::log("VM") << "Load device : " << name << std::endl;
            FunctionType fun = _loader.get<FunctionType>(libName, "construct");
            return std::shared_ptr<event::EventThread>(fun(config));
        }
    }
}
