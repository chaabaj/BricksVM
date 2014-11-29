#ifndef __BRICKSVM_PARSER_LEXER_HPP__
# define __BRICKSVM_PARSER_LEXER_HPP__

# include <memory>
# include <map>
# include <functional>

# include "interpreter/Instruction.hpp"
# include "interpreter/ValueParameter.hpp"
# include "interpreter/InstructionParameter.hpp"
# include "interpreter/Value.hpp"
# include "core/Utils.hpp"


namespace bricksvm
{
	namespace parser
	{
		class Lexer
		{
		private:
			unsigned int			_position;
			int						_lineNumber;
			int						_parentheses;
			std::string				_line;
			std::map<std::string, interpreter::Type> _stringTypes;
			std::map<std::string, int> _labels;

		public:
			Lexer();
			~Lexer();

		public:
			std::shared_ptr<interpreter::Instruction> getNextInstruction();
			void addNewLine(std::string const &line, int lineNumber);

		private:
			std::shared_ptr<interpreter::AParameter> getNextParameter();
			interpreter::AParameter::Type getParameterType();
			interpreter::Value convertStringToValue(std::string val, interpreter::Type type) const;
			bool hasParameterIdentifier(std::string const &parameter);
			interpreter::Value getLabelLine(std::string val);
			void functionCall(std::shared_ptr<interpreter::Instruction> &instruction);
			void addNewValueParameter(std::shared_ptr<interpreter::Instruction> &instruction,
				int parameterIdx);
			interpreter::Type convertStringTypeToEnumType(std::string type);

		};
	}
}

#endif