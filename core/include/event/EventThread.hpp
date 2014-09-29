#ifndef __BRICKSVM_EVENT_EVENTTHREAD_HPP__
# define __BRICKSVM_EVENT_EVENTTHREAD_HPP__

# include <map>
# include <memory>
# include <iterator>
# include <sstream>
# include <list>
# include <vector>
# include "thread/Worker.hpp"
# include "event/Message.hpp"
# include "event/Channel.hpp"
# include "core/DllExport.hpp"
# include "core/NewPolicy.hpp"

namespace bricksvm
{
    namespace event
    {
        class EXPORT_DLL EventThread : public bricksvm::thread::AbstractWorker<std::shared_ptr<Message> >,
                                       public bricksvm::core::NewPolicy < EventThread >
        {
        public:

            typedef bricksvm::thread::AbstractWorker<std::shared_ptr<Message> >	ParentClass;

            EventThread(std::string const &name);
            virtual ~EventThread();

            bool hasEvent(std::string const &name) const;

            template<typename ... Args>
            void emit(std::string const &eventName, EventThread &src, Args ... args)
            {
                std::shared_ptr<Message>	msg;

                msg = std::shared_ptr<Message>(new Message(eventName, std::ref(src), args...));
                this->pushItem(msg);
            }

            void emit(std::string const &eventName, std::shared_ptr<Message> &msg)
            {
                this->pushItem(msg);
            }

            std::string const &getName() const;

            template<typename FunctionType>
            void on(std::string const &expr, FunctionType fn)
            {
                std::vector<std::string>	eventNames;
                std::stringstream			ss;

                ss.str(expr);
                std::copy(std::istream_iterator<std::string>(ss),
                    std::istream_iterator<std::string>(),
                    std::back_inserter<std::vector<std::string> >(eventNames));

                for (std::string const &eventName : eventNames)
                {
                    _channels[eventName].on(fn);
                }
            }


            virtual void broadcastMsg(std::shared_ptr<Message> &msg);

        protected:
            typedef std::list<std::shared_ptr<Message> >	MessageContainerType;

            void processItems(ItemContainerType &items);

        private:
            typedef Channel<void(EventThread&, Message&)>   ChannelType;
            typedef	std::map<std::string, ChannelType>      ChannelContainerType;


            std::string const       _name;
            ChannelContainerType    _channels;
        };
    }
}

#endif
