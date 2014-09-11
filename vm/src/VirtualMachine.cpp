#include "VirtualMachine.hpp"
#include "interpreter/Utils.hpp"

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
		typedef interpreter::Instruction::ParameterContainerType	ParameterContainerType;

		std::string										progId = msg.getParameter<std::string>(1);
		ParameterContainerType							&params = msg.getParameter<ParameterContainerType>(2);
		VirtualMachine::ProgramContainerType::iterator	it;
		interpreter::Value const						&retVal = dynamic_cast<interpreter::ValueParameter&>(*params[0]).getValue();
		
		if ((it = _programs.find(progId)) != _programs.end())
		{
			this->nextInstruction(progId, it->second, retVal);
		}
	}

	void VirtualMachine::onCall(bricksvm::event::EventThread &thread, bricksvm::event::Message &msg)
	{
		std::string		progId = msg.getParameter<std::string>(1);
		event::Message	response("instruction:finished", std::ref(*this), progId, interpreter::makeParameters(0));

		std::cout << "Call instruction : " << progId << std::endl;
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

		for (auto &program : _programs)
		{
			this->nextInstruction(program.first, program.second, retVal);
		}
	}
}