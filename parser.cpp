#include <parser.h>
#include <iostream>
#include <bitset>


Parser::Parser()
{

}


Parser::~Parser()
{

}


Parser::Parser(uint16_t instruction)
{
    this->instruction_name = instruction;
}


void Parser::PrintInstruction()
{
    std::cout << "Current instruction is " << this->instruction_name << std::endl;
}


void Parser::CheckLastBit() //Word VS Byte checking
{
    if(this->instruction_name & 0x8000) // 0x8000 = 1000000000000000
        this->flagOn15Bit = BYTE;
    else
        this->flagOn15Bit = WORD;

    std::cout << "flagOn15Bit = " << this->flagOn15Bit << std::endl;
}


void Parser::CountOperands()
{
    if((this->instruction_name & 0x7800) == 0x0800) //0000100000000000 = 0x800
    {
        this->flagOnOperandsNumber = SINGLE_OP_INSTR;
    }

    else if((this->instruction_name & 0x7800) == 0) //0111100000000000 = 0x7800
    {
        this->flagOnOperandsNumber = CONDITIONAL_INSTR;
    }

    else if ((this->instruction_name & 0xF000) == 0x7000)
    {
        this->flagOnOperandsNumber = DOUBLE_OP_REG_INSTR;
    }

    else
    {
        this->flagOnOperandsNumber = DOUBLE_OP_INSTR;
    }

    std::cout << "flagOnOperandsNumber = " << this->flagOnOperandsNumber << std::endl;
}









//********************************************************************BRANCH_CONDITIONAL_CASE_BEGIN****************************************************************************//


void Parser::GetOpcodeInBranchOpCase()
{
    this->opcode = (this->instruction_name) >> 8;
    binary_format = std::bitset<8>(this->opcode).to_string(); //to binary
    std::cout << "Binary opcode format in branch is " << binary_format << std::endl;
}


void Parser::GetOffsetInBranchOpCase()
{
    this->offset = this->instruction_name << 8;
    this->offset = this->offset >> 8;

    binary_format = std::bitset<8>(this->offset).to_string();
    std::cout << "Binary offset format in branch is " << binary_format << std::endl;
}


//*********************************************************************BRANCH_CONDITIONAL_CASE_END*****************************************************************************//


                                                                                                                            /*!!!!!!!!!!!!!*/


//************************************************************************SINGLE_OPERATION_CASE_BEGIN***************************************************************************//


void Parser::GetOpcodeInSingleOpCase()
{
    this->opcode = (this->instruction_name & 0xFFC0) >> 6; //1111111111000000
    binary_format = std::bitset<16>(this->opcode).to_string(); //to binary
    std::cout << "Binary opcode format in SingleOpCase is " << binary_format << std::endl;

}

void Parser::GetModeInSingleCase()
{
    this->mode_1 = (this->instruction_name & 0x38) >> 3;
    binary_format = std::bitset<3>(this->mode_1).to_string();
    std::cout << "Binary format of mode_1 in SingleCase " << binary_format << std::endl;

}

void Parser::GetArgs_1InSingleCase()
{
    this->arg_1 = (this->instruction_name & 0x7);
    binary_format = std::bitset<3>(this->arg_1).to_string();
    std::cout << "Binary format of arg_1 in SingleCase " << binary_format << std::endl;

}


//*********************************************************************SINGLE_OPERATION_CASE_END********************************************************************************//


                                                                                                                            /*!!!!!!!!!!!!!*/


//********************************************************************DOUBLE_OPERATION_CASE_BEGIN******************************************************************************//


void Parser::GetOpcodeInDoubleOpCase()
{
    this->opcode = (this->instruction_name & 0xF000) >> 12;
    binary_format = std::bitset<16>(this->opcode).to_string(); //to binary
    std::cout << "Binary opcode format in DoubleOpCase is " << binary_format << std::endl;
}

void Parser::GetMode_1_InDoubleOpCase()
{
    this->mode_1 = (this->instruction_name & 0xE00) >> 9;
    binary_format = std::bitset<4>(this->mode_1).to_string(); //to binary
    std::cout << "Binary format of mode_1 is " << binary_format << std::endl;
}

void Parser::GetArg_1_InDoubleOpCase()
{
    this->arg_1 = (this->instruction_name & 0x1C0) >> 6;
    binary_format = std::bitset<4>(this->arg_1).to_string(); //to binary
    std::cout << "Binary format of arg_1 is " << binary_format << std::endl;
}

void Parser::GetMode_2_InDoubleOpCase()
{
    this->mode_2 = (this->instruction_name & 0x38) >> 3;
    binary_format = std::bitset<4>(this->mode_2).to_string(); //to binary
    std::cout << "Binary format of mode_2 is " << binary_format << std::endl;
}

void Parser::GetArg_2_InDoubleOpCase()
{
    this->arg_2 = (this->instruction_name & 0x7);
    binary_format = std::bitset<4>(this->arg_2).to_string(); //to binary
    std::cout << "Binary format of arg_2 is " << binary_format << std::endl;
}


//*********************************************************************DOUBLE_OPERATION_CASE_END*******************************************************************************//


                                                                                                                            /*!!!!!!!!!!!!!*/


//*************************************************************DOUBLE_REGISTER_OPERATION_CASE_BEGIN**************************************************************************//


void Parser::GetOpcodeInDoubleRegOpCase()
{
    this->opcode = (this->instruction_name & 0xFE00) >> 9;
    binary_format = std::bitset<16>(this->opcode).to_string(); //to binary
    std::cout << "Binary opcode format in DoubleRegOpCase is " << binary_format << std::endl;

}

void Parser::GetArg_1_InDoubleRegOpCase()
{
    this->arg_1 = (this->instruction_name & 0x1C0) >> 6;
    binary_format = std::bitset<4>(this->arg_1).to_string(); //to binary
    std::cout << "Binary format of arg_1 is " << binary_format << std::endl;
}

void Parser::GetMode_2_InDoubleRegOpCase()
{
    this->mode_2 = (this->instruction_name & 0x38) >> 3;
    binary_format = std::bitset<4>(this->mode_2).to_string(); //to binary
    std::cout << "Binary format of mode_2 is " << binary_format << std::endl;
}

void Parser::GetArg_2_InDoubleRegOpCase()
{
    this->arg_2 = (this->instruction_name & 0x7);
    binary_format = std::bitset<4>(this->arg_2).to_string(); //to binary
    std::cout << "Binary format of arg_2 is " << binary_format << std::endl;

}


//*************************************************************DOUBLE_REGISTER_OPERATION_CASE_END****************************************************************************//


//*********************************************************************************ALGORITHM***************************************************************************************//


void Parser::MakeParse()
{
    PrintInstruction();
    CheckLastBit();
    CountOperands();
    switch(flagOnOperandsNumber)
    {
        case(SINGLE_OP_INSTR):
        {
            GetOpcodeInSingleOpCase();
            GetModeInSingleCase();
            GetArgs_1InSingleCase();
            break;
        }

        case(DOUBLE_OP_REG_INSTR):
        {
            GetOpcodeInDoubleRegOpCase();
            GetArg_1_InDoubleRegOpCase();
            GetMode_2_InDoubleRegOpCase();
            GetArg_2_InDoubleRegOpCase();
            break;
        }

        case(DOUBLE_OP_INSTR):
        {
            GetOpcodeInDoubleOpCase();
            GetMode_1_InDoubleOpCase();
            GetArg_1_InDoubleOpCase();
            GetMode_2_InDoubleOpCase();
            GetArg_2_InDoubleOpCase();
            break;
        }



        case(CONDITIONAL_INSTR):
        {
            GetOpcodeInBranchOpCase();
            GetOffsetInBranchOpCase();
            break;
        }
    }
}
