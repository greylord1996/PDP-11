#pragma once
#include <iostream>
#include <cstdint>

enum wordVersusbyte{WORD, BYTE}; //The symbol "0" or "1" in an opcode refers to a 0 for the word version of the instrucion and 1 for the byte version of the instruction

enum INSTRUCTION_TYPE{SINGLE_OP_INSTR, DOUBLE_OP_REG_INSTR, DOUBLE_OP_INSTR, CONDITIONAL_INSTR}; //Go to Wiki - https://en.wikipedia.org/wiki/PDP-11_architecture

class Parser
{
public:
    Parser();
    ~Parser();
    std::string binary_format; // for debug

    uint16_t instruction_name;
    uint16_t opcode;
    uint16_t mode_1;
    uint16_t arg_1;
    uint16_t mode_2;
    uint16_t arg_2;
    uint16_t offset;



    Parser(uint16_t instruction_name);

    void PrintInstruction(); //for debug

    int flagOn15Bit; //Flag for checking last bit.  The symbol "0" or "1" in an opcode refers to a 0 for the word version of the instrucion and 1 for the byte version of the instruction
    int flagOnOperandsNumber; //This check how many operands in function

    void CheckLastBit(); //Method for checking last bit
    void CountOperands(); //Method for counting the number of operands in instruction, in other words - get type of instraction


    /*Two-operand instructions require a register source operand*/
    void GetOpcodeInDoubleRegOpCase();
    void GetArg_1_InDoubleRegOpCase();
    void GetMode_2_InDoubleRegOpCase();
    void GetArg_2_InDoubleRegOpCase();

    /*Conditional branch instructions*/
    void GetOpcodeInBranchOpCase();
    void GetOffsetInBranchOpCase();

    /*Single-operand instructions*/
    void GetOpcodeInSingleOpCase();
    void GetModeInSingleCase();
    void GetArgs_1InSingleCase();

    /*Double-operand instructions*/
    void GetOpcodeInDoubleOpCase();
    void GetMode_1_InDoubleOpCase();
    void GetMode_2_InDoubleOpCase();
    void GetArg_1_InDoubleOpCase();
    void GetArg_2_InDoubleOpCase();

    /*Algorithm for parsing*/
    void MakeParse();


};

