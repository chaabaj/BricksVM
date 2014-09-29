#include <memory>
#include <iostream>
#include <functional>
#include <interpreter/Value.hpp>
#include "exception/InvalidOperationException.hpp"
#include "SimpleCPU/SimpleCPU.hpp"

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
        SimpleCPU::SimpleCPU(rapidjson::Value *config) : bricksvm::event::EventThread("SimpleCPU")
        {
            using namespace std::placeholders;

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
        }

        SimpleCPU::~SimpleCPU()
        {
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
            std::string                     progId = msg.getParameter<std::string>(1);
            interpreter::Value              &val1 = msg.getParameter<interpreter::Value>(2);
            interpreter::Value              &val2 = msg.getParameter<interpreter::Value>(3);
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
            src.emit("instruction:finished", std::ref(self), progId, interpreter::Value(static_cast<int>(state)));
        }
    }
}