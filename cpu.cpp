#include <cpu.h>

void CPU::SetRegisterByNum(int numOfReg, uint16_t val)
{
    this->reg[numOfReg] = val;
}


uint16_t CPU::GetValFromRegisterByNum(int numOfReg)
{
    return this->reg[numOfReg];
}


CPU::CPU()
{

}


CPU::~CPU()
{

}

void CPU::InstructionHandler(uint16_t instr, CPU *cpu)
{
    Parser parser(instr);
    cpu->reg[2] = 2;
    parser.HandleInstruction();
}
