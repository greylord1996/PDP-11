#pragma once
#include <cstdint>
#include <map>
#include <iostream>
#include <cpu.h>

class SingleOpInstruction;
class DoubleOpInstruction;
class DoubleOpRegInstruction;
class ConditionalInstruction;

typedef void (SingleOpInstruction::* SingleOpInstructionExecutor)();
typedef void (DoubleOpInstruction::* DoubleOpInstructionExecutor)();
typedef void (DoubleOpRegInstruction::*DoubleOpRegInstructionExecutor)();
typedef void (ConditionalInstruction::* ConditionalInstructionExecutor)();

class Instruction
{
public:
    class CPU* cpu;

    Instruction();
    virtual ~Instruction();

    virtual void ExecuteInstruction() = 0;
    void privet()
    {
        std::cout << "!!!!\n";
    }
    virtual void who_am_i()
    {
        std::cout << "who_am_i\n";
    }
};

class ConditionalInstruction : public Instruction
{
public:

    ConditionalInstruction();
    ConditionalInstruction(uint16_t opcode, uint16_t offset, class CPU* cpu);
    virtual ~ConditionalInstruction();
    virtual void ExecuteInstruction();
    virtual void who_am_i()
    {
        std::cout << "I am conditional instruction" << std::endl;
    }



private:

    std::map<uint16_t, ConditionalInstructionExecutor> ConditionalInstructionMap;

    int flagOn15Bit;
    uint16_t opcode;
    uint16_t offset;




};

class SingleOpInstruction : public Instruction
{

    typedef void (SingleOpInstruction::* SingleOpInstructionExecutor)();

public:

    friend class Parser;
    SingleOpInstruction();
    SingleOpInstruction(uint16_t opcode, uint16_t mode_1, uint16_t arg_1, class CPU* cpu);
    virtual ~SingleOpInstruction();
    virtual void ExecuteInstruction();
    virtual void who_am_i()
    {
        std::cout << "I am single operands instruction" << std::endl;
    }

private:

    std::map<uint16_t, SingleOpInstructionExecutor> SingleOpInstructionMap;

    //class CPU* cpu;
    int flagOn15Bit;
    uint16_t opcode;
    uint16_t mode_1;
    uint16_t arg_1; // =destination

    void SWAB(); //Swap bytes: rotate 8 bits //OPCODE = 0003
    void JSR(); //	Jump to subroutine //OPCODE = 0040
    void  EMT(); //Emulator trap //OPCODE = 1040
    void  CLR(); //	Clear: dest = 0 //OPCODE = 0050
    void  CLRB (); //Clear: dest = 0 //OPCODE = 1050
    void  COM	(); //  Complement: dest = ~dest //OPCODE = 0051
    void  COMB(); // Complement: dest = ~dest //OPCODE = 1051
    void  INC(); //	Increment: dest += 1 //OPCODE = 0052
    void  INCB();//Increment: dest += 1 //OPCODE = 1052
    void  DEC(); //	Decrement: dest −= 1 //OPCODE = 0053
    void  DECB(); //Decrement: dest −= 1 //OPCODE = 1053
    void  NEG(); //	Negate: dest = −dest //OPCODE = 0054
    void  NEGB(); //Negate: dest = −dest //OPCODE = 1054
    void  ADC(); //	Add carry: dest += C //OPCODE =  0055
    void ADCB(); //Add carry: dest += C //OPCODE = 1055
    void  SBC(); //	Subtract carry: dest −= C //OPCODE = 0056
    void  SBCB(); // Subtract carry: dest −= C//OPCODE = 1056
//  void TST();//	Test: Load src, set flags only //OPCODE = 0057
//  void  TSTB(); //Test: Load src, set flags only //OPCODE = 1057
//  void  ROR(); //	Rotate right 1 bit //OPCODE = 0060
//  void  RORB(); //Rotate right 1 bit //OPCODE = 1060
//  void  ROL(); //	Rotate left 1 bit //OPCODE = 0061
//  void  ROLB(); //Rotate left 1 bit //OPCODE = 1061
//  void  ASR(); //	Shift right: dest >>= 1 //OPCODE = 0062
//  void  ASRB(); //Shift right: dest >>= 1 //OPCODE = 1062
//  void  ASL(); //	Shift left: dest <<= 1 //OPCODE = 0063
//  void  ASLB(); //Shift left: dest <<= 1 //OPCODE = 1063
//  void  MARK(); //	Return from subroutine, skip 0..63 instruction words //OPCODE = 0064
//  void  MTPS(); //	Move to status: PS = src //OPCODE = 1064
//  void  MFPI	(); //Move from previous I space: −(SP) = src //OPCODE = 0065
//  void  MFPD(); //	Move from previous D space: −(SP) = src //OPCODE =  1065
//  void  MTPI	(); //Move to previous I space: dest = (SP)+ //OPCODE = 0066
//  void  MTPD(); //	Move to previous D space: dest = (SP)+ //OPCODE = 1066
//  void  SXT(); //	Sign extend: dest = (16 copies of N flag) //OPCODE = 0067
//  void  MFPS(); //	Move from status: dest = PS //OPCODE = 1067

};

class DoubleOpInstruction : public Instruction
{
public:

    //friend class Parser;
    DoubleOpInstruction();
    DoubleOpInstruction(uint16_t opcode, uint16_t mode_1, uint16_t arg_1, uint16_t mode_2, uint16_t arg_2, class CPU* cpu);
    virtual ~DoubleOpInstruction();
    virtual void ExecuteInstruction();
    virtual void who_am_i()
    {
        std::cout << "I am double operand instruction" << std::endl;
    }


private:

    std::map<uint16_t, DoubleOpInstructionExecutor> DoubleOpInstructionMap;

    int flagOn15Bit;
    uint16_t opcode;
    uint16_t mode_1;
    uint16_t arg_1;
    uint16_t mode_2;
    uint16_t arg_2;


//    MOV(); // Move: arg_2 = arg_1 // OPCODE  = 01
//    MOVB(); //Move: arg_2 = arg_1 // OPCODE = 11
//    CMP(); //Compare: compute arg_1 − arg_2, set flags only // OPCODE = 02
//    CMPB(); //Compare: compute arg_1 − arg_2, set flags only // OPCODE = 12
//    BIT(); //Bit test: compute arg_2 & arg_1, set flags only // OPCODE = 03
//    BITB(); //Bit test: compute arg_2 & arg_1, set flags only // OPCODE = 13
//    BIC(); //Bit clear: arg_2 &= ~arg_1 // OPCODE = 04
//    BICB(); //Bit clear: arg_2 &= ~arg_1 // OPCODE = 14
//    BIS(); //Bit set, a.k.a. logical OR: arg_2 |= arg_1 //OPCODE = 05
//    BISB(); //Bit set, a.k.a. logical OR: arg_2 |= arg_1 //OPCODE = 15
//    ADD();	//Add, arg_2 += arg_1 // OPCODE = 06
//    SUB(); //Add, arg_2 += arg_1 // OPCODE = 16
};

class DoubleOpRegInstruction : public Instruction
{
public:


    //friend class Parser;
    DoubleOpRegInstruction();
    DoubleOpRegInstruction(uint16_t opcode, uint16_t arg_1, uint16_t mode_2, uint16_t arg_2, class CPU* cpu);
    virtual ~DoubleOpRegInstruction();
    virtual void ExecuteInstruction();
    virtual void who_am_i()
    {
        std::cout << "I am double operand-register instruction" << std::endl;
    }


private:

    std::map<uint16_t, DoubleOpRegInstructionExecutor> DoubleOpRegInstructionMap;

    int flagOn15Bit;
    uint16_t opcode;
    uint16_t arg_1;
    uint16_t mode_2;
    uint16_t arg_2;

//    MUL(); //Multiply: (R,R+1) = R × src; OPCODE  = 070
//    DIV();  //Divide: Compute (R,R+1) ÷ src; quotient in R, remainder in R+1; OPCODE  = 071
//    ASH(); // Arithmetic shift: R <<= src, shift amount may be −32..31.; OPCODE  = 072
//    ASHC(); //	Arithmetic shift combined: (R,R+1) <<= src, shift amount may be −32..31. ; OPCODE  = 073
//    XOR(); //Exclusive or: dest ^= reg (word only) ; OPCODE  = 074
//    //075	(floating-point operations)
//    //076	(system instructions)
//    SOB(); // Subtract one and branch: Decrement register, if result non-zero, branch backward 0..63 words. ; OPCODE  = 077

};
