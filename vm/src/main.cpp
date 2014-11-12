#include <iostream>
#include "VirtualMachine.hpp"
#include "ConfigurationParser.hpp"
#include "interpreter/ValueParameter.hpp"

#include "parser/Parser.hpp"

#include "core/Console.hpp"


int main(int ac, char **av)
{
    using namespace bricksvm;

    ConfigurationParser                         parser("config/config.json");
    VirtualMachine                              vm;
    std::shared_ptr<interpreter::Program>       prg(new interpreter::Program);
    std::shared_ptr<interpreter::Program>       prg2(new interpreter::Program);
    std::shared_ptr<interpreter::Instruction>   instr(new interpreter::Instruction(0));
    std::shared_ptr<interpreter::Instruction>   instr2(new interpreter::Instruction(1));
    interpreter::Value                          index(1);
    interpreter::Value                          val(3.4);
    std::shared_ptr<interpreter::AParameter>	param(new interpreter::ValueParameter(index));
    std::shared_ptr<interpreter::AParameter>	param2(new interpreter::ValueParameter(val));
    std::shared_ptr<interpreter::AParameter>	width(new interpreter::ValueParameter(interpreter::Value(800)));
    std::shared_ptr<interpreter::AParameter>	height(new interpreter::ValueParameter(interpreter::Value(600)));
    std::shared_ptr<interpreter::AParameter>	color(new interpreter::ValueParameter(interpreter::Value(32)));

    try
    {

		parser::Parser pp;

		pp.generateProgramFromFile("C:/Users/kovacs_s/tek4/BricksVM/program.txt");

        parser.parse(vm);
        instr->setName("scpu_reg_write");

        bricksvm::core::Console::log("VM") << "BricksVM 0.1" << std::endl;
        instr2->setName("svid_init");
        instr2->addParameter(width);
        instr2->addParameter(height);
        instr2->addParameter(color);
        prg->addInstruction(instr2);
        /*instr->setName("scpu_fpreg_write");

        instr->addParameter(param);
        instr->addParameter(param2);
        prg->addInstruction(instr2);
        for (unsigned int i = 0; i < 100; ++i)
        {
            prg->addInstruction(instr);
            prg2->addInstruction(instr);
        }*/
        vm.addProgram("toto", prg);
      //  vm.addProgram("test", prg2);
        parser.parse(vm);
        vm.start();
        while (true);
    }
    catch (std::runtime_error &err)
    {
        bricksvm::core::Console::error("VM") << err.what() << std::endl;
    }

    return 0;
}