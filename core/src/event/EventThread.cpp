#include "event/EventThread.hpp"

namespace bricksvm
{
	namespace event
	{
		EventThread::EventThread(std::string const &name) : EventThread::ParentClass(), _name(name)
		{
		}

		EventThread::~EventThread()
		{
		}


		bool EventThread::hasEvent(std::string const &name) const
		{
			return _channels.find(name) != _channels.end();
		}

		std::string const &EventThread::getName() const
		{
			return _name;
		}

		void EventThread::processItems(EventThread::ParentClass::ItemContainerType &items)
		{
			for (std::shared_ptr<Message> &msg : items)
			{
				this->broadcastMsg(msg);
			}
		}

		void EventThread::broadcastMsg(std::shared_ptr<Message> &msg)
		{
			ChannelContainerType::iterator	it;
			std::string const				&name = msg->getName();

			if ((it = _channels.find(name)) != _channels.end())
			{
				it->second.emit(std::ref(*this), std::ref(*msg));
			}
		}

	}
}