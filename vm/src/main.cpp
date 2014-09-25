#include <iostream>
#include "VirtualMachine.hpp"
#include "ConfigurationParser.hpp"
#include "interpreter/ValueParameter.hpp"

int main()
{
    using namespace bricksvm;

    ConfigurationParser							parser("config/config.json");
    VirtualMachine								vm;
    std::shared_ptr<interpreter::Program>		prg(new interpreter::Program);
    std::shared_ptr<interpreter::Program>		prg2(new interpreter::Program);
    std::shared_ptr<interpreter::Instruction>	instr(new interpreter::Instruction(0));
    interpreter::Value							val(0);
    std::shared_ptr<interpreter::AParameter>	param(new interpreter::ValueParameter(val));


    try
    {
     //   parser.parse(vm);
        instr->setName("vm_jmp");
        instr->addParameter(param);
        for (unsigned int i = 0; i < 1000; ++i)
        {
            prg->addInstruction(instr);
            prg2->addInstruction(instr);
        }
        vm.addProgram("toto", prg);
        vm.addProgram("test", prg2);
        vm.start();
        while (true);
    }
    catch (std::runtime_error &err)
    {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}