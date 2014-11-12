#include <cmath>
#include "core/Computation.hpp"
#include "SimpleCPU/MathUnit.hpp"

namespace bricksvm
{
    namespace device
    {
        interpreter::Value  MathUnit::sqrt(interpreter::Value const &val1) const
        {
            double  result;

            result = std::sqrt(val1.as<double>());
            return interpreter::Value(result);
        }

        interpreter::Value  MathUnit::pow(interpreter::Value const &val1, interpreter::Value const &val2) const
        {
            double  result;

            result = std::pow(val1.as<double>(), val2.as<double>());
            return interpreter::Value(result);
        }

        interpreter::Value  MathUnit::log(interpreter::Value const &val) const
        {
            double  result;

            result = std::log(val.as<double>());
            return interpreter::Value(result);
        }

        interpreter::Value  MathUnit::sin(interpreter::Value const &val) const
        {
            double  result;

            result = std::sin(val.as<double>());
            return interpreter::Value(result);
        }

        interpreter::Value  MathUnit::cos(interpreter::Value const &val) const
        {
            double  result;

            result = std::sin(val.as<double>());
            return interpreter::Value(result);
        }

        interpreter::Value  MathUnit::tan(interpreter::Value const &val) const
        {
            double  result;

            result = std::tan(val.as<double>());
            return interpreter::Value(result);
        }

        void    MathUnit::addVector(Memory &memory, 
                                 std::string const &progId,
                                 uint64_t vecAddr1, 
                                 uint64_t vecAddr2, 
                                 uint64_t destAddr, 
                                 uint8_t vecSize) const
        {
            this->vecOperation<bricksvm::core::Add<double> >(memory, progId, vecAddr1, vecAddr2, destAddr, vecSize);
        }

        void    MathUnit::mulVector(Memory &memory,
                                    std::string const &progId,
                                    uint64_t vecAddr1,
                                    uint64_t vecAddr2,
                                    uint8_t vecSize, 
                                    uint64_t destAddr) const
        {
            this->vecOperation<bricksvm::core::Multiply<double> >(memory, progId, vecAddr1, vecAddr2, destAddr, vecSize);
        }

        void    MathUnit::subVector(Memory &memory,
                                    std::string const &progId,
                                    uint64_t vecAddr1,
                                    uint64_t vecAddr2,
                                    uint8_t vecSize,
                                    uint64_t destAddr) const
        {
            this->vecOperation<bricksvm::core::Substract<double> >(memory, progId, vecAddr1, vecAddr2, destAddr, vecSize);
        }

        void    MathUnit::divVector(Memory &memory,
                                    std::string const &progId,
                                    uint64_t vecAddr1,
                                    uint64_t vecAddr2,
                                    uint8_t vecSize,
                                    uint64_t destAddr) const
        {
            this->vecOperation<bricksvm::core::Divide<double> >(memory, progId, vecAddr1, vecAddr2, destAddr, vecSize);
        }
    }
}