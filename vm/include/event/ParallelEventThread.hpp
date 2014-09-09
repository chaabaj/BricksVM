#ifndef __BRICKSVM_EVENT_PARALLELEVENTTHREAD_HPP__
# define __BRICKSVM_EVENT_PARALLELEVENTTHREAD_HPP__

# include "event/EventThread.hpp"
# include "thread/WorkerPool.hpp"

namespace bricksvm
{
	namespace event
	{
		class ParallelEventThread : public EventThread
		{
		public:
			ParallelEventThread(std::string const &name);

			~ParallelEventThread();

			void broadcastMsg(std::shared_ptr<Message> &msg);

		private:
			bricksvm::thread::WorkerPool	_pool;

			static const unsigned int		_nbWorker = 4;
		};
	}
}

#endif