#ifndef __BRICKSVM_EVENT_PARALLELEVENTTHREAD_HPP__
# define __BRICKSVM_EVENT_PARALLELEVENTTHREAD_HPP__

# include "event/EventThread.hpp"
# include "thread/WorkerPool.hpp"
# include "core/DllExport.hpp"
# include "core/NewPolicy.hpp"

namespace bricksvm
{
    namespace event
    {
        template<int nbThread>
        class EXPORT_DLL ParallelEventThread : public EventThread,
                                               public bricksvm::core::NewPolicy < ParallelEventThread<nbThread> >
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
                std::function<void()> task = [this, msg]()
                {
                    std::shared_ptr<Message> cpyMsg = msg;

                    EventThread::broadcastMsg(cpyMsg);
                };
                    
                _pool.dispatch(task);
            }

        private:
            bricksvm::thread::WorkerPool    _pool;

            static const unsigned int       _nbWorker = nbThread;
        };
    }
}

#endif
