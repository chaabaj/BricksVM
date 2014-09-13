#ifndef __BRICKSVM_CONFIGURATIONPARSER_HPP__
# define __BRICKSVM_CONFIGURATIONPARSER_HPP__

# include "gason/gason.hpp"
# include "VirtualMachine.hpp"

namespace bricksvm
{
	class ConfigurationParser
	{
	public:
		ConfigurationParser(std::string const &configFile);
		~ConfigurationParser();

		void parse(VirtualMachine &vm);

	private:
		void parse(VirtualMachine &vm, gason::JsonValue &val);

		void parseDevice(VirtualMachine &vm, gason::JsonValue &val);

	private:
		std::string const	_configFile;
		std::string			_rootPath;
	};
}

#endif