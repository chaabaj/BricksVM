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
    std::shared_ptr<interpreter::Program>       prg;
    std::shared_ptr<interpreter::Program>       prg2;

    try
    {

		parser::Parser pp;

        bricksvm::core::Console::log("VM") << "Compiling program" << std::endl;
        prg = pp.generateProgramFromFile("programs/save_text.s");
        prg2 = pp.generateProgramFromFile("programs/hello_world.s");

        bricksvm::core::Console::success("VM") << "Program compiled successfully" << std::endl;
        bricksvm::core::Console::log("VM") << "BricksVM 0.1" << std::endl;
        vm.addProgram("toto", prg);
        vm.addProgram("bite", prg2);
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