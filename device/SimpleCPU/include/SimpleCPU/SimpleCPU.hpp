#ifndef __BRICKSVM_DEVICE_SIMPLECPU_HPP__
# define __BRICKSVM_DEVICE_SIMPLECPU_HPP__

# include <map>
# include <array>
# include "interpreter/Value.hpp"
# include "rapidjson/document.h"
# include "core/DllExport.hpp"
# include "event/ParallelEventThread.hpp"
# include "SimpleCPU/MathUnit.hpp"

namespace bricksvm
{
	namespace device
	{
		class EXPORT_DLL SimpleCPU : public bricksvm::event::ParallelEventThread<4>
		{
			public:
                enum CompareState
                {
                    Lower = -1,
                    Equal = 0,
                    Greater = 1
                };
			
				SimpleCPU(rapidjson::Value *config);
				~SimpleCPU();

        private:

            void onAdd(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onSub(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onMultiply(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onDivide(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onModulo(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onBinaryOr(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onBinaryAnd(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onBinaryXor(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onBinaryLeftShift(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onBinrayRightShift(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onJumpLowerThan(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onJumpGreaterThan(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onJumpEqual(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onJumpNotEqual(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onSqrt(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onCompare(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onSinus(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onCosinus(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            
            void onTangente(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onPower(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onLogarithm(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onAddVector(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onSubVector(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onMulVector(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onDivVector(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            template<typename CompareFunctionType>
            void onJumpCmp(bricksvm::event::EventThread &self, bricksvm::event::Message &msg,
                           CompareFunctionType &&compareFn)
            {
                bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
                std::string                     progId = msg.getParameter<std::string>(2);
                int                             result = msg.getParameter<interpreter::Value>(3);
                interpreter::Value              jmpAddress = msg.getParameter<interpreter::Value>(4);

                if (compareFn(result))
                {
                    src.emit("vm_jmp", self, NULL, progId, jmpAddress);
                }
                else
                {
                    src.emit("instruction:finished", self, progId, interpreter::Value(0));
                }
            }

            template<typename OperationFunctionType>
            void onCompute(bricksvm::event::EventThread &self, bricksvm::event::Message &msg,
                           OperationFunctionType &&opFun)
            {
                bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
                std::string                     progId = msg.getParameter<std::string>(2);
                interpreter::Value              val1 = msg.getParameter<interpreter::Value>(3);
                interpreter::Value              val2 = msg.getParameter<interpreter::Value>(4);

                try
                {

                    src.emit("instruction:finished", self, progId, opFun(val1, val2));
                }
                catch (bricksvm::exception::InvalidOperationException &err)
                {
                    src.emit("instruction:error", self, progId, std::string(err.what()));
                }
            }

            template<typename RegisterContainerType>
            void onReadRegister(bricksvm::event::EventThread &self, bricksvm::event::Message &msg, 
                                RegisterContainerType &registers)
            {
                bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
                std::string                     progId = msg.getParameter<std::string>(2);
                int                             index = msg.getParameter<interpreter::Value>(3);

                if (index >= 0 && index < 16)
                {
                    interpreter::Value  val(registers[progId][index]);
                    src.emit("instruction:finished", self, progId, val);
                }
                else
                {
                    src.emit("instruction:error", self, progId, "Invalid register");
                }
            }

            template<typename RegisterContainerType>
            void onWriteRegister(bricksvm::event::EventThread &self, bricksvm::event::Message &msg,
                                 RegisterContainerType &registers)
            {
                typedef typename RegisterContainerType::mapped_type     MappedType;
                typedef typename MappedType::value_type                 ValueType;

                bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
                std::string                     progId = msg.getParameter<std::string>(2);
                int                             index = msg.getParameter<interpreter::Value>(3);
                ValueType                       val = msg.getParameter<interpreter::Value>(4);

                
                if (index >= 0 && index < 16)
                {
                    registers[progId][index] = val;
                    src.emit("instruction:finished", self, progId, interpreter::Value(0));
                }
                else
                {
                    src.emit("instruction:error", self, progId, "Invalid register");
                }
            }

        private:
            typedef std::map<std::string, std::array<long long int, 16> >   RegisterContainerType;
            typedef std::map<std::string, std::array<double, 16> >          FloatingRegisterContainerType;

            RegisterContainerType           _registers;
            FloatingRegisterContainerType   _fpRegisters;
            MathUnit                        _mathUnit;
		};
	}
}

#endif