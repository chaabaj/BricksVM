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

        std::shared_ptr<bricksvm::event::EventThread> DeviceLoader::load(std::string const &name, rapidjson::Value *config)
        {
            typedef bricksvm::event::EventThread* (*FunctionType)(rapidjson::Value *config);

                
            FunctionType fun = _loader.get<FunctionType>(name + bricksvm::core::LibraryLoader::getExtension(), "construct");
            return std::shared_ptr<bricksvm::event::EventThread>(fun(config));
        }
    }
}