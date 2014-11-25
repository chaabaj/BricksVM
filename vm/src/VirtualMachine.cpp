#include <algorithm>
#include "VirtualMachine.hpp"
#include "interpreter/ValueParameter.hpp"
#include "core/Console.hpp"

namespace bricksvm
{
    VirtualMachine::VirtualMachine() : event::ParallelEventThread<4>("VM")
    {
        using namespace std::placeholders;

        this->on("instruction:finished", std::bind(&VirtualMachine::onInstructionFinished, this, _1, _2));
        this->on("instruction:error", std::bind(&VirtualMachine::onInstructionError, this, _1, _2));
        this->on("vm_jmp", std::bind(&VirtualMachine::onJump, this, _1, _2));
        this->on("vm_print", std::bind(&VirtualMachine::onPrintValue, this, _1, _2));
    }

    VirtualMachine::~VirtualMachine()
    {

    }

    void VirtualMachine::onInstructionFinished(bricksvm::event::EventThread &thread, bricksvm::event::Message &msg)
    {
        typedef interpreter::Instruction::ParameterContainerType	ParameterContainerType;

        std::string										progId = msg.getParameter<std::string>(1);
        VirtualMachine::ProgramContainerType::iterator	it;
        interpreter::Value								&retVal = msg.getParameter<interpreter::Value>(2);

        if ((it = _programs.find(progId)) != _programs.end())
        {
            this->nextInstruction(progId, it->second, retVal);
        }
    }

    void VirtualMachine::onInstructionError(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
    {
        std::string                                     progId = msg.getParameter<std::string>(1);
        VirtualMachine::ProgramContainerType::iterator  it;
        std::string                                     errMsg = msg.getParameter<std::string>(2);

        if ((it = _programs.find(progId)) != _programs.end())
        {
            bricksvm::core::Console::error(progId) << errMsg << std::endl;
        }
    }

    void VirtualMachine::onJump(bricksvm::event::EventThread &thread, bricksvm::event::Message &msg)
    {
        std::string		progId = msg.getParameter<std::string>(2);
        unsigned int    index = msg.getParameter<interpreter::Value>(3);
        event::Message	response("instruction:finished", std::ref(*this), progId, interpreter::Value(0));

        _programs[progId]->jump(index - 1);
        static_cast<VirtualMachine&>(thread).onInstructionFinished(thread, response);
    }

    void VirtualMachine::emit(std::string const &eventName, std::shared_ptr<event::Message> &msg)
    {

        if (this->hasEvent(eventName))
        {
            EventThread::emit(eventName, msg);
        }
        else
        {
            auto it = std::find_if(_devices.begin(), _devices.end(), [this, eventName](std::shared_ptr<EventThread> &device)
            {
                return device->hasEvent(eventName);
            });
            if (it != _devices.end())
            {
                it->get()->emit(eventName, msg);
            }
            else
            {
                bricksvm::core::Console::error("VM") << " No such instruction : " << eventName << std::endl;
            }
        }
    }

    void VirtualMachine::addDevice(std::shared_ptr<event::EventThread> const &device)
    {
        _devices.push_back(device);
    }


    void VirtualMachine::addProgram(std::string const &name, std::shared_ptr<interpreter::Program> const &program)
    {
        _programs[name] = program;
    }

    void VirtualMachine::executeInstruction(std::string const &progName, interpreter::Instruction &instruction)
    {
        std::shared_ptr<event::Message>	msg = std::shared_ptr<event::Message>(new event::Message(instruction.getName()));
        interpreter::ValueParameter		*param;

        msg->pushParameter(std::ref(*this));
        msg->pushParameter(std::ref(*_memory));
        msg->pushParameter(progName);
        for (auto &elem : instruction.getParameters())
        {
            param = static_cast<interpreter::ValueParameter*>(elem.get());
            msg->pushParameter(param->getValue());
        }
        this->emit(instruction.getName(), msg);
    }

    void VirtualMachine::nextInstruction(std::string const &prgName,
                                         std::shared_ptr<interpreter::Program> &prg,
                                         interpreter::Value const &retVal)
    {
        std::shared_ptr<interpreter::Instruction>	currentInstruction;

        currentInstruction = prg->execute(retVal);
        if (currentInstruction != nullptr)
        {
            this->executeInstruction(prgName, *currentInstruction);
        }

    }

    void VirtualMachine::start()
    {
        interpreter::Value	retVal(0);

        bricksvm::core::Console::success("VM") << "Virtual machine started" << std::endl;
        for (auto &program : _programs)
        {
            this->nextInstruction(program.first, program.second, retVal);
        }
    }

    void VirtualMachine::onPrintValue(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
    {
        bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
        std::string                     prgId = msg.getParameter<std::string>(2);
        interpreter::Value              val = msg.getParameter<interpreter::Value>(3);

        bricksvm::core::Console::log("VM") << val.toString() << std::endl;
        src.emit("instruction:finished", self, prgId, interpreter::Value(0));
    }

    void VirtualMachine::allocateMemory(uint64_t memSize)
    {
        using namespace std::placeholders;


        std::vector<std::string>    prgIds;

 
        for (auto elem : _programs)
        {
            prgIds.push_back(elem.first);
        }
        this->_memory = MemoryPtrType(new bricksvm::device::Memory(memSize, prgIds));
        this->on("vm_mem_write", std::bind(&bricksvm::device::Memory::onWrite, _memory.get(), _1, _2));
        this->on("vm_mem_read", std::bind(&bricksvm::device::Memory::onRead, _memory.get(), _1, _2));
        this->on("vm_mem_dump", std::bind(&bricksvm::device::Memory::onDumpMemory, _memory.get(), _1, _2));
    }
}