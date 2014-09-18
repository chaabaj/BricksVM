#ifndef __BRICKS_CORE_CHANNEL_HPP__
# define __BRICKS_CORE_CHANNEL_HPP__

# include <memory>
# include <list>
# include <functional>
# include "core/Any.hpp"

namespace bricksvm
{
	namespace event
	{
		template<typename Signature>
		class Channel
		{
		public:

			typedef std::function<Signature>	FunctionType;

			Channel()
			{

			}

			~Channel()
			{

			}

			template<typename ... Args>
			void emit(Args ... args)
			{
				for (FunctionType &fn : _listeners)
				{
					fn(args...);
				}
			}

			template<typename ListenerType>
			void on(ListenerType listener)
			{
				std::function<Signature>	fn = listener;

				_listeners.push_back(fn);
			}

		private:
			typedef std::list<FunctionType >	ListenerContainerType;

			ListenerContainerType	_listeners;
		};
	}
}

#endif