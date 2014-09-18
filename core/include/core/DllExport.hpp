#ifndef __BRICKSVM_CORE_DLLEXPORT_HPP__
# define __BRICKSVM_CORE_DLLEXPORT_HPP__

# ifdef WIN32
#  define EXPORT_DLL __declspec(dllexport)
# else
#  define EXPORT_DLL
# endif

#endif