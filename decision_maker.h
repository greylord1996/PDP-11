#pragma once

#include <instruction.h>
#include <parser.h>
#include <cpu.h>

class InstructionHandler
{
public:
    class CPU* cpu;
    uint16_t instruction;
    InstructionHandler(uint16_t instruction, CPU* cpu);
    void HandleInstruction();
    ~InstructionHandler();
};
