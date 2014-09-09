#ifndef __BRICKSVM_THREAD_WORKERPOOL_HPP__
# define __BRICKSVM_THREAD_WORKERPOOL_HPP__

# include <vector>
# include <memory>
# include "thread/Worker.hpp"

namespace bricksvm
{
	namespace thread
	{
		class WorkerPool
		{
		public:

			WorkerPool(unsigned int size);

			~WorkerPool();

			template<typename FunctionType>
			void dispatch(FunctionType fn)
			{
				std::shared_ptr<Worker>	lessWorker;
				std::function<void()>	stdFn = fn;

				lessWorker = _workers[0];
				for (std::shared_ptr<Worker> &worker : _workers)
				{
					if (worker->getItemSize() < lessWorker->getItemSize())
					{
						lessWorker = worker;
					}
				}
				lessWorker->pushItem(stdFn);
			}
		private:
			typedef std::vector<std::shared_ptr<Worker> >	WorkerContainerType;

			WorkerContainerType	_workers;
		};
	}
}

#endif