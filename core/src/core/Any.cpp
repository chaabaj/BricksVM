#include "core/Any.hpp"

namespace bricksvm
{
    namespace core
    {
        Any::Any()
        {

        }

        template<>
        Any::Any(Any const &other)
        {
            _value = other._value;
        }
        Any::~Any()
        {

        }

    }
}