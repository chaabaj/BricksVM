#ifndef __BRICKSVM_CORE_ABSTRACTCONSOLE_HPP__
# define __BRICKSVM_CORE_ABSTRACTCONSOLE_HPP__

# include <string>

namespace bricksvm
{
    namespace core
    {
        class AbstractConsole
        {
        public:
            virtual ~AbstractConsole() {}
            virtual void success(std::string const &deviceName, std::string const &msg) const = 0;
            virtual void log(std::string const &deviceName, std::string const &msg) const = 0;
            virtual void error(std::string const &deviceName, std::string const &msg) const = 0;

        };

    }
}

#endif