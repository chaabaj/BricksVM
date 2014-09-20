#ifndef __BRICKSVM_THREAD_ABSTRACTWORKER_HPP__
# define __BRICKSVM_THREAD_ABSTRACTWORKER_HPP__

# include <stack>
# include <mutex>
# include <thread>
# include <condition_variable>
# include <list>
# include "core/DllExport.hpp"
# include "core/NoCopyable.hpp"

namespace bricksvm
{
    namespace thread
    {
        /**
         * @class AbstractWorker
         * @tparam ItemType Object type to pull(Message, Task,...)
         *
         * @desc Abstraction of a worker that manage items and process it child classes need to implement the method processItems
         */
        template<typename ItemType>
        class EXPORT_DLL AbstractWorker : public bricksvm::core::NoCopyable
        {
        public:

            /**
             * @typedef LockType lock type used
             */
            typedef std::unique_lock<std::mutex>	LockType;


            /// constructor
            AbstractWorker()
            {
                _started = false;
                _thread = std::thread(std::bind(&AbstractWorker::operator(), this));
                {
                    LockType	lock(_mutex);

                    _condVar.wait(lock, [this]()
                    {
                        return _started;
                    });
                }
            }

            /// destructor
            virtual ~AbstractWorker()
            {
                _started = false;
                _condVar.notify_one();
                _thread.join();
            }

            /**
             * @brief method where the thread execute
             *
             * @desc this method is a loop that wait items and process it
             */
            void operator()()
            {
                _started = true;
                _condVar.notify_one();
                while (_started)
                {
                    if (!_items.size())
                    {
                        LockType	lock(_mutex);

                        _condVar.wait(lock, [this]()
                        {
                            return _items.size() > 0;
                        });
                    }
                    else
                    {
                        ItemContainerType	items;

                        {
                            ItemType	item;
                            LockType	lock(_mutex);

                            while (!_items.empty())
                            {
                                item = _items.back();
                                items.push_front(item);
                                _items.pop_back();
                            }
                        }
                        this->processItems(items);
                    }
                }
            }

            /**
             * @brief lock push the new item in items and notify the thread a new item was pushed
             */
            void pushItem(ItemType &newItem)
            {
                {
                    LockType	lock(_mutex);

                    _items.push_back(newItem);
                }
                _condVar.notify_one();
            }

            bool isStarted() const
            {
                return _started;
            }

            unsigned int getItemSize() const
            {
                return _items.size();
            }

        protected:
            typedef std::list<ItemType>	ItemContainerType;

            /// Process the items(To implement in child classes)
            virtual void processItems(ItemContainerType &items) = 0;

        private:
            bool					_started;
            std::condition_variable	_condVar;
            std::mutex				_mutex;
            std::thread				_thread;
            ItemContainerType		_items;
        };
    }
}

#endif