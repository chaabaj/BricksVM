#include <fstream>
#include "core/Singleton.hpp"
#include "device/DeviceLoader.hpp"
#include "event/EventThread.hpp"
#include "exception/FileNotFoundException.hpp"
#include "ConfigurationParser.hpp"

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

		rapidjson::Value &devices = root["devices"];

		for (auto it = devices.Begin(); it != devices.End(); ++it)
		{
			this->parseDevice(vm, *it);
		}
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