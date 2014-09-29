#ifndef __BRICKSVM_DEVICE_DEVICELOADER_HPP__
# define __BRICKSVM_DEVICE_DEVICELOADER_HPP__

# include "core/LibraryLoader.hpp"
# include "event/EventThread.hpp"
# include "rapidjson/rapidjson.h"
# include "rapidjson/document.h"


namespace bricksvm
{
    namespace device
    {
        class DeviceLoader
        {
        public:

            DeviceLoader();
            ~DeviceLoader();

            std::shared_ptr<bricksvm::event::EventThread>	load(std::string const &name,
                                                                 rapidjson::Value *val);

           
        private:
            bricksvm::core::LibraryLoader   _loader;

        };
    }
}

#endif