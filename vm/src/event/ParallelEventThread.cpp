#include "event/ParallelEventThread.hpp"

namespace bricksvm
{
	namespace event
	{
		ParallelEventThread::ParallelEventThread(std::string const &name) : EventThread(name), 
																		    _pool(bricksvm::thread::WorkerPool(_nbWorker))
		{

		}

		ParallelEventThread::~ParallelEventThread()
		{

		}

		void ParallelEventThread::broadcastMsg(std::shared_ptr<Message> &msg)
		{
			_pool.dispatch([msg, this]()
			{
				auto cpyMsg = msg;

				EventThread::broadcastMsg(cpyMsg);
			});
		}
	}
}