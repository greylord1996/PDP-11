#pragma once
#include <cstdint>
#include <parser.h>
#include <RAM.h>

class CPU
{
private:

    RAM* ram;
    uint16_t  reg[6] = {};
    bool T = false;
    bool N = false;
    bool Z = false;
    bool V = false;
    bool C =  false;

public:

    void SetRegisterByNum(int numOfReg, uint16_t val);

    uint16_t GetValFromRegisterByNum(int numOfReg);



    CPU();

    ~CPU();

    void InstructionHandler(uint16_t  instr, CPU* cpu);

};

