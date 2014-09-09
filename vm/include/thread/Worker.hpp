#ifndef __BRICKSVM_THREAD_WORKER_HPP__
# define __BRICKSVM_THREAD_WORKER_HPP__

# include <functional>
# include "thread/AbstractWorker.hpp"

namespace bricksvm
{
	namespace thread
	{
		class Worker : public AbstractWorker< std::function<void()> >
		{
		public:
			typedef AbstractWorker<std::function<void()> >	ParentClass;

			Worker();

			~Worker();

		protected:

			void processItems(ParentClass::ItemContainerType &items);
		};
	}
}

#endif