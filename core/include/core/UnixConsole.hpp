#ifndef __BRICKSVM_CORE_UNIXCONSOLE_HPP__
# define __BRICKSVM_CORE_UNIXCONSOLE_HPP__

# include <ostream>
# include <string>


namespace bricksvm
{
    namespace core
    {
        class  UnixConsole
        {
        public:
            
            static std::ostream &success(std::string const &deviceName);
            static std::ostream &log(std::string const &deviceName);
            static std::ostream &error(std::string const &deviceName);

        private:
            static const std::string    Red;
            static const std::string    Green;
            static const std::string    White;
            static const std::string    Blue;
        };
    }
}

#endif