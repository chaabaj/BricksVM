#ifndef __BRICKSVM_VIRTUALMACHINE_HPP__
#define __BRICKSVM_VIRTUALMACHINE_HPP__

# include <string>
# include <istream>
# include "interpreter/Program.hpp"
# include "event/EventThread.hpp"

namespace bricksvm
{
	class VirtualMachine : public event::EventThread
	{
	public:

		typedef std::vector<std::shared_ptr<event::EventThread> >		EventThreadContainerType;
		typedef std::vector<std::shared_ptr<interpreter::Program> >		ProgramContainerType;

		VirtualMachine();

		~VirtualMachine();

		void addDevice(std::shared_ptr<event::EventThread> const &device);

		void addProgram(std::shared_ptr<interpreter::Program> const &program);

		void start();

	private:

		void executeInstruction(std::shared_ptr<interpreter::Instruction> &instruction);
		
		void onInstructionFinished(bricksvm::event::EventThread &thread, bricksvm::event::Message &msg);

		void onCall(bricksvm::event::EventThread &thread, bricksvm::event::Message &msg);

		template<typename ... Args>
		void emit(std::string eventName, Args ... args)
		{
			if (this->hasEvent(name))
			{
				EventThread::emit(name, args...);
			}
			else
			{
				for (std::shared_ptr<EventThread> &eventThread : _eventThreads)
				{
					eventThread->emit(eventName, std::ref(*this), args...);
				}
			}		
		}

	private:

		ProgramContainerType		_programs;
		EventThreadContainerType	_devices;
	};
}

#endif