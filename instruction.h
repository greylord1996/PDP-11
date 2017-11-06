#pragma once
#include <cstdint>
#include <map>

void (SingleOpInstruction::* SingleOpInstructionExecutor)();
void (DoubleOpInstruction::* DoubleOpInstructionExecutor)();
void (DoubleOpRegInstruction::*DoubleOpRegInstructionExecutor)();
void (ConditionalInstruction::* ConditionalInstructionExecutor)();

class Instruction
{
public:

    Instruction();
    ~Instruction();

    virtual void ExecuteInstruction() = 0;
};

class ConditionalInstruction : public Instruction
{
public:

    ConditionalInstruction();
    virtual ~ConditionalInstruction();
    virtual void ExecuteInstruction();

private:

    std::map<uint16_t, ConditionalInstructionExecutor> ConditionalInstructionMap;

    int flagOn15Bit;
    uint16_t opcode;
    uint16_t offset;


};

class SingleOpInstruction : public Instruction
{
public:

    SingleOpInstruction();
    virtual ~SingleOpInstruction();
    virtual void ExecuteInstruction();

private:

    std::map<uint16_t, SingleOpInstructionExecutor> SingleOpInstructionMap;

    int flagOn15Bit;
    uint16_t opcode;
    uint16_t mode_1;
    uint16_t arg_1; // =destination

    SWAB(); //Swap bytes: rotate 8 bits //OPCODE = 0003
    JSR(); //	Jump to subroutine //OPCODE = 0040
    EMT(); //Emulator trap //OPCODE = 1040
    CLR(); //	Clear: dest = 0 //OPCODE = 0050
    CLRB (); //Clear: dest = 0 //OPCODE = 1050
    COM	(); //  Complement: dest = ~dest //OPCODE = 0051
    COMB(); // Complement: dest = ~dest //OPCODE = 1051
    INC(); //	Increment: dest += 1 //OPCODE = 0052
    INCB();//Increment: dest += 1 //OPCODE = 1052
    DEC(); //	Decrement: dest −= 1 //OPCODE = 0053
    DECB(); //Decrement: dest −= 1 //OPCODE = 1053
    NEG(); //	Negate: dest = −dest //OPCODE = 0054
    NEGB(); //Negate: dest = −dest //OPCODE = 1054
    ADC(); //	Add carry: dest += C //OPCODE =  0055
    ADCB(); //Add carry: dest += C //OPCODE = 1055
    SBC(); //	Subtract carry: dest −= C //OPCODE = 0056
    SBCB(); // Subtract carry: dest −= C//OPCODE = 1056
    TST();//	Test: Load src, set flags only //OPCODE = 0057
    TSTB(); //Test: Load src, set flags only //OPCODE = 1057
    ROR(); //	Rotate right 1 bit //OPCODE = 0060
    RORB(); //Rotate right 1 bit //OPCODE = 1060
    ROL(); //	Rotate left 1 bit //OPCODE = 0061
    ROLB(); //Rotate left 1 bit //OPCODE = 1061
    ASR(); //	Shift right: dest >>= 1 //OPCODE = 0062
    ASRB(); //Shift right: dest >>= 1 //OPCODE = 1062
    ASL(); //	Shift left: dest <<= 1 //OPCODE = 0063
    ASLB(); //Shift left: dest <<= 1 //OPCODE = 1063
    MARK(); //	Return from subroutine, skip 0..63 instruction words //OPCODE = 0064
    MTPS(); //	Move to status: PS = src //OPCODE = 1064
    MFPI	(); //Move from previous I space: −(SP) = src //OPCODE = 0065
    MFPD(); //	Move from previous D space: −(SP) = src //OPCODE =  1065
    MTPI	(); //Move to previous I space: dest = (SP)+ //OPCODE = 0066
    MTPD(); //	Move to previous D space: dest = (SP)+ //OPCODE = 1066
    SXT(); //	Sign extend: dest = (16 copies of N flag) //OPCODE = 0067
    MFPS(); //	Move from status: dest = PS //OPCODE = 1067

};

class DoubleOpInstruction : public Instruction
{
public:

    DoubleOpInstruction();
    virtual ~DoubleOpInstruction();
    virtual void ExecuteInstruction();


private:

    std::map<uint16_t, DoubleOpInstructionExecutor> DoubleOpInstructionMap;

    int flagOn15Bit;
    uint16_t opcode;
    uint16_t mode_1;
    uint16_t arg_1;
    uint16_t mode_2;
    uint16_t arg_2;


    MOV(); // Move: arg_2 = arg_1 // OPCODE  = 01
    MOVB(); //Move: arg_2 = arg_1 // OPCODE = 11
    CMP(); //Compare: compute arg_1 − arg_2, set flags only // OPCODE = 02
    CMPB(); //Compare: compute arg_1 − arg_2, set flags only // OPCODE = 12
    BIT(); //Bit test: compute arg_2 & arg_1, set flags only // OPCODE = 03
    BITB(); //Bit test: compute arg_2 & arg_1, set flags only // OPCODE = 13
    BIC(); //Bit clear: arg_2 &= ~arg_1 // OPCODE = 04
    BICB(); //Bit clear: arg_2 &= ~arg_1 // OPCODE = 14
    BIS(); //Bit set, a.k.a. logical OR: arg_2 |= arg_1 //OPCODE = 05
    BISB(); //Bit set, a.k.a. logical OR: arg_2 |= arg_1 //OPCODE = 15
    ADD();	//Add, arg_2 += arg_1 // OPCODE = 06
    SUB(); //Add, arg_2 += arg_1 // OPCODE = 16
};

class DoubleOpRegInstruction : public Instruction
{
public:

    DoubleOpRegInstruction();
    virtual ~DoubleOpRegInstruction();
    virtual void ExecuteInstruction();


private:

    std::map<uint16_t, DoubleOpRegInstructionExecutor> DoubleOpRegInstructionMap;

    int flagOn15Bit;
    uint16_t opcode;
    uint16_t arg_1;
    uint16_t mode_2;
    uint16_t arg_2;

    MUL(); //Multiply: (R,R+1) = R × src; OPCODE  = 070
    DIV();  //Divide: Compute (R,R+1) ÷ src; quotient in R, remainder in R+1; OPCODE  = 071
    ASH(); // Arithmetic shift: R <<= src, shift amount may be −32..31.; OPCODE  = 072
    ASHC(); //	Arithmetic shift combined: (R,R+1) <<= src, shift amount may be −32..31. ; OPCODE  = 073
    XOR(); //Exclusive or: dest ^= reg (word only) ; OPCODE  = 074
    //075	(floating-point operations)
    //076	(system instructions)
    SOB(); // Subtract one and branch: Decrement register, if result non-zero, branch backward 0..63 words. ; OPCODE  = 077

};
