#ifndef __BRICKSVM_CORE_SINGLETON_HPP__
# define __BRICKSVM_CORE_SINGLETON_HPP__

# include "core/DllExport.hpp"

namespace bricksvm
{
    namespace core
    {
        template<typename T>
        class EXPORT_DLL Singleton
        {
        public:

            static T *get()
            {
                if (_instance == NULL)
                {
                    _instance = new T();
                    atexit(Singleton<T>::release);
                }
                return _instance;
            }

        private:

            static void release()
            {
                delete _instance;
            }

            Singleton();
            ~Singleton();
        private:
            static T    *_instance;
        };

        template<typename T>
        T *Singleton<T>::_instance = NULL;
    }

}



#endif