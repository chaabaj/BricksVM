#include "interpreter/AParameter.hpp"

namespace bricksvm
{
    namespace interpreter
    {
        AParameter::AParameter(AParameter::Type const &type) : _type(type)
        {

        }

        AParameter::~AParameter()
        {

        }

        AParameter::Type const &AParameter::getType() const
        {
            return _type;
        }
    }
}