#include <memory>
#include <iostream>
#include <functional>
#include <cmath>
#include <interpreter/Value.hpp>
#include "exception/InvalidOperationException.hpp"
#include "SimpleCPU/SimpleCPU.hpp"
#include "core/Console.hpp"
#include "exception/InvalidOperationException.hpp"

extern "C"
{
    EXPORT_DLL bricksvm::event::EventThread *construct(rapidjson::Value *config)
    {
        return new bricksvm::device::SimpleCPU(config);
    }
}

namespace bricksvm
{
    namespace device
    {
        SimpleCPU::SimpleCPU(rapidjson::Value *config) : bricksvm::event::ParallelEventThread<4>("SimpleCPU")
        {
            using namespace std::placeholders;

            bricksvm::core::Console::log(this->getName()) << "loading instruction set " << this->getName() << std::endl;
            this->on("scpu_reg_read", std::bind(&SimpleCPU::onReadRegister<RegisterContainerType>, this,
                                                _1, _2, std::ref(_registers)));
            this->on("scpu_reg_write", std::bind(&SimpleCPU::onWriteRegister<RegisterContainerType>, this,
                                                 _1, _2, std::ref(_registers)));
            this->on("scpu_fpreg_read", std::bind(&SimpleCPU::onReadRegister<FloatingRegisterContainerType>, this,
                                                  _1, _2, std::ref(_fpRegisters)));
            this->on("scpu_fpreg_write", std::bind(&SimpleCPU::onWriteRegister<FloatingRegisterContainerType>, this,
                                                    _1, _2, std::ref(_fpRegisters)));
            this->on("scpu_add", std::bind(&SimpleCPU::onAdd, this, _1, _2));
            this->on("scpu_sub", std::bind(&SimpleCPU::onSub, this, _1, _2));
            this->on("scpu_mul", std::bind(&SimpleCPU::onMultiply, this, _1, _2));
            this->on("scpu_div", std::bind(&SimpleCPU::onDivide, this, _1, _2));
            this->on("scpu_mod", std::bind(&SimpleCPU::onModulo, this, _1, _2));
            this->on("scpu_or", std::bind(&SimpleCPU::onBinaryOr, this, _1, _2));
            this->on("scpu_and", std::bind(&SimpleCPU::onBinaryAnd, this, _1, _2));
            this->on("scpu_xor", std::bind(&SimpleCPU::onBinaryXor, this, _1, _2));
            this->on("scpu_lshift", std::bind(&SimpleCPU::onBinaryLeftShift, this, _1, _2));
            this->on("scpu_rshift", std::bind(&SimpleCPU::onBinrayRightShift, this, _1, _2));
            this->on("scpu_cmp", std::bind(&SimpleCPU::onCompare, this, _1, _2));
            this->on("scpu_jne", std::bind(&SimpleCPU::onJumpNotEqual, this, _1, _2));
            this->on("scpu_jlt", std::bind(&SimpleCPU::onJumpLowerThan, this, _1, _2));
            this->on("scpu_jgt", std::bind(&SimpleCPU::onJumpGreaterThan, this, _1, _2));
            this->on("scpu_je", std::bind(&SimpleCPU::onJumpEqual, this, _1, _2));
            this->on("scpu_sqrt", std::bind(&SimpleCPU::onSqrt, this, _1, _2));
            this->on("scpu_pow", std::bind(&SimpleCPU::onPower, this, _1, _2));
            this->on("scpu_log", std::bind(&SimpleCPU::onLogarithm, this, _1, _2));
            this->on("scpu_sin", std::bind(&SimpleCPU::onSinus, this, _1, _2));
            this->on("scpu_cos", std::bind(&SimpleCPU::onCosinus, this, _1, _2));
            this->on("scpu_tan", std::bind(&SimpleCPU::onTangente, this, _1, _2));
            this->on("scpu_add_vec", std::bind(&SimpleCPU::onAddVector, this, _1, _2));
            this->on("scpu_mul_vec", std::bind(&SimpleCPU::onMulVector, this, _1, _2));
            this->on("scpu_sub_vec", std::bind(&SimpleCPU::onSubVector, this, _1, _2));
            this->on("scpu_div_vec", std::bind(&SimpleCPU::onDivVector, this, _1, _2));
            bricksvm::core::Console::success(this->getName()) << this->getName() << " initialized" << std::endl;
        }

        SimpleCPU::~SimpleCPU()
        {
            bricksvm::core::Console::log(this->getName()) << "closed" << std::endl;
        }

        void SimpleCPU::onAdd(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            this->onCompute(self, msg, [](interpreter::Value const &val1, interpreter::Value const &val2)
            {
                return val1 + val2;
            });
        }

        void SimpleCPU::onSub(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            this->onCompute(self, msg, [](interpreter::Value const &val1, interpreter::Value const &val2)
            {
                return val1 - val2;
            });
        }

        void SimpleCPU::onMultiply(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            this->onCompute(self, msg, [](interpreter::Value const &val1, interpreter::Value const &val2)
            {
                return val1 * val2;
            });
        }

        void SimpleCPU::onDivide(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            this->onCompute(self, msg, [](interpreter::Value const &val1, interpreter::Value const &val2)
            {
                return val1 / val2;
            });
        }

        void SimpleCPU::onModulo(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            this->onCompute(self, msg, [](interpreter::Value const &val1, interpreter::Value const &val2)
            {
                return val1 % val2;
            });
        }

        void SimpleCPU::onBinaryOr(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            this->onCompute(self, msg, [](interpreter::Value const &val1, interpreter::Value const &val2)
            {
                return val1 | val2;
            });
        }

        void SimpleCPU::onBinaryAnd(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            this->onCompute(self, msg, [](interpreter::Value const &val1, interpreter::Value const &val2)
            {
                return val1 & val2;
            });
        }

        void SimpleCPU::onBinaryXor(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            this->onCompute(self, msg, [](interpreter::Value const &val1, interpreter::Value const &val2)
            {
                return val1 ^ val2;
            });
        }

        void SimpleCPU::onBinaryLeftShift(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            this->onCompute(self, msg, [](interpreter::Value const &val1, interpreter::Value const &val2)
            {
                return val1 << val2;
            });
        }

        void SimpleCPU::onBinrayRightShift(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            this->onCompute(self, msg, [](interpreter::Value const &val1, interpreter::Value const &val2)
            {
                return val1 >> val2;
            });
        }

        void SimpleCPU::onJumpLowerThan(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            this->onJumpCmp(self, msg, [](int val)
            {
                return val == Lower;
            });
        }

        void SimpleCPU::onJumpGreaterThan(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            this->onJumpCmp(self, msg, [](int val)
            {
                return val == Greater;
            });
        }

        void SimpleCPU::onJumpEqual(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            this->onJumpCmp(self, msg, [](int val)
            {
                return val == Equal;
            });
        }

        void SimpleCPU::onJumpNotEqual(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            this->onJumpCmp(self, msg, [](int val)
            {
                return val != Equal;
            });
        }

        void SimpleCPU::onCompare(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            interpreter::Value              &val1 = msg.getParameter<interpreter::Value>(3);
            interpreter::Value              &val2 = msg.getParameter<interpreter::Value>(4);
            CompareState                    state;

            if (val1 > val2)
            {
                state = Greater;
            }
            else if (val1 < val2)
            {
                state = Lower;
            }
            else
            {
                state = Equal;
            }
            src.emit("instruction:finished", self, progId, interpreter::Value(static_cast<int>(state)));
        }

        void SimpleCPU::onSqrt(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            interpreter::Value              &val = msg.getParameter<interpreter::Value>(3);

            src.emit("instruction:finished", self,progId, _mathUnit.sqrt(val));
        }

        void SimpleCPU::onSinus(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            interpreter::Value              &val = msg.getParameter<interpreter::Value>(3);

            src.emit("instruction:finished", self, progId, _mathUnit.sin(val));
        }

        void SimpleCPU::onCosinus(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            interpreter::Value              &val = msg.getParameter<interpreter::Value>(3);

            src.emit("instruction:finished", self, progId, _mathUnit.cos(val));

        }

        void SimpleCPU::onTangente(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            interpreter::Value              &val = msg.getParameter<interpreter::Value>(3);

            src.emit("instruction:finished", self, progId, _mathUnit.tan(val));
        }

        void SimpleCPU::onPower(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            interpreter::Value              &val1 = msg.getParameter<interpreter::Value>(3);
            interpreter::Value              &val2 = msg.getParameter<interpreter::Value>(4);

            src.emit("instruction:finished", self, progId, _mathUnit.pow(val1, val2));
        }

        void SimpleCPU::onLogarithm(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            interpreter::Value              &val = msg.getParameter<interpreter::Value>(3);

            src.emit("instruction:finished", self, progId, _mathUnit.log(val));
        }

        void SimpleCPU::onAddVector(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            Memory                          &memory = msg.getParameter<Memory>(1);
            std::string                     progId = msg.getParameter<std::string>(2);
            uint64_t                        vecAddr1 = msg.getParameter<interpreter::Value>(3);
            uint64_t                        vecAddr2 = msg.getParameter<interpreter::Value>(4);
            uint64_t                        destAddr = msg.getParameter<interpreter::Value>(5);
            uint8_t                         vecSize = msg.getParameter<interpreter::Value>(6);

            try
            {
                _mathUnit.addVector(memory, progId, vecAddr1, vecAddr2, destAddr, vecSize);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &err)
            {
                src.emit("instruction:error", self, progId, std::string(err.what()));
            }
        }

        void SimpleCPU::onSubVector(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            Memory                          &memory = msg.getParameter<Memory>(1);
            std::string                     progId = msg.getParameter<std::string>(2);
            uint64_t                        vecAddr1 = msg.getParameter<interpreter::Value>(3);
            uint64_t                        vecAddr2 = msg.getParameter<interpreter::Value>(4);
            uint64_t                        destAddr = msg.getParameter<interpreter::Value>(5);
            uint8_t                         vecSize = msg.getParameter<interpreter::Value>(6);

            try
            {
                _mathUnit.subVector(memory, progId, vecAddr1, vecAddr2, destAddr, vecSize);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &err)
            {
                src.emit("instruction:error", self, progId, std::string(err.what()));
            }
        }

        void SimpleCPU::onMulVector(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            Memory                          &memory = msg.getParameter<Memory>(1);
            std::string                     progId = msg.getParameter<std::string>(2);
            uint64_t                        vecAddr1 = msg.getParameter<interpreter::Value>(3);
            uint64_t                        vecAddr2 = msg.getParameter<interpreter::Value>(4);
            uint64_t                        destAddr = msg.getParameter<interpreter::Value>(5);
            uint8_t                         vecSize = msg.getParameter<interpreter::Value>(6);

            try
            {
                _mathUnit.mulVector(memory, progId, vecAddr1, vecAddr2, destAddr, vecSize);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &err)
            {
                src.emit("instruction:error", self, progId, std::string(err.what()));
            }
        }

        void SimpleCPU::onDivVector(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            Memory                          &memory = msg.getParameter<Memory>(1);
            std::string                     progId = msg.getParameter<std::string>(2);
            uint64_t                        vecAddr1 = msg.getParameter<interpreter::Value>(3);
            uint64_t                        vecAddr2 = msg.getParameter<interpreter::Value>(4);
            uint64_t                        destAddr = msg.getParameter<interpreter::Value>(5);
            uint8_t                         vecSize = msg.getParameter<interpreter::Value>(6);

            try
            {
                _mathUnit.divVector(memory, progId, vecAddr1, vecAddr2, destAddr, vecSize);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &err)
            {
                src.emit("instruction:error", self, progId, std::string(err.what()));
            }
        }

    }

    
}