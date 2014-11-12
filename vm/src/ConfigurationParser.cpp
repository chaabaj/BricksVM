#include <fstream>
#include "core/Singleton.hpp"
#include "device/DeviceLoader.hpp"
#include "event/EventThread.hpp"
#include "exception/FileNotFoundException.hpp"
#include "ConfigurationParser.hpp"
#include "core/String.hpp"
#include "core/Console.hpp"

namespace bricksvm
{
    ConfigurationParser::ConfigurationParser(std::string const &configFile) : _configFile(configFile)
    {
        _rootPath = "../devices";
    }

    ConfigurationParser::~ConfigurationParser()
    {
        
    }

    void ConfigurationParser::parse(VirtualMachine &vm)
    {
        char				buf[4096];
        std::stringstream	jsonStream;
        rapidjson::Document	root;
        std::ifstream		fileStream(_configFile);

        bricksvm::core::Console::log("VM") << "Start parsing configuration file" << std::endl;
        bricksvm::core::Console::log("VM") << "Opening " << _configFile << std::endl;
        if (fileStream.is_open())
        {
            while (!fileStream.eof())
            {
                fileStream.read(buf, 4096);
                jsonStream.write(buf, fileStream.gcount());
            }
            root.Parse(jsonStream.str().c_str());
        }
        else
        {
            throw exception::FileNotFoundException("Cannot find config file");
        }

        std::string const & memSize = root["memSize"].GetString();

        vm.allocateMemory(bricksvm::core::getMemSize(memSize));

        rapidjson::Value &devices = root["devices"];
        bricksvm::core::Console::log("VM") << "Start parsing device configuration" << std::endl;
        for (auto it = devices.Begin(); it != devices.End(); ++it)
        {
            this->parseDevice(vm, *it);
        }
        bricksvm::core::Console::success("VM") << "All device are initialized" << std::endl;
        
    }

    void ConfigurationParser::parseDevice(VirtualMachine &vm, rapidjson::Value &deviceConfig)
    {
        std::string			file;
        rapidjson::Value	*config = nullptr;

        file = deviceConfig["file"].GetString();
        if (deviceConfig.HasMember("config"))
        {
            config = &deviceConfig["config"];
        }
        vm.addDevice(core::Singleton<device::DeviceLoader>::get()->load(file, config));
    }

}