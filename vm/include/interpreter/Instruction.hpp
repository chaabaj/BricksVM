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

			Instruction(unsigned const int lineNumber);
			~Instruction();

			void setName(std::string const &str);
			void addParameter(std::shared_ptr<AParameter> const &parameter);

			ParameterContainerType		&getParameters();
			
			bool						parametersIsResolved() const;

			void						resolveParameter(std::shared_ptr<AParameter> const &paramToResolve,
														 std::shared_ptr<AParameter> const &resolvedValue);
		
			std::shared_ptr<AParameter> getUnresolvedParameter();

			std::string const			&getName() const;

		private:
			bool					_isResolved;
			std::string				_name;
			ParameterContainerType	_parameters;
			unsigned const int		_lineNumber;
		};
	}
}

#endif