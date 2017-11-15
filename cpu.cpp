#include <cpu.h>

void CPU::SetRegisterByNum(int numOfReg, uint16_t val)
{
    this->reg[numOfReg] = val;
}

void CPU::IncRegisterByX(int numOfReg, int x)
{
    this->reg[numOfReg] += x;
}

void CPU::DecRegisterByX(int numOfReg, int x)
{
    this->reg[numOfReg] -= x;
}


uint16_t CPU::GetValFromRegisterByNum(int numOfReg)
{
    return this->reg[numOfReg];
}

RAM *CPU::GetRam()
{
    return this->ram;
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
    return instruction_handler.HandleInstruction();
}
