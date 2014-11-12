#include "parser/Lexer.hpp"

namespace bricksvm
{ 
	namespace parser
	{
		Lexer::Lexer()
		{
			_position = 0;
			/*_stringTypes["Int8"] = ;
			_stringTypes["Int16"] = ;
			_stringTypes["Int32"] = ;
			_stringTypes["Float"] = ;
			_stringTypes["Double"] = ;
			_stringTypes["Int64"] = ;*/
		}

		Lexer::~Lexer()
		{

		}

		void Lexer::addNewLine(std::string const &line, int lineNumber)
		{
			_line = line; 
			_lineNumber = lineNumber;
			_position = 0;
		}

		// stdin()
		// int6: 


		std::shared_ptr<interpreter::Instruction> Lexer::getNextInstruction()
		{
			std::shared_ptr<interpreter::Instruction> instruction(new interpreter::Instruction(this->_lineNumber));
			std::string instructionName = "";

			while (this->_position < _line.length())
			{
				if (this->_line[this->_position] == '(')
				{
					instructionName = this->_line.substr(0, _position);
					instruction->setName(instructionName);
					this->_position++;
					this->functionCall(instruction);
				}
				else if (this->_line[this->_position] == ':')
				{
					instructionName = this->_line.substr(0, _position);
					_labels[instructionName] = this->_lineNumber;
				}
				/*if (this->_line[this->_position] == '(')
				{
					
					this->getNextParameter();
					this->_parentheses++;
				}
				else if (this->_line[this->_position] == ')')
				{
					this->_parentheses--;
				}*/
				this->_position++;
			}
			return (instruction);
		}

		void Lexer::functionCall(std::shared_ptr<interpreter::Instruction> &instruction)
		{
			unsigned int parameterIdx = this->_position;
			
			while (this->_line.length() > this->_position && this->_line[this->_position] != ')')
			{
				/* check if it's a ValueParameter */
				if (this->_line[this->_position] == ',')
				{
					std::string parameter = this->_line.substr(parameterIdx, this->_position - parameterIdx);

					if (core::isInteger(parameter))
					{ 
						interpreter::ValueParameter *param = new interpreter::ValueParameter(convertStringToValue(parameter, interpreter::Type::Int32));
						instruction->addParameter(std::shared_ptr<interpreter::ValueParameter>(param));
					}
					else if (core::isDecimal(parameter))
						instruction->addParameter(std::shared_ptr<interpreter::ValueParameter>(new interpreter::ValueParameter(convertStringToValue(parameter, interpreter::Type::Float))));
					else if (core::isLabel(parameter))
						instruction->addParameter(std::shared_ptr<interpreter::ValueParameter>(new interpreter::ValueParameter(getLabelLine(parameter))));

					this->_position++;
					parameterIdx = this->_position;
				}
				/* check if is another function call (eg InstructionParameter)*/
				else if (this->_line[this->_position] == '(')
				{
					std::shared_ptr<interpreter::Instruction> newInstruction(new interpreter::Instruction(this->_lineNumber));

					newInstruction->setName(this->_line.substr(parameterIdx, _position - parameterIdx));
					this->_position++;
					this->functionCall(newInstruction);
					instruction->addParameter(std::shared_ptr<interpreter::InstructionParameter>(new interpreter::InstructionParameter(newInstruction)));
				}
				
				this->_position++;
			}

			if (this->_line.length() > this->_position)
			{
				std::string parameter = this->_line.substr(parameterIdx, this->_position - parameterIdx);

				if (core::isInteger(parameter))
				{
					interpreter::ValueParameter *param = new interpreter::ValueParameter(convertStringToValue(parameter, interpreter::Type::Int32));
					instruction->addParameter(std::shared_ptr<interpreter::ValueParameter>(param));
				}
				else if (core::isDecimal(parameter))
					instruction->addParameter(std::shared_ptr<interpreter::ValueParameter>(new interpreter::ValueParameter(convertStringToValue(parameter, interpreter::Type::Float))));
				else if (core::isLabel(parameter))
					instruction->addParameter(std::shared_ptr<interpreter::ValueParameter>(new interpreter::ValueParameter(getLabelLine(parameter))));

				this->_position++;
				parameterIdx = this->_position;
			}
		}

		interpreter::Value Lexer::getLabelLine(std::string val)
		{
			std::map<std::string, int>::const_iterator it;
			for (it = this->_labels.begin(); it != this->_labels.end(); ++it)
			{
				if (it->first == val)
					return interpreter::Value(it->second);
			}
			throw new std::exception("Invalid label");
		}

		std::shared_ptr<interpreter::AParameter> Lexer::getNextParameter()
		{
			std::shared_ptr<interpreter::AParameter> ptr;
			interpreter::AParameter::Type type;

			type = this->getParameterType();

			return (ptr);
		}

		interpreter::AParameter::Type Lexer::getParameterType()
		{
			if (hasParameterIdentifier())
			{

			}

			for (int i = this->_position; i < this->_line.length(); i++)
			{
				
			}

			return (interpreter::AParameter::ValueType);
		}

		bool Lexer::hasParameterIdentifier()
		{
			if (this->_line.find(':', this->_position) != std::string::npos)
			{
				std::string identifier = this->_line.substr(this->_position, this->_line.find(':', this->_position));
				for (std::map<std::string, interpreter::Type>::const_iterator it = this->_stringTypes.begin();
					it != this->_stringTypes.end();
					++it)
				{
					if (it->first == identifier)
						return (true);
				}
			}
			return (false);
		}

		interpreter::Value  Lexer::convertStringToValue(std::string val, interpreter::Type type)
		{
			switch (type)
			{
				case interpreter::Int8:
					return interpreter::Value(core::convert<char>(val));
				case interpreter::Int16:
					return interpreter::Value(core::convert<short>(val));
				case interpreter::Int32:
					return interpreter::Value(core::convert<int>(val));
				case interpreter::Int64:
					return interpreter::Value(core::convert<long long int>(val));
				case interpreter::Double:
					return interpreter::Value(core::convert<double>(val));
				case interpreter::Float:
					return interpreter::Value(core::convert<float>(val));
				default:
					throw exception::InvalidTypeException(core::stringBuilder(val, "has an unexpected type"));
			}
		}

		

	}
}