#include <instruction.h>
#include <iostream>


ConditionalInstruction::ConditionalInstruction(uint16_t opcode, uint16_t offset)
{
    this->opcode = opcode;
    this->offset = offset;
}

SingleOpInstruction::SingleOpInstruction(uint16_t opcode, uint16_t mode_1, uint16_t arg_1)
{
    this->opcode = opcode;
    this->mode_1 = mode_1;
    this->arg_1 = arg_1;
}

DoubleOpInstruction::DoubleOpInstruction(uint16_t opcode, uint16_t mode_1, uint16_t arg_1, uint16_t mode_2, uint16_t arg_2)
{
    this->opcode = opcode;
    this->mode_1 = mode_1;
    this->arg_1 = arg_1;
    this->mode_2 = mode_2;
    this->arg_2 = arg_2;
}

DoubleOpRegInstruction::DoubleOpRegInstruction(uint16_t opcode, uint16_t arg_1, uint16_t mode_2, uint16_t arg_2)
{
    this->opcode = opcode;
    this->arg_1 = arg_1;
    this->mode_2 = mode_2;
    this->arg_2 = arg_2;
}


Instruction::Instruction()
{

}

Instruction::~Instruction()
{

}


ConditionalInstruction::ConditionalInstruction()
{

}

ConditionalInstruction::~ConditionalInstruction()
{

}

void ConditionalInstruction::ExecuteInstruction()
{
    std::cout << "Execute conditional instruction\n";
}

SingleOpInstruction::SingleOpInstruction()
{

}

SingleOpInstruction::~SingleOpInstruction()
{

}

void SingleOpInstruction::ExecuteInstruction()
{
    std::cout << "Execute single operation instruction\n";
}

DoubleOpInstruction::DoubleOpInstruction()
{

}

DoubleOpInstruction::~DoubleOpInstruction()
{

}

void DoubleOpInstruction::ExecuteInstruction()
{
    std::cout << "Execute double operation instruction\n";
}

DoubleOpRegInstruction::DoubleOpRegInstruction()
{

}

DoubleOpRegInstruction::~DoubleOpRegInstruction()
{

}

void DoubleOpRegInstruction::ExecuteInstruction()
{
    std::cout << "Execute double operation-register instruction\n";
}

