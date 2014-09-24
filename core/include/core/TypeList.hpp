#ifndef __BRICKSVM_CORE_TYPELIST_HPP__
# define __BRICKSVM_CORE_TYPELIST_HPP__

namespace bricksvm
{
    namespace core
    {
        struct NullType {};

        template<typename T, typename U>
        struct PairType
        {
            typedef T   First;
            typedef U   Second;
        };

        template<typename T, typename U>
        struct TypeList
        {
            typedef T   Type;
            typedef U   Next;
        };

        template<typename ... Args>
        struct MakeTypeList
        {

        };
    }
}

#endif