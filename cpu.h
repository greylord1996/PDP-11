#pragma once
#include <cstdint>
#include <decision_maker.h>
#include <RAM.h>

enum GeneralRegisterAddressingModes
{
    REGISTER = 0,
    REGISTER_DEFFERED = 1,
    AUTOINCREMENT = 2,
    AUTOINCREMENT_DEFFERED = 3,
    AUTODECREMENT =  4,
    AUTODECREMENT_DEFFERED = 5,
    INDEX = 6,
    INDEX_DEFFERED = 7
};

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

    void IncRegisterByX(int numOfReg, int x);
    void DecRegisterByX(int numOfReg, int x);

    uint16_t GetValFromRegisterByNum(int numOfReg);

    RAM* GetRam();


    CPU();

    ~CPU();

    void ProcessInstruction(uint16_t  instr, CPU* cpu);

};

