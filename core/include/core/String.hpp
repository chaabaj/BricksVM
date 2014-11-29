#ifndef __BRICKSVM_CORE_STRING_HPP__
# define __BRICKSVM_CORE_STRING_HPP__

# include <string>
# include <cstdint>
# include <sstream>
# include "core/DllExport.hpp"


namespace bricksvm
{
    namespace core
    {
        enum MemorySize
        {
            KB = 1000,
            MB = KB * 1000,
            GB = MB * 1000
        };

        EXPORT_DLL uint64_t  getMemSize(std::string const &str);
        template<typename T>
        std::string toString(T const &value)
        {
            std::stringstream   stream;

            stream << value;
            return stream.str();
        }
        
        template<typename ... U>
        std::string append(std::stringstream &stream, U&& ... values)
        {
            return append(stream);
        }
        
        template<typename T, typename ... U>
        std::string append(std::stringstream &stream, T const &&value, U&& ... values)
        {
            stream << value;
            
            return append(stream, values...);
        }
        
        template<typename T>
        std::string append(std::stringstream &stream, T const &&value)
        {
            stream << value;
            
            return stream.str();
        }
        
        template<typename ... U>
        std::string stringBuilder(U&& ... values)
        {
            std::stringstream   stream;
            
            return append(stream, values...);
        }
        
        
        
        template<typename T>
        T convert(std::string const &value)
        {
            std::stringstream stream;
            T convertedValue;

            stream << value;
            stream >> convertedValue;
            return (convertedValue);
        }
    }
}

#endif