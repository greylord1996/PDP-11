#include <iostream>
#include <parser.h>
#include <cstdint>
#include <bitset>


using namespace std;

int main()
{
    uint16_t instruction;
    std::cout << "Enter instruction " ;
    std::cin >> instruction;

    std::string binary_code = std::bitset<16>(instruction).to_string(); //to binary
    std::cout << "binary_code = " << binary_code << std::endl;

    Parser parser(instruction);


    //Instruction* instr;
    parser.MakeParse();
    //instr->ExecuteInstruction();
    //instr->who_am_i();
    //instr->who_am_i();

    return 0;
}

