#include "thread/WorkerPool.hpp"

namespace bricksvm
{
	namespace thread
	{
		WorkerPool::WorkerPool(unsigned int size)
		{
			for (unsigned int i = 0; i < size; ++i)
			{
				_workers.push_back(std::shared_ptr<Worker>(new Worker()));
			}
		}

		WorkerPool::~WorkerPool()
		{

		}

	}
}