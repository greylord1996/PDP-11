#include <iostream>
#include <cstdint>
#include <bitset>
#include <cpu.h>
#include <RAM.h>


using namespace std;

int main()
{
//    uint16_t instruction;
//    std::cout << "Enter instruction " ;
//    std::cin >> instruction;

//    std::string binary_code = std::bitset<16>(instruction).to_string(); //to binary
//    std::cout << "binary_code = " << binary_code << std::endl;

//    CPU cpu;
//    cpu.ProcessInstruction(instruction, &cpu);

    RAM ram;
    //ram.SetWordOnAddr(12, 35655);
    //ram.GetWordByAddr(12);
    //ram.GetByteByAddr(12);
    ram.SetByteOnAddr(12, 139);
    ram.GetByteByAddr(12);







    return 0;
}

