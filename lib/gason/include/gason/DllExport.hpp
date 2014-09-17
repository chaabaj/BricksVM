#ifndef __GASON_DLLEXPORT_HPP__
# define __GASON_DLLEXPORT_HPP__

# ifdef WIN32
#  define EXPORT_DLL __declspec(dllexport)
# else
#  define EXPORT_DLL
# endif

#endif