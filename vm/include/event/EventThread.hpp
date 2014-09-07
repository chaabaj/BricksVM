#ifndef __BRICKSVM_EVENT_EVENTTHREAD_HPP__
# define __BRICKSVM_EVENT_EVENTTHREAD_HPP__

# include <thread>
# include <condition_variable>
# include <map>
# include <memory>
# include <sstream>
# include <list>
# include <vector>
# include <mutex>
# include "event/Message.hpp"
# include "event/Channel.hpp"

namespace bricksvm
{
	namespace event
	{
		class EventThread
		{
		public:

			typedef std::unique_lock<std::mutex>			LockType;

			EventThread(std::string const &name);
			virtual ~EventThread();

			void stop();

			bool hasEvent(std::string const &name) const;

			template<typename ... Args>
		    void emit(std::string const &eventName, EventThread &src, Args ... args)
			{
				std::shared_ptr<Message>	msg;

				
				msg = std::shared_ptr<Message>(new Message(eventName, std::ref(src), args...));
				{
					LockType	lock(_mutex);

					_messages.push_back(msg);
				}
				_condVar.notify_one();
			}

			std::string const &getName() const;

			void operator()();

			template<typename FunctionType>
			void on(std::string const &expr, FunctionType fn)
			{
				std::vector<std::string>	eventNames;
				std::stringstream			ss;

				ss.str(expr);
				std::copy(std::istream_iterator<std::string>(ss),
					std::istream_iterator<std::string>(),
					std::back_inserter<std::vector<std::string> >(eventNames));

				for (std::string const &eventName : eventNames)
				{
					_channels[eventName].on(fn);
				}
			}

		private:

			void broadcastMsg(Message &msg);
			
		private:
			typedef Channel<void(EventThread&, Message&)>	ChannelType;
			typedef	std::map<std::string, ChannelType>		ChannelContainerType;
			typedef std::list<std::shared_ptr<Message> >	MessageContainerType;

			bool					_started;
			std::string const		_name;
			std::condition_variable	_condVar;
			std::mutex				_mutex;
			std::thread				_thread;
			ChannelContainerType	_channels;
			MessageContainerType	_messages;
		};
	}
}

#endif