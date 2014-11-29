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
			parser::Lexer lexer;

			source.open(fileName.c_str());
			if (!source.good())
				throw exception::FileNotFoundException("Cannot find programe file:" + fileName);
			std::list<std::string> program;
			/*program.push_back("function1(1)");
			program.push_back("label:");
			program.push_back("label_two:");
			program.push_back("  function2(  Int32:1.2  ,   function3(   2.2 , label), function25(2.251, label_two, 55555)");
			program.push_back("jump(  label_two )");
			program.push_back("  jump(  label  )");
			
			for (std::list<std::string>::iterator it = program.begin(); it != program.end(); it++)
			{*/
			while (std::getline(source, line))
			{
				if (line.size() == 0 || (line[0] == '/' && line[1] == '/'))
						continue;
				lexer.addNewLine(line, lineNumber);
				std::shared_ptr<interpreter::Instruction> instr = lexer.getNextInstruction();
				if (instr->getName() != "")
					newProgram->addInstruction(instr);
				++lineNumber;
			}
			/*}*/
			newProgram->dumpProgram();

			source.close();

			return newProgram;
		}

	}
}
