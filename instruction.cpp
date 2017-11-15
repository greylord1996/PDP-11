#include <instruction.h>
#include <iostream>
#include <cassert>


ConditionalInstruction::ConditionalInstruction(uint16_t opcode, uint16_t offset)
{
    this->opcode = opcode;
    this->offset = offset;
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

//Single operand instruction!!! In this section all methods of class SingleOpInstruction will be implemented

//Constructor. Here we init map <opcode, pointer to called funcion>

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




/*Single operand instruction case: START*/

SingleOpInstruction::SingleOpInstruction()
{

}

//Constructor.

SingleOpInstruction::SingleOpInstruction(uint16_t opcode, uint16_t mode_1, uint16_t arg_1)
{
    //Init instructions parts
    this->opcode = opcode;
    this->mode_1 = mode_1;
    this->arg_1 = arg_1;

    //In this constructor must be inited the functions. Here we init map <opcode, pointer to called funcion>

    this->SingleOpInstructionMap[00003] = &SingleOpInstruction::SWAB;
    this->SingleOpInstructionMap[01040] = &SingleOpInstruction::EMT;
    this->SingleOpInstructionMap[00050] = &SingleOpInstruction::CLR;
    this->SingleOpInstructionMap[01050] = &SingleOpInstruction::CLRB;
    this->SingleOpInstructionMap[00051] = &SingleOpInstruction::COM;
    this->SingleOpInstructionMap[01051] = &SingleOpInstruction::COMB;
    this->SingleOpInstructionMap[00052] = &SingleOpInstruction::INC;
    this->SingleOpInstructionMap[01052] = &SingleOpInstruction::INCB;
    this->SingleOpInstructionMap[00053] = &SingleOpInstruction::DEC;
    this->SingleOpInstructionMap[01053] = &SingleOpInstruction::DECB;
    this->SingleOpInstructionMap[00054] = &SingleOpInstruction::NEG;
    this->SingleOpInstructionMap[01054] = &SingleOpInstruction::NEGB;
    this->SingleOpInstructionMap[00055] = &SingleOpInstruction::ADC;
    this->SingleOpInstructionMap[01055] = &SingleOpInstruction::ADCB;
    this->SingleOpInstructionMap[00056] = &SingleOpInstruction::SBC;
    this->SingleOpInstructionMap[01056] = &SingleOpInstruction::SBCB;
}

SingleOpInstruction::~SingleOpInstruction()
{

}





void SingleOpInstruction::ExecuteInstruction()
{
    std::cout << "Execute single operation instruction called\n";
    SingleOpInstructionExecutor single_op_instr_executor = this->SingleOpInstructionMap[this->opcode];
    assert(single_op_instr_executor); //BLED. Here was the complete whore
    (this->*single_op_instr_executor)();
}


//Single operand instruction!!! In this section all methods of class SingleOpInstruction will be implemented

void SingleOpInstruction::SWAB()
{
    std::cout << "SWAB" << std::endl;
}

void SingleOpInstruction::EMT()
{
    std::cout << "EMT" << std::endl;
}

void SingleOpInstruction::CLR()
{
    std::cout << "CLR" << std::endl;
}

void SingleOpInstruction::CLRB()
{
    std::cout << "CLRB" << std::endl;
}

void SingleOpInstruction::COM()
{
    std::cout << "COM" << std::endl;
}

void SingleOpInstruction::COMB()
{
    std::cout << "COMB" << std::endl;
}

void SingleOpInstruction::INC()
{
    std::cout << "INC" << std::endl;
}

void SingleOpInstruction::INCB()
{
    std::cout << "INCB" << std::endl;
}

void SingleOpInstruction::DEC()
{
    std::cout << "DEC" << std::endl;
}

void SingleOpInstruction::DECB()
{
    std::cout << "DECB" << std::endl;
}

void SingleOpInstruction::NEG()
{
    std::cout << "NEG" << std::endl;
}

void SingleOpInstruction::NEGB()
{
    std::cout << "NEGB" << std::endl;
}

void SingleOpInstruction::ADC()
{
    std::cout << "ADC\n";
}

void SingleOpInstruction::ADCB()
{
    std::cout << "ADCBlyat\n";
}



void SingleOpInstruction::SBC()
{
    std::cout << "SBC" << std::endl;
}

void SingleOpInstruction::SBCB()
{
    std::cout << "SBCB" << std::endl;
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

