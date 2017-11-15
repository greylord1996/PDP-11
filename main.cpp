#include <iostream>
#include <parser.h>
#include <cstdint>
#include <bitset>
#include <cassert>
#include <cpu.h>
//#include <instruction.h>

using namespace std;

int main()
{
    uint16_t instruction;
    std::cout << "Enter instruction " ;
    std::cin >> instruction;

    std::string binary_code = std::bitset<16>(instruction).to_string(); //to binary
    std::cout << "binary_code = " << binary_code << std::endl;

    CPU cpu;
    cpu.InstructionHandler(instruction, &cpu);
    //std::cout << cpu.reg[2] << std::endl;

    return 0;
}

