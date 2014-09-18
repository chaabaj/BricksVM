#include "event/Message.hpp"

namespace bricksvm
{
	namespace event
	{

		Message::Message(std::string const &name) : _name(name)
		{
		}

		Message::Message(Message const &other) : _name(other._name), _parameters(other._parameters)
		{

		}

		Message &Message::operator=(Message const &other)
		{
			_name = other._name;
			_parameters = other._parameters;
			return (*this);
		}

		Message::~Message()
		{

		}

		std::string const &Message::getName() const
		{
			return _name;
		}
	}
}