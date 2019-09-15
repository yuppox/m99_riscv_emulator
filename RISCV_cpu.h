#ifndef RISCV_CPU_H
#define RISCV_CPU_H

#include <cstdint>
#include "bit_tools.h"

class RiscvCpu {
public:
    RiscvCpu(bool randomize=true);
    ~RiscvCpu() {};
    uint32_t reg[32];
    uint32_t pc;

    void set_register(uint32_t num, uint32_t value);

    uint32_t read_register(uint32_t num);

    int run_cpu(uint8_t *mem, uint32_t start_pc, bool verbose = true);

    void randomize_registers();

private:
    uint32_t load_cmd(uint8_t *mem, uint32_t pc);
    uint32_t get_code(uint32_t ir);

};

enum Registers {
    ZERO = 0,
    X0 = 0,
    X1 = 1,
    X2 = 2,
    X3 = 3,
    X4 = 4,
    X5 = 5,
    X6 = 6,
    X7 = 7,
    X8 = 8,
    X9 = 9,
    X10 = 10,
    X11 = 11,
    X12 = 12,
    X13 = 13,
    X14 = 14,
    X15 = 15,
    X16 = 16,
    RA = 1,
    SP = 2,
    GP = 3,
    TP = 4,
    T0 = 5,
    T1 = 6,
    T2 = 7,
    FP = 8,
    S0 = 8,
    S1 = 9,
    A0 = 10,
    A1 = 11,
    A2 = 12,
    A3 = 13,
    A4 = 14,
    A5 = 15,
    A6 = 16,
    A7 = 17,
    S2 = 18,
    S3 = 19,
    S4 = 20,
    S5 = 21,
    S6 = 22,
    S7 = 23,
    S8 = 24,
    S9 = 25,
    S10 = 26,
    S11 = 27,
    T3 = 28,
    T4 = 29,
    T5 = 30,
    T6 = 31
};

enum op_label {
    OPCODE_ARITHLOG = 0b0110011,
    OPCODE_ADDI = 0b0010011,
    OPCODE_B = 0b1100011,
    OPCODE_LD = 0b0000011,
    OPCODE_J = 0b1101111,
    OPCODE_S = 0b0100011,
    OPCODE_JALR = 0b1100111,
    OPCODE_LUI = 0b0110111,
};

enum op_funct {
    FUNC_NORM = 0b0000000,
    FUNC_ALT = 0b0100000,
    FUNC_SLLI = 0b000000,
    FUNC_SRLI = 0b000000,
    FUNC_SRAI = 0b010000,
};

enum op_funct3 {
    FUNC3_ADDSUB = 0b000,
    FUNC3_AND = 0b111,
    FUNC3_OR = 0b110,
    FUNC3_XOR = 0b100,
    FUNC3_SL = 0b001,
    FUNC3_SR = 0b0101,
    FUNC3_BEQ = 0b000,
    FUNC3_BGE = 0b101,
    FUNC3_BLTU = 0b110,
    FUNC3_BNE = 0b001,
    FUNC3_LS = 0b010,
    FUNC3_JALR = 0b000,
};

enum instruction {
    INST_ERROR,
    INST_ADD,
    INST_AND,
    INST_SUB,
    INST_OR,
    INST_XOR,
    INST_SLL,
    INST_SRL,
    INST_SRA,
    INST_ADDI,
    INST_ANDI,
    INST_ORI,
    INST_XORI,
    INST_SLLI,
    INST_BEQ,
    INST_BGE,
    INST_BLTU,
    INST_BNE,
    INST_JAL,
    INST_JALR,
    INST_LW,
    INST_SW,
    INST_LUI,
};


#endif // RISCV_CPU_H