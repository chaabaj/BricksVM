#ifndef __BRICKSVM_CORE_LIBRARYLOADER_HPP__
# define __BRICKSVM_CORE_LIBRARYLOADER_HPP__

# include <type_traits>
# include <map>
# include <string>
# include "core/constants.hpp"

# ifdef WIN32
#  include <Windows.h>
# elif __gnu_linux__
#  include <dlfnc.h>
#endif

namespace bricksvm
{
	namespace core
	{
		class LibraryLoader
		{
		public:
			typedef std::conditional<WINDOWS, HMODULE, void*>::type	DynamicLibraryType;

			LibraryLoader();

			~LibraryLoader();

			template<typename FunctionType>
			FunctionType	get(std::string const &libraryName, std::string const &name)
			{
				auto it = _libraries.find(libraryName);

				if (it != _libraries.end())
				{
					DynamicLibraryType lib = it->second;

					# ifdef WIN32
						return reinterpret_cast<FunctionType>(GetProcAddress(_libraries[libraryName], name.c_str()));
					# elif __gnu_linux__
						return reinterpret_cast<FunctionType>(dlsym(_libraries[libraryName], name.c_str()));
					# endif
				}
				this->load(libraryName);
				return this->get<FunctionType>(libraryName, name);
			}
				

		private:

			void load(std::string const &libraryName);

			void unload(DynamicLibraryType &lib);

		private:
			std::map<std::string, DynamicLibraryType>	_libraries;
		};
	}
}

#endif