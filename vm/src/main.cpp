#include <iostream>
#include "VirtualMachine.hpp"
#include "interpreter/ValueParameter.hpp"

int main()
{
	using namespace bricksvm;

	VirtualMachine								vm;
	std::shared_ptr<interpreter::Program>		prg(new interpreter::Program);
	std::shared_ptr<interpreter::Program>		prg2(new interpreter::Program);
	std::shared_ptr<interpreter::Instruction>	instr(new interpreter::Instruction);
	interpreter::Value							val(std::string("test"));
	std::shared_ptr<interpreter::AParameter>	param(new interpreter::ValueParameter(val));
	

	instr->setName("call");
	instr->addParameter(param);
	for (unsigned int i = 0; i < 100; ++i)
	{
		prg->addInstruction(instr);
		prg2->addInstruction(instr);
	}
	vm.addProgram("toto", prg);
	vm.addProgram("test", prg2);
	vm.start();
	while (true);
	return 0;
}