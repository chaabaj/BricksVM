#ifndef __BRICKSVM_INTERPRETER_INSTRUCTION_HPP__
# define __BRICKSVM_INTERPRETER_INSTRUCTION_HPP__

# include <vector>
# include "interpreter/Parameter.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		class Instruction
		{
		public:

			typedef std::vector<std::shared_ptr<IParameter> >	ParameterContainerType;

			Instruction();
			~Instruction();

			void setName(std::string const &str);
			void addParameter(IParameter *parameter);

			ParameterContainerType	&getParameters();
			std::string const		&getName() const;

		private:
			std::string				_name;
			ParameterContainerType	_parameters;
		};
	}
}

#endif