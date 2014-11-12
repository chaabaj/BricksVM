#include <iostream>
#include <fstream>
#include <string>
#include "parser/Parser.hpp"
#include "parser/Lexer.hpp"
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
			std::shared_ptr<interpreter::Program>	newProgram(new interpreter::Program());
			std::ifstream source;
			std::string line;
			int lineNumber = 1;

			/*source.open(fileName.c_str());
			std::cerr << source.fail() << std::endl;
			if (!source.good())
				throw exception::FileNotFoundException("Cannot find programe file:" + fileName);*/
			std::list<std::string> program;
			program.push_back("function1(1)");
			program.push_back("label:");
			program.push_back("label2:");
			program.push_back("function2(1, function3(2.2))");
			program.push_back("jump(label)");
			parser::Lexer lexer;
			for (std::list<std::string>::iterator it = program.begin(); it != program.end(); it++)
			{
			/*while (std::getline(source, line))
			{*/
				lexer.addNewLine(*it, lineNumber);
				std::shared_ptr<interpreter::Instruction> instr = lexer.getNextInstruction();
				if (instr->getName() != "")
					newProgram->addInstruction(instr);
				++lineNumber;
			}
			//}
			newProgram->dumpProgram();

			source.close();

			return newProgram;
		}

	}
}
