#include "core/LibraryLoader.hpp"

namespace bricksvm
{
    namespace core
    {
        LibraryLoader::LibraryLoader()
        {

        }

        LibraryLoader::~LibraryLoader()
        {
            for (auto it : _libraries)
            {
                unload(it.second);
            }
        }


        void LibraryLoader::load(std::string const &libName)
        {
            DynamicLibraryType	library;

            #ifdef WIN32
                library = LoadLibrary(libName.c_str());
            #elif __gnu_linux__
                library = dlopen(libName.c_str(), RTLD_LAZY);
            #endif
            if (!library)
                throw std::runtime_error("Cannot load library : " + libName);
            _libraries[libName] = library;
        }

        void LibraryLoader::unload(DynamicLibraryType &lib)
        {
            #ifdef WIN32
                FreeLibrary(lib);
            #elif __gnu_linux__
                dlclose(lib);
            #endif
        }
    }
}
