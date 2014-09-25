#include "VirtualMachine.hpp"
#include "interpreter/ValueParameter.hpp"

namespace bricksvm
{
    VirtualMachine::VirtualMachine() : event::ParallelEventThread<4>("VM")
    {
        this->on("instruction:finished", std::bind(&VirtualMachine::onInstructionFinished, this, std::placeholders::_1, std::placeholders::_2));
        this->on("vm_jmp", std::bind(&VirtualMachine::onJump, this, std::placeholders::_1, std::placeholders::_2));
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

    void VirtualMachine::onJump(bricksvm::event::EventThread &thread, bricksvm::event::Message &msg)
    {
        std::string		progId = msg.getParameter<std::string>(1);
        VirtualMachine	&vm = msg.getParameter<VirtualMachine>(0);
        unsigned int    index = msg.getParameter<interpreter::Value>(2);
        event::Message	response("instruction:finished", std::ref(*this), progId, interpreter::Value(0));

        _programs[progId]->jump(index);
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
            for (std::shared_ptr<EventThread> &device : _devices)
            {
                if (device->hasEvent(eventName))
                {
                    device->emit(eventName, msg);
                }
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
        prg->next();
        if (currentInstruction != nullptr)
        {
            this->executeInstruction(prgName, *currentInstruction);
        }

    }

    void VirtualMachine::start()
    {
        interpreter::Value	retVal(0);

        for (auto &program : _programs)
        {
            this->nextInstruction(program.first, program.second, retVal);
        }
    }
}