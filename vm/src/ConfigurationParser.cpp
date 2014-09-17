#include <fstream>
#include "core/Singleton.hpp"
#include "device/DeviceLoader.hpp"
#include "event/EventThread.hpp"
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
		char				*endPtr;
		char				buf[4096];
		std::stringstream	jsonStream;
		std::ifstream		fileStream(_configFile);
		
		if (fileStream.is_open())
		{
			std::cout << "Config file opened" << std::endl;
			while (!fileStream.eof())
			{
				fileStream.read(buf, 4096);
				jsonStream.write(buf, fileStream.gcount());
			}
			
			char *src = const_cast<char*>(jsonStream.str().c_str());
			std::cout << "json src" << jsonStream.str() << std::endl;
			gason::JsonValue		root;
			gason::JsonAllocator	allocator;

			gason::JsonParseStatus status = gason::jsonParse(src, &endPtr, &root, allocator);

			if (status == gason::JSON_PARSE_OK)
			{
				std::cout << "ok" << std::endl;
				this->parse(vm, root);
			}
			else
			{
				throw std::runtime_error("Bad json file");
			}
		}
	}

	void ConfigurationParser::parse(VirtualMachine &vm, gason::JsonValue &val)
	{
		switch (val.getTag())
		{
			case gason::JSON_TAG_OBJECT:
			{
				for (auto obj : val)
				{
					if (obj->key == "devices")
					{
						if (obj->value.getTag() == gason::JSON_TAG_ARRAY)
						{
							this->parseDevice(vm, obj->value);
						}
						else
						{
							throw std::runtime_error("devices must be an object array");
						}
					}
				}
			}
		}
	}

	void ConfigurationParser::parseDevice(VirtualMachine &vm, gason::JsonValue &devicesConfig)
	{
		std::string							libName;
		std::shared_ptr<event::EventThread>	device;
		gason::JsonNode						*config;
		

		for (auto deviceConfig : devicesConfig)
		{
			if (deviceConfig->value.getTag() == gason::JSON_TAG_OBJECT)
			{
				libName = "";
				for (auto obj : deviceConfig->value)
				{
					if (obj->key == "path")
					{
						libName = obj->value.toString();
					}
					else if (obj->key == "config")
					{
						config = obj;
					}
				}
				if (libName == "")
				{
					throw std::runtime_error("Missing path for the device");
				}
				device = core::Singleton<device::DeviceLoader>::get()->load(libName, config);
				vm.addDevice(device);
			}
		}
	}

}