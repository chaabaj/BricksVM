#include "VirtualMachine.hpp"

namespace bricksvm
{
	VirtualMachine::VirtualMachine() : event::EventThread("VM")
	{
		this->on("instruction:finished", std::bind(&VirtualMachine::onInstructionFinished, this, std::placeholders::_1, std::placeholders::_2));
		this->on("call", std::bind(&VirtualMachine::onCall, this, std::placeholders::_1, std::placeholders::_2));
	}

	VirtualMachine::~VirtualMachine()
	{

	}

	void VirtualMachine::onInstructionFinished(bricksvm::event::EventThread &thread, bricksvm::event::Message &msg)
	{
		// TODO
	}

	void VirtualMachine::onCall(bricksvm::event::EventThread &thread, bricksvm::event::Message &msg)
	{
		// TODO
	}

	void VirtualMachine::addDevice(std::shared_ptr<event::EventThread> const &device)
	{
		_devices.push_back(device);
	}

	void VirtualMachine::addProgram(std::shared_ptr<interpreter::Program> const &program)
	{
		_programs.push_back(program);
	}

	void VirtualMachine::executeInstruction(std::shared_ptr<interpreter::Instruction> &instruction)
	{
		//TODO
	}

	void VirtualMachine::start()
	{
		std::shared_ptr<interpreter::Instruction>	currentInstruction;
		bool										hasInstruction = true;


		hasInstruction = false;
		for (std::shared_ptr<interpreter::Program> &program : _programs)
		{
			currentInstruction = program->nextInstruction();
			if (currentInstruction != nullptr)
			{
				hasInstruction = true;
				this->executeInstruction(currentInstruction);
			}
		}
	}
}