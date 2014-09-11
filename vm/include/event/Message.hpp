#ifndef __BRICKSVM_EVENT_MESSAGE_HPP__
# define __BRICKSVM_EVENT_MESSAGE_HPP__

# include <vector>
# include <string>
# include <memory>
# include "core/Any.hpp"

namespace bricksvm
{
	namespace event
	{
		class Message
		{
		public:

			template<typename ... Args>
			Message(std::string const &name, Args&& ... args) : _name(name)
			{
				this->pushParameter(args...);
			}

			Message(std::string const &name);

			~Message();
			
			Message(Message const &other);

			Message &operator=(Message const &other);


			std::string const &getName() const;

			template<typename ValueType>
			ValueType	&getParameter(unsigned int index)
			{
				if (index < _parameters.size())
				{
					return _parameters[index].getValue<ValueType>();
				}
				throw std::out_of_range("Cannot access to parameter n° : " + index);
			}

		private:

			template<typename ArgType, typename ... Args>
			void pushParameter(ArgType &&arg, Args&& ... args)
			{
				bricksvm::core::Any	value(arg);

				_parameters.push_back(value);
				this->pushParameter(args...);
			}

			template<typename ArgType>
			void pushParameter(ArgType &&arg)
			{
				bricksvm::core::Any	value(arg);

				_parameters.push_back(value);
			}

		private:

			typedef std::vector<bricksvm::core::Any>	ParameterContainerType;

			std::string				_name;
			ParameterContainerType	_parameters;
			
		};
	}
}

#endif