#ifndef __BRICKSVM_VIRTUALMACHINE_HPP__
#define __BRICKSVM_VIRTUALMACHINE_HPP__

# include <string>
# include <istream>
# include "interpreter/Program.hpp"
# include "event/EventThread.hpp"
# include "event/ParallelEventThread.hpp"

namespace bricksvm
{
	class VirtualMachine : public event::ParallelEventThread
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

		void nextInstruction(std::string const &prgName, std::shared_ptr<interpreter::Program> &prg);

		template<typename ... Args>
		void emit(std::string eventName, Args ... args)
		{
			if (this->hasEvent(eventName))
			{
				EventThread::emit(eventName, std::ref(*this), args...);
			}
			else
			{
				for (std::shared_ptr<EventThread> &device : _devices)
				{
					if (device->hasEvent(eventName))
					{
						device->emit(eventName, std::ref(*this), args...);
					}
				}
			}		
		}

	private:
		typedef std::vector<std::shared_ptr<event::EventThread> >				EventThreadContainerType;
		typedef std::map<std::string, std::shared_ptr<interpreter::Program> >	ProgramContainerType;

		ProgramContainerType		_programs;
		EventThreadContainerType	_devices;
	};
}

#endif