#ifndef __BRICKSVM_INTERPRETER_INSTRUCTION_HPP__
# define __BRICKSVM_INTERPRETER_INSTRUCTION_HPP__

# include <vector>
# include <memory>
# include "interpreter/AParameter.hpp"

namespace bricksvm
{
	namespace interpreter
	{
		class Instruction
		{
		public:

			typedef std::vector<std::shared_ptr<AParameter> >	ParameterContainerType;

			Instruction();
			~Instruction();

			void setName(std::string const &str);
			void addParameter(std::shared_ptr<AParameter> const &parameter);

			ParameterContainerType	&getParameters();
			std::string const		&getName() const;

		private:
			std::string				_name;
			ParameterContainerType	_parameters;
		};
	}
}

#endif