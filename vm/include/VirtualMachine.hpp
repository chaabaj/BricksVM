#ifndef __BRICKSVM_VIRTUALMACHINE_HPP__
#define __BRICKSVM_VIRTUALMACHINE_HPP__

# include <string>
# include <istream>
# include "interpreter/Program.hpp"
# include "event/EventThread.hpp"
# include "event/Message.hpp"
# include "event/ParallelEventThread.hpp"
# include "core/NonCopyable.hpp"

namespace bricksvm
{
	class VirtualMachine : public event::ParallelEventThread<4>, public core::NonCopyable
	{
	public:

		VirtualMachine();

		~VirtualMachine();

		void addDevice(std::shared_ptr<event::EventThread> const &device);

		void addProgram(std::string const &name, std::shared_ptr<interpreter::Program> const &program);

		void start();

	private:

		void executeInstruction(std::string const &program, interpreter::Instruction &instruction);
		
		void onInstructionFinished(bricksvm::event::EventThread &thread, bricksvm::event::Message &msg);

		void onCall(bricksvm::event::EventThread &thread, bricksvm::event::Message &msg);

		void nextInstruction(std::string const &prgName, 
							 std::shared_ptr<interpreter::Program> &prg, 
							 interpreter::Value const &retVal);

		void emit(std::string const &eventName, std::shared_ptr<event::Message> &msg);


	private:
		typedef std::vector<std::shared_ptr<event::EventThread> >				EventThreadContainerType;
		typedef std::map<std::string, std::shared_ptr<interpreter::Program> >	ProgramContainerType;

		ProgramContainerType		_programs;
		EventThreadContainerType	_devices;
	};
}

#endif