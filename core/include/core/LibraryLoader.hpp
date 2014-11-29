#ifndef __BRICKSVM_CORE_LIBRARYLOADER_HPP__
# define __BRICKSVM_CORE_LIBRARYLOADER_HPP__

# include <type_traits>
# include <map>
# include <string>
# include "core/constants.hpp"
# include "core/DllExport.hpp"

# ifdef WIN32
#  include <Windows.h>
# elif __gnu_linux__
   typedef int HMODULE;
#  include <dlfcn.h>
#endif


namespace bricksvm
{
    namespace core
    {

      
        class EXPORT_DLL LibraryLoader
        {
        public:

            typedef std::conditional<WINDOWS, HMODULE, void*>::type DynamicLibraryType;

            LibraryLoader();

            ~LibraryLoader();

            static inline std::string getExtension()
            {
                # ifdef WIN32
                    return ".dll";
                # elif __gnu_linux__
                    return ".so";
                # else
                    return "";
                #endif
            }
	   
	    static inline std::string getLibraryPrefix()
	    {
               # ifdef WIN32
                    return "";
                # elif __gnu_linux__
                    return "lib";
                # else
                    return "";
                #endif
	    }

            template<typename FunctionType>
            FunctionType	get(std::string const &libraryName, std::string const &name)
            {
                FunctionType    fun;
                auto            it = _libraries.find(libraryName);
            
                if (it != _libraries.end())
                {
                    DynamicLibraryType lib = it->second;

                    # ifdef WIN32
                        fun = reinterpret_cast<FunctionType>(GetProcAddress(lib, name.c_str())); 
                    # elif __gnu_linux__
                        fun = reinterpret_cast<FunctionType>(dlsym(lib, name.c_str()));
                    # endif

                    if (!fun)
                    {
                        throw std::runtime_error(LibraryLoader::getError());
                    }
                    return fun;
                }
                this->load(libraryName);
                return this->get<FunctionType>(libraryName, name);
            }


        private:

                static inline std::string const getError()
                {
                    #ifdef WIN32
                        return "Windows crap here";
                    #elif __gnu_linux__
                        return std::string(dlerror());
                    #endif
                }


            
            void load(std::string const &libraryName);

            void unload(DynamicLibraryType &lib);

        private:
            std::map<std::string, DynamicLibraryType>   _libraries;
        };
    }
}

#endif
