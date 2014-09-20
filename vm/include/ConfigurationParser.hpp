#ifndef __BRICKSVM_CONFIGURATIONPARSER_HPP__
# define __BRICKSVM_CONFIGURATIONPARSER_HPP__

# include "VirtualMachine.hpp"
# include "rapidjson/rapidjson.h"
# include "rapidjson/document.h"

namespace bricksvm
{
	class ConfigurationParser
	{
	public:
		ConfigurationParser(std::string const &configFile);
		~ConfigurationParser();

		void parse(VirtualMachine &vm);

	private:

		void parseDevice(VirtualMachine &vm, rapidjson::Value &deviceConfig);

	private:
		std::string const	_configFile;
		std::string			_rootPath;
	};
}

#endif