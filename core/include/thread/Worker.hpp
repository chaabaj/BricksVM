#ifndef __BRICKSVM_THREAD_WORKER_HPP__
# define __BRICKSVM_THREAD_WORKER_HPP__

# include <functional>
# include "thread/AbstractWorker.hpp"
# include "core/DllExport.hpp"
# include "core/NewPolicy.hpp"

namespace bricksvm
{
    namespace thread
    {
        class EXPORT_DLL Worker : public AbstractWorker< std::function<void()> >,
                                  public bricksvm::core::NewPolicy < Worker >
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