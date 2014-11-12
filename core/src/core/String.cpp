#include <sstream>
#include <map>
#include <iostream>
#include "core/String.hpp"

namespace bricksvm
{
    namespace core
    {
        uint64_t    getMemSize(std::string const &str)
        {
            static const std::map<std::string, uint32_t>  sizeMap = { { "MB", MemorySize::MB }, 
                                                                      { "KB", MemorySize::KB }, 
                                                                      { "GB", MemorySize::GB } };
            std::stringstream   ss;
            uint64_t            num = 0;
            uint32_t            size = 0;
            uint32_t            i = 0;
            std::string         sizeStr;

            std::cout << num << std::endl;
            for (; isalnum(str[i]) && str[i]; ++i)
            {
                ss << str[i];
            }
            ss >> num;
            ss.clear();


            for (; str[i]; ++i)
            {
                ss << str[i];
            }
            ss >> sizeStr;
            auto it = sizeMap.find(sizeStr);
            if (it != sizeMap.end())
            {
                return num * it->second;
            }
            throw std::runtime_error("Invalid memory size");
        }
    }
}