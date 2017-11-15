#include <decision_maker.h>





InstructionHandler::InstructionHandler(uint16_t instruction, CPU *cpu)
{
    this->instruction =instruction;
    this->cpu = cpu;
}

void InstructionHandler::HandleInstruction()
{
    Instruction* instr;
    Parser parser(this->instruction);

    parser.PrintInstruction();
    parser.CheckLastBit();
    parser.CountOperands();
    //cpu->GetValFromRegisterByNum(9);
    switch(parser.flagOnOperandsNumber)
    {
        case(parser.SINGLE_OP_INSTR):
        {
            parser.GetOpcodeInSingleOpCase();
            parser.GetModeInSingleCase();
            parser.GetArgs_1InSingleCase();
            SingleOpInstruction single_op_instruction(parser.opcode, parser.mode_1, parser.arg_1, cpu, parser.flagOn15Bit);
            single_op_instruction.ExecuteInstruction();
            //return single_op_instruction.getCPU();
            break;
        }

        case(parser.DOUBLE_OP_REG_INSTR):
        {
            parser.GetOpcodeInDoubleRegOpCase();
            parser.GetArg_1_InDoubleRegOpCase();
            parser.GetMode_2_InDoubleRegOpCase();
            parser.GetArg_2_InDoubleRegOpCase();
            DoubleOpRegInstruction double_op_reg_instruction(parser.opcode, parser.arg_1, parser.mode_2, parser.arg_2, cpu, parser.flagOn15Bit);
            instr = &double_op_reg_instruction;
            instr->ExecuteInstruction();
            break;
        }

        case(parser.DOUBLE_OP_INSTR):
        {
            parser.GetOpcodeInDoubleOpCase();
            parser.GetMode_1_InDoubleOpCase();
            parser.GetArg_1_InDoubleOpCase();
            parser.GetMode_2_InDoubleOpCase();
            parser.GetArg_2_InDoubleOpCase();
            DoubleOpInstruction double_op_instruction(parser.opcode, parser.mode_1, parser.arg_1, parser.mode_2, parser.arg_2, cpu, parser.flagOn15Bit);
            instr = &double_op_instruction;
            instr->ExecuteInstruction();
            break;
        }



        case(parser.CONDITIONAL_INSTR):
        {
            parser.GetOpcodeInBranchOpCase();
            parser.GetOffsetInBranchOpCase();
            ConditionalInstruction conditional_instruction(parser.opcode, parser.offset, cpu, parser.flagOn15Bit);
            instr = &conditional_instruction;
            std::cout << "break\n";
            instr->ExecuteInstruction();
            break;
        }
    }

    //return instr;


}

InstructionHandler::~InstructionHandler()
{

}


