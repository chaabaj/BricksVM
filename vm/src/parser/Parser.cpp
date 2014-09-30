#include <iostream>
#include <fstream>
#include <string>
#include "parser/Parser.hpp"
#include "exception/FileNotFoundException.hpp"


namespace bricksvm
{
	namespace parser
	{
		Parser::Parser()
		{

		}

		std::shared_ptr<interpreter::Program> Parser::generateProgramFromFile(std::string const &fileName)
		{
			std::shared_ptr<interpreter::Program>	newProgram;
			std::ifstream source;
			std::string line;

			source.open(fileName);
			if (source.good())
				throw exception::FileNotFoundException("Cannot find programe file:" + fileName);
			while (std::getline(source, line))
			{
				
			}

			source.close();

			return newProgram;
		}

	}
}
