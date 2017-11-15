#include <instruction.h>
#include <iostream>
#include <cassert>
//#include <cpu.h>


ConditionalInstruction::ConditionalInstruction(uint16_t opcode, uint16_t offset, CPU *cpu, int flagOn15Bit)
{
    this->opcode = opcode;
    this->offset = offset;
    this->cpu = cpu;
    this->flagOn15Bit = flagOn15Bit;
}

DoubleOpInstruction::DoubleOpInstruction(uint16_t opcode, uint16_t mode_1, uint16_t arg_1, uint16_t mode_2, uint16_t arg_2, CPU *cpu, int flagOn15Bit)
{
    this->opcode = opcode;
    this->mode_1 = mode_1;
    this->arg_1 = arg_1;
    this->mode_2 = mode_2;
    this->arg_2 = arg_2;
    this->cpu = cpu;
    this->flagOn15Bit = flagOn15Bit;
}

DoubleOpRegInstruction::DoubleOpRegInstruction(uint16_t opcode, uint16_t arg_1, uint16_t mode_2, uint16_t arg_2, CPU *cpu, int flagOn15Bit)
{
    this->opcode = opcode;
    this->arg_1 = arg_1;
    this->mode_2 = mode_2;
    this->arg_2 = arg_2;
    this->cpu = cpu;
    this->flagOn15Bit = flagOn15Bit;
}

//Base class Instruction

Instruction::Instruction()
{

}

Instruction::~Instruction()
{

}

uint16_t Instruction::GetArgGeneralRegisterAddressingModes(uint16_t mode, uint16_t reg, int flagOn15Bit)
{
    uint16_t value = 0;

    switch(mode)
    {
        //The operand is in Rn
        case(REGISTER):
        {
                value = this->cpu->GetValFromRegisterByNum(reg);
                break;
        }
        //Rn contains the address of the operand
        case(REGISTER_DEFFERED):
        {
            if(flagOn15Bit == WORD)
                value = this->cpu->GetRam()->GetWordByAddr(cpu->GetValFromRegisterByNum(reg));
            else if(flagOn15Bit == BYTE)
                value = this->cpu->GetRam()->GetWordByAddr(cpu->GetValFromRegisterByNum(reg));
            break;
        }

        //Rn contains the address of the operand, then increment Rn
        case(AUTOINCREMENT):
        {
            if(flagOn15Bit == WORD)
            {
                value = this->cpu->GetRam()->GetWordByAddr(cpu->GetValFromRegisterByNum(reg));
                //this->cpu->reg[reg] += 2;
                this->cpu->IncRegisterByX(reg, 2);
            }

            if(flagOn15Bit == BYTE)
            {
                value =  this->cpu->GetRam()->GetByteByAddr(cpu->GetValFromRegisterByNum(reg));
                this->cpu->IncRegisterByX(reg, 1);
            }

            break;
        }

        //Rn contains the address of the address, then increment Rn by 2
         case(AUTOINCREMENT_DEFFERED):
        {
            value = this->cpu->GetRam()->GetWordByAddr(this->cpu->GetRam()->GetWordByAddr(cpu->GetValFromRegisterByNum(reg)));
            this->cpu->IncRegisterByX(reg, 2);
            break;
        }

        //Decrement Rn, then use it as the address
        case(AUTODECREMENT):
        {
             if(flagOn15Bit == WORD)
            {
                 this->cpu->DecRegisterByX(reg, 2);
                 value = this->cpu->GetRam()->GetWordByAddr(cpu->GetValFromRegisterByNum(reg));
            }

            if(flagOn15Bit == BYTE)
            {
                this->cpu->DecRegisterByX(reg, 1);
                value =  this->cpu->GetRam()->GetByteByAddr(cpu->GetValFromRegisterByNum(reg));
             }

        break;
        }

        //Decrement Rn by 2, then use it as the address of the address
        case(AUTODECREMENT_DEFFERED):
        {
            this->cpu->DecRegisterByX(reg, 2);
            value = this->cpu->GetRam()->GetWordByAddr(this->cpu->GetRam()->GetWordByAddr(cpu->GetValFromRegisterByNum(reg)));
            break;
        }

        case(INDEX):
        {

        }

        case(INDEX_DEFFERED):
        {

        }


    }

    return value;
}

CPU *Instruction::getCPU()
{
    return this->cpu;
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

SingleOpInstruction::SingleOpInstruction(uint16_t opcode, uint16_t mode_1, uint16_t arg_1, CPU *cpu, int flagOn15Bit)
{
    //Init instructions parts
    this->opcode = opcode;
    this->mode_1 = mode_1;
    this->arg_1 = arg_1;
    this->cpu = cpu;
    this->flagOn15Bit = flagOn15Bit;

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
 //   this->cpu->reg[0];//!!!!!!!!!!!!!!!!!!!!!!!!!
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
    uint16_t val = GetArgGeneralRegisterAddressingModes(this->mode_1, this->arg_1, this->flagOn15Bit);
    std::cout << "val = " << val << std::endl;
    val++;
    this->arg_1 =val;
    this->cpu->SetRegisterByNum(this->arg_1, val);

    std::cout << "New val in register " << this->cpu->GetValFromRegisterByNum(this->arg_1)<< std::endl;
    //return this->cpu;
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

