#include "thread/Worker.hpp"

namespace bricksvm
{
    namespace thread
    {
        Worker::Worker() : ParentClass()
        {

        }

        Worker::~Worker()
        {

        }

        void Worker::processItems(Worker::ParentClass::ItemContainerType &items)
        {
            for (std::function<void()> &fn : items)
            {
                fn();
            }
        }
    }
}