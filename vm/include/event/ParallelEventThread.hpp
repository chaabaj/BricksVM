#ifndef __BRICKSVM_EVENT_PARALLELEVENTTHREAD_HPP__
# define __BRICKSVM_EVENT_PARALLELEVENTTHREAD_HPP__

# include "event/EventThread.hpp"
# include "thread/WorkerPool.hpp"

namespace bricksvm
{
	namespace event
	{
		template<int nbThread>
		class ParallelEventThread : public EventThread
		{
		public:
			ParallelEventThread(std::string const &name) : EventThread(name),
														   _pool(bricksvm::thread::WorkerPool(_nbWorker))
			{

			}

			~ParallelEventThread()
			{

			}

			void broadcastMsg(std::shared_ptr<Message> &msg)
			{
				_pool.dispatch([msg, this]()
				{
					auto cpyMsg = msg;

					EventThread::broadcastMsg(cpyMsg);
				});
			}

		private:
			bricksvm::thread::WorkerPool	_pool;

			static const unsigned int		_nbWorker = nbThread;
		};
	}
}

#endif