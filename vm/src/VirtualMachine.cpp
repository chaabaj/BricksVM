#include "VirtualMachine.hpp"

namespace bricksvm
{
	VirtualMachine::VirtualMachine() : event::ParallelEventThread("VM")
	{
		this->on("instruction:finished", std::bind(&VirtualMachine::onInstructionFinished, this, std::placeholders::_1, std::placeholders::_2));
		this->on("call", std::bind(&VirtualMachine::onCall, this, std::placeholders::_1, std::placeholders::_2));
	}

	VirtualMachine::~VirtualMachine()
	{

	}

	void VirtualMachine::onInstructionFinished(bricksvm::event::EventThread &thread, bricksvm::event::Message &msg)
	{
		std::string										progId = msg.getParameter<std::string>(0);
		VirtualMachine::ProgramContainerType::iterator	it;
		
		if ((it = _programs.find(progId)) != _programs.end())
		{
			this->nextInstruction(progId, it->second);
		}
	}

	void VirtualMachine::onCall(bricksvm::event::EventThread &thread, bricksvm::event::Message &msg)
	{
		std::string		progId = msg.getParameter<std::string>(1);
		event::Message	response("finished", progId);

		static_cast<VirtualMachine&>(thread).onInstructionFinished(thread, response);
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
		this->emit(instruction.getName(), progName, instruction.getParameters());
	}

	void VirtualMachine::nextInstruction(std::string const &prgName, std::shared_ptr<interpreter::Program> &prg)
	{
		std::shared_ptr<interpreter::Instruction>	currentInstruction;

		currentInstruction = prg->nextInstruction();
		if (currentInstruction != nullptr)
		{
			this->executeInstruction(prgName, *currentInstruction);
		}

	}

	void VirtualMachine::start()
	{
		for (auto &program : _programs)
		{
			this->nextInstruction(program.first, program.second);
		}
	}
}