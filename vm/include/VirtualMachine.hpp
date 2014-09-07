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

		void readFile(std::string const &filename);

	private:

		template<typename ... Args>
		void emit(std::string eventName, Args ... args)
		{
			for (std::shared_ptr<EventThread> &eventThread : _eventThreads)
			{
				eventThread->emit(eventName, args...);
			}
		}

		void readStream(std::istream const &stream);

	private:

		ProgramContainerType		_programs;
		EventThreadContainerType	_devices;
	};
}

#endif