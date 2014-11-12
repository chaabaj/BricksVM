#ifndef __BRICKSVM_DEVICE_MATHUNIT_HPP__
# define __BRICKSVM_DEVICE_MATHUNIT_HPP__

# include <functional>
# include "interpreter/Value.hpp"
# include "device/Memory.hpp"

namespace bricksvm
{
    namespace device
    {
        class MathUnit
        {
        public:
            interpreter::Value  sqrt(interpreter::Value const &val1) const;
            interpreter::Value  pow(interpreter::Value const &val1, interpreter::Value const &val2) const;
            interpreter::Value  log(interpreter::Value const &val1) const;
            interpreter::Value  sin(interpreter::Value const &val1) const;
            interpreter::Value  cos(interpreter::Value const &val1) const;
            interpreter::Value  tan(interpreter::Value const &val1) const;
            void                addVector(Memory &memory,
                                          std::string const &progId,
                                          uint64_t vecAddr1, 
                                          uint64_t vecAddr2, 
                                          uint64_t destAddr,
                                          uint8_t vecSize) const;
            void                mulVector(Memory &memory,
                                          std::string const &progId,
                                          uint64_t vecAddr1, 
                                          uint64_t vecAddr2, 
                                          uint8_t vecSize, 
                                          uint64_t destAddr) const;
            void                subVector(Memory &memory,
                                          std::string const &progId,
                                          uint64_t vecAddr1,
                                          uint64_t vecAddr2,
                                          uint8_t vecSize,
                                          uint64_t destAddr) const;
            void                divVector(Memory &memory, 
                                          std::string const &progId,
                                          uint64_t vecAddr1, 
                                          uint64_t vecAddr2, 
                                          uint8_t vecSize, 
                                          uint64_t destAddr) const;

        private:
            template<typename Operation>
            void    vecOperation(Memory &memory,
                                 std::string const &progId,
                                 uint64_t vecAddr1,
                                 uint64_t vecAddr2,
                                 uint8_t vecSize,
                                 uint64_t destAddr) const
            {
                std::vector<double> result;
                std::vector<double> vec1;
                std::vector<double> vec2;

                result.resize(vecSize);
                vec1.resize(vecSize);
                vec2.resize(vecSize);
                memory.read(progId, vecAddr1, &vec1[0], vecSize);
                memory.read(progId, vecAddr2, &vec2[0], vecSize);
                for (uint8_t i = 0; i < vecSize; ++i)
                {
                    result[i] = Operation::compute(vec1[i], vec2[i]);
                }
                memory.write(progId, destAddr, &result[0], vecSize);
            }
        };
    }
}

#endif