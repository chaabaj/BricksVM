#include "event/EventThread.hpp"

namespace bricksvm
{
	namespace event
	{
		EventThread::EventThread(std::string const &name) : _name(name)
		{
			_started = false;
			_thread = std::thread(std::bind(&EventThread::operator(), this));
			{
				LockType	lock(_mutex);

				_condVar.wait(lock, [this]()
				{
					return _started;
				});
			}
		}

		EventThread::~EventThread()
		{
			_condVar.notify_one();
			_started = false;
			_thread.join();
		}

		void EventThread::stop()
		{
			_started = false;
		}

		void EventThread::operator()()
		{
			_started = true;
			_condVar.notify_one();
			while (_started)
			{
				if (_messages.size() == 0)
				{
					LockType lock(_mutex);

					_condVar.wait(lock, [this]()
					{
						return _messages.size() > 0;
					});
				}
				else
				{
					{
						std::shared_ptr<Message>	msgPtr;
						LockType					lock(_mutex);

						while (!_messages.empty())
						{
							msgPtr = _messages.front();
							this->broadcastMsg(*msgPtr);
							_messages.pop_front();
						}
					}
				}
			}
		}

		bool EventThread::hasEvent(std::string const &name) const
		{
			return _channels.find(name) != _channels.end();
		}

		std::string const &EventThread::getName() const
		{
			return _name;
		}

		void EventThread::broadcastMsg(Message &msg)
		{
			ChannelContainerType::iterator	it;
			std::string const				&name = msg.getName();

			if ((it = _channels.find(name)) != _channels.end())
			{
				std::cout << "device 1(2) : " << this << std::endl;
				it->second.emit(std::ref(*this), std::ref(msg));
			}
		}

	}
}