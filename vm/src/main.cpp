#include <iostream>
#include "VirtualMachine.hpp"
#include "ConfigurationParser.hpp"
#include "interpreter/ValueParameter.hpp"

#include "parser/Parser.hpp"

#include "core/Console.hpp"


int main(int ac, char **av)
{
    using namespace bricksvm;

    ConfigurationParser                         cfgParser("config/config.json");
    VirtualMachine                              vm;
    std::shared_ptr<interpreter::Program>       prg;
    std::shared_ptr<interpreter::Program>       prg2;

    try
    {

		parser::Parser pp;
        bricksvm::core::Console::log("VM") << "BricksVM 0.1" << std::endl;
        bricksvm::core::Console::log("VM") << "Compiling program" << std::endl;
        bricksvm::core::throwIf<std::runtime_error>(ac < 2, "No program found");
        for (int i = 1; i < ac; ++i)
        {
            prg = pp.generateProgramFromFile(av[i]);
            vm.addProgram(core::toString(i), prg);
        }
        bricksvm::core::Console::success("VM") << "Program compiled successfully" << std::endl;
        cfgParser.parse(vm);
        vm.start();
        while (true);
    }
    catch (std::exception &err)
    {
        bricksvm::core::Console::error("VM") << err.what() << std::endl;
    }
    return 0;
}