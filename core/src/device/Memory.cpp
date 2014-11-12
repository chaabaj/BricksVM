#include <cassert>
#include "interpreter/Value.hpp"
#include "device/Memory.hpp"
#include "core/Console.hpp"

namespace bricksvm
{
    namespace device
    {
        Memory::Memory(unsigned int size, std::vector<std::string> const &progIds) : _size(size)
        {
            unsigned int step = size / progIds.size();

            assert(size > 0 && step > 0);
            _memory = MemoryBufferType(new char[size]);
            for (unsigned int i = 0; i < progIds.size(); ++i)
            {
                IndexMemoryType index;

                std::string const &progId = progIds[i];

                index.first = i * step;
                index.second = i * step + step - 1;
                _memIndexes[progId] = index;
            }
            bricksvm::core::Console::success("Memory") << "Memory size " << size << " bytes" << std::endl;
            bricksvm::core::Console::success("Memory") << "Program memory size" << step << " bytes" << std::endl;
        }
        

        Memory::~Memory()
        {
        }

        void Memory::onRead(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            auto                &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string const   &progId = msg.getParameter<std::string>(1);
            uint64_t            addr = msg.getParameter<uint64_t>(2);
            interpreter::Type   type = static_cast<interpreter::Type>(msg.getParameter<interpreter::Value>(3).as<int>());
            interpreter::Value  readValue(0);

            try
            {
                switch (type)
                {
                case interpreter::Int8:
                {
                    char    byte;

                    this->read(progId, addr, &byte, sizeof(byte));
                    readValue = byte;
                    break;
                }
                case interpreter::Int16:
                {
                    int16_t value;

                    this->read(progId, addr, &value, 1);
                    readValue = value;
                    break;
                }
                case interpreter::Int32:
                {
                    int32_t value;

                    this->read(progId, addr, &value, 1);
                    readValue = value;
                    break;
                }
                case interpreter::Int64:
                {
                    int64_t value;

                    this->read(progId, addr, &value, 1);
                    readValue = value;
                    break;
                }
                case interpreter::Float:
                {
                    float   value;

                    this->read(progId, addr, &value, 1);
                    readValue = value;
                    break;
                }
                case interpreter::Double:
                {
                    double  value;

                    this->read(progId, addr, &value, 1);
                    readValue = value;
                    break;
                }
                default:
                {
                    throw bricksvm::exception::InvalidOperationException("Invalid operation unknown type");
                    break;
                }
                }
                src.emit("instruction:finished", self, progId, readValue);
            }
            catch (bricksvm::exception::InvalidOperationException &err)
            {
                src.emit("instruction:error", self, progId, std::string(err.what()));
            }
        }

        void Memory::onWrite(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            auto                &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string const   &progId = msg.getParameter<std::string>(1);
            uint64_t            addr = msg.getParameter<uint64_t>(2);
            interpreter::Value  value = msg.getParameter<interpreter::Value>(3);

            try
            {
                switch (value.type())
                {
                case interpreter::Int8:
                {
                    char    byte = value;

                    this->write(progId, addr, &byte, 1);
                    break;
                }
                case interpreter::Int16:
                {
                    int16_t int16Value = value;

                    this->write(progId, addr, &int16Value, 1);
                    break;
                }
                case interpreter::Int32:
                {
                    int32_t int32Value = value;

                    this->write(progId, addr, &int32Value, 1);
                    break;
                }
                case interpreter::Int64:
                {
                    int64_t int64Value;

                    this->write(progId, addr, &int64Value, 1);
                    break;
                }
                case interpreter::Float:
                {
                    float   floatValue = value;

                    this->write(progId, addr, &floatValue, 1);
                    break;
                }
                case interpreter::Double:
                {
                    double  doubleValue;

                    this->write(progId, addr, &doubleValue, 1);
                    break;
                }
                default:
                {
                    throw bricksvm::exception::InvalidOperationException("Invalid operation unknown type");
                    break;
                }
                }
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &err)
            {
                src.emit("instruction:error", self, progId, std::string(err.what()));
            }
        }

        uint64_t Memory::getRealAddr(std::string const &progId, uint64_t virtualAddr) const
        {
            auto    it = _memIndexes.find(progId);

            if (it != _memIndexes.end())
            {
                auto        index = (*it).second;
                uint64_t    realAddr;

                realAddr = index.first + virtualAddr;
                if (realAddr <= index.second)
                {
                    throw bricksvm::exception::InvalidOperationException("Memory overflow");
                }
                return realAddr;
            }
            throw bricksvm::exception::InvalidOperationException("No such program id registered");
        }
    }
}