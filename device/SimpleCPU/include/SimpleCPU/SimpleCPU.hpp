#ifndef __BRICKSVM_DEVICE_SIMPLECPU_HPP__
# define __BRICKSVM_DEVICE_SIMPLECPU_HPP__

# include <map>
# include "interpreter/Value.hpp"
# include "rapidjson/document.h"
# include "core/DllExport.hpp"
# include "event/EventThread.hpp"

namespace bricksvm
{
	namespace device
	{
		class EXPORT_DLL SimpleCPU : public bricksvm::event::EventThread
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

            void onCompare(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
        private:

            template<typename CompareFunctionType>
            void onJumpCmp(bricksvm::event::EventThread &self, bricksvm::event::Message &msg,
                           CompareFunctionType &&compareFn)
            {
                bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
                std::string                     progId = msg.getParameter<std::string>(1);
                int                             result = msg.getParameter<interpreter::Value>(2);
                interpreter::Value              jmpAddress = msg.getParameter<interpreter::Value>(3);

                if (compareFn(result))
                {
                    src.emit("vm_jump", std::ref(self), progId, jmpAddress);
                }
                else
                {
                    src.emit("instruction:finished", std::ref(self), progId, interpreter::Value(0));
                }
            }

            template<typename OperationFunctionType>
            void onCompute(bricksvm::event::EventThread &self, bricksvm::event::Message &msg,
                           OperationFunctionType &&opFun)
            {
                bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
                std::string                     progId = msg.getParameter<std::string>(1);
                interpreter::Value              val1 = msg.getParameter<interpreter::Value>(2);
                interpreter::Value              val2 = msg.getParameter<interpreter::Value>(3);

                try
                {
                    src.emit("instruction:finished", std::ref(self), progId, opFun(val1, val2));
                }
                catch (bricksvm::exception::InvalidOperationException &err)
                {
                    src.emit("instruction:error", std::ref(self), progId, std::string(err.what()));
                }
            }

            template<typename RegisterContainerType>
            void onReadRegister(bricksvm::event::EventThread &self, bricksvm::event::Message &msg, 
                                RegisterContainerType &registers)
            {
                bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
                std::string                     progId = msg.getParameter<std::string>(1);
                char                            index = msg.getParameter<interpreter::Value>(2);

                if (index >= 0 && index < 16)
                {
                    interpreter::Value  val(registers[progId][index]);
                    src.emit("instruction:finished", std::ref(self), progId, val);
                }
                else
                {
                    src.emit("instruction:error", std::ref(self), progId, "Invalid register");
                }
            }

            template<typename RegisterContainerType>
            void onWriteRegister(bricksvm::event::EventThread &self, bricksvm::event::Message &msg,
                                 RegisterContainerType &registers)
            {
                typedef typename std::remove_extent<RegisterContainerType::mapped_type>::type    ValueType;

                bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
                std::string                     progId = msg.getParameter<std::string>(1);
                int                             index = msg.getParameter<interpreter::Value>(2);
                ValueType                       val = msg.getParameter<interpreter::Value>(3);

                std::cout << "index : " << index << " value : " << val << std::endl;
                if (index >= 0 && index < 16)
                {
                    registers[progId][index] = val;
                    src.emit("instruction:finished", std::ref(self), progId, interpreter::Value(0));
                }
                else
                {
                    src.emit("instruction:error", std::ref(self), progId, "Invalid register");
                }
            }

        private:

            typedef long long int                                           RegisterValueType;
            typedef double                                                  FloatingRegisterValueType;
            typedef std::map<std::string, RegisterValueType[16]>            RegisterContainerType;
            typedef std::map<std::string, FloatingRegisterValueType[16]>    FloatingRegisterContainerType;

            RegisterContainerType           _registers;
            FloatingRegisterContainerType   _fpRegisters;
		};
	}
}

#endif