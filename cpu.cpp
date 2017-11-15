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

void CPU::ProcessInstruction(uint16_t instr, CPU *cpu)
{
    InstructionHandler instruction_handler(instr, cpu);
    //std::cout << cpu->GetValFromRegisterByNum(0) << std::endl;
    instruction_handler.HandleInstruction();
}
