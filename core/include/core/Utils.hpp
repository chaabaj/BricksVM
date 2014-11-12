#ifndef __BRICKSVM_CORE_UTILS_HPP__
#define __BRICKSVM_CORE_UTILS_HPP__

# include <string>
# include <sstream>

namespace bricksvm
{
    namespace core
    {
        template<typename ExceptionType>
        inline void throwIf(bool val, std::string const &msg)
        {
            if (val)
            {
                throw ExceptionType(msg);
            }
        }

        template<typename Signature>
        struct CountArgs;

        template<typename ResultType, typename ... Args>
        struct CountArgs < ResultType(Args...) >
        {
            static const int value = sizeof...(Args);
        };

        template<typename T>
        class TypeTraits
        {
            template<typename U>
            struct isRefWrapper
            {
                static const bool value = false;
            };

            template<typename U>
            struct isRefWrapper < std::reference_wrapper<U> >
            {
                static const bool value = true;
            };

        public:
            static const bool is_ref_wrapper = isRefWrapper<T>::value;
        };

    }
}

#endif
