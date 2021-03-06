#include "instruction_encdec.h"
#include "assembler.h"
#include "bit_tools.h"
#include <iostream>
#include <string>
#include <random>
#include <bitset>

using namespace RISCV_EMULATOR;
using namespace CPU_TEST;

namespace {
constexpr int TEST_NUM = 1000;

std::mt19937 rnd;
constexpr int kSeed = 155719;

void init_random() {
  rnd.seed(kSeed);
}


// Print binary bit by bit.
template<class T>
void print_binary(T value) {
  int bitwidth = sizeof(T) * 8;
  for (int i = 0; i < bitwidth; i++) {
    printf("%d", (value >> (bitwidth - i - 1)) & 1);
    if (i % 8 == 7) {
      printf(" ");
    }
  }
}

bool check_equal(const std::string &text, uint32_t value, uint32_t exp,
                 bool verbose = false) {
  bool error = value != exp;
  if (!verbose) {
    return error;
  }
  std::cout << text;
  printf(": %d (", value);
  print_binary(value);
  printf(")");
  if (!error) {
    printf(" - Pass\n");
  } else {
    printf(" - Error (expected: ");
    print_binary(exp);
    printf(")\n");
  }
  return error;
}

bool check_equal_quiet(const std::string &text, uint32_t cmd, uint32_t exp,
                       bool verbose = false) {
  bool error = check_equal(text, cmd, exp, false);
  if (error & verbose) {
    error = check_equal(text, cmd, exp, true);
  }
  return error;
}


bool test_r_type_decode(uint32_t instruction, uint8_t opcode, uint8_t funct3,
                        uint8_t funct7, uint8_t rd, uint8_t rs1, uint8_t rs2,
                        bool verbose = false) {
  bool error = false;
  RType cmd;
  cmd.SetValue(instruction);
  error |= check_equal("opcode", cmd.opcode, opcode, verbose);
  error |= check_equal("funct7", cmd.funct7, funct7, verbose);
  error |= check_equal("funct3", cmd.funct3, funct3, verbose);
  error |= check_equal("rd", cmd.rd, rd, verbose);
  error |= check_equal("rs1", cmd.rs1, rs1, verbose);
  error |= check_equal("rs2", cmd.rs2, rs2, verbose);
  return error;
}

// Only shows message when there's an error.
bool test_r_type_decode_quiet(uint32_t instruction, uint8_t opcode,
                              uint8_t funct3, uint8_t funct7, uint8_t rd,
                              uint8_t rs1, uint8_t rs2, bool verbose = false) {
  bool error = test_r_type_decode(instruction, opcode, funct3, funct7, rd, rs1,
                                  rs2, false);
  if (error && verbose) {
    // Show error message.
    error = test_r_type_decode(instruction, opcode, funct3, funct7, rd, rs1,
                               rs2, true);
  }
  return error;
}

bool test_i_type_decode(uint32_t instruction, uint8_t opcode, uint8_t funct3,
                        uint8_t rd, uint8_t rs1, int16_t imm12,
                        bool verbose = false) {
  bool error = false;
  IType cmd;
  cmd.SetValue(instruction);
  error |= check_equal("cmd", cmd.opcode, opcode, verbose);
  error |= check_equal("funct3", cmd.funct3, funct3, verbose);
  error |= check_equal("rd", cmd.rd, rd, verbose);
  error |= check_equal("rs1", cmd.rs1, rs1, verbose);
  error |= check_equal("imm12", SignExtend(cmd.imm12, 12), imm12, verbose);
  return error;
}

// Only shows message when there's an error.
bool test_i_type_decode_quiet(uint32_t instruction, uint8_t opcode,
                              uint8_t funct3, uint8_t rd, uint8_t rs1,
                              int16_t imm12, bool verbose = false) {
  bool error =
    test_i_type_decode(instruction, opcode, funct3, rd, rs1, imm12, false);
  if (error && verbose) {
    // Show error message.
    error =
      test_i_type_decode(instruction, opcode, funct3, rd, rs1, imm12, true);
  }
  return error;
}

bool test_b_type_decode(uint32_t instruction, uint8_t opcode, uint8_t funct3,
                        uint8_t rs1, uint8_t rs2, int16_t imm13,
                        bool verbose = false) {
  bool error = false;
  BType cmd;
  cmd.SetValue(instruction);
  error |= check_equal("cmd", cmd.opcode, opcode, verbose);
  error |= check_equal("funct3", cmd.funct3, funct3);
  error |= check_equal("rs1", cmd.rs1, rs1, verbose);
  error |= check_equal("rs2", cmd.rs2, rs2, verbose);
  error |= check_equal("imm13", SignExtend(cmd.imm13, 13), imm13 & (~0b01),
                       verbose);
  return error;
}

// Only shows message when there's an error.
bool test_b_type_decode_quiet(uint32_t instruction, uint8_t opcode,
                              uint8_t funct3, uint8_t rs1, uint8_t rs2,
                              int16_t imm13, bool verbose = false) {
  bool error =
    test_b_type_decode(instruction, opcode, funct3, rs1, rs2, imm13, false);
  if (error && verbose) {
    // Show error message.
    error =
      test_b_type_decode(instruction, opcode, funct3, rs1, rs2, imm13, true);
  }
  return error;
}

bool test_j_type_decode(uint32_t instruction, uint8_t opcode, uint8_t rd,
                        int32_t imm21, bool verbose = false) {
  bool error = false;
  JType cmd;
  cmd.SetValue(instruction);
  error |= check_equal("cmd", cmd.opcode, opcode, verbose);
  error |= check_equal("rd", cmd.rd, rd, verbose);
  error |= check_equal("imm21", SignExtend(cmd.imm21, 21), imm21 & (~1),
                       verbose);
  return error;
}

// Only shows message when there's an error.
bool test_j_type_decode_quiet(uint32_t instruction, uint8_t opcode, uint8_t rd,
                              int32_t imm21, bool verbose = false) {
  bool error = test_j_type_decode(instruction, opcode, rd, imm21, false);
  if (error && verbose) {
    // Show error message.
    error = test_j_type_decode(instruction, opcode, rd, imm21, true);
  }
  return error;
}

bool test_s_type_decode(uint32_t instruction, uint8_t opcode, uint8_t funct3,
                        uint8_t rs1, uint8_t rs2, int16_t imm12,
                        bool verbose = false) {
  bool error = false;
  SType cmd;
  cmd.SetValue(instruction);
  error |= check_equal("cmd", cmd.opcode, opcode, verbose);
  error |= check_equal("funct3", cmd.funct3, funct3);
  error |= check_equal("rs1", cmd.rs1, rs1, verbose);
  error |= check_equal("rs2", cmd.rs2, rs2, verbose);
  error |= check_equal("imm12", SignExtend(cmd.imm12, 12), imm12, verbose);
  return error;
}

// Only shows message when there's an error.
bool test_s_type_decode_quiet(uint32_t instruction, uint8_t opcode,
                              uint8_t funct3, uint8_t rs1, uint8_t rs2,
                              int16_t imm12, bool verbose = false) {
  bool error =
    test_s_type_decode(instruction, opcode, funct3, rs1, rs2, imm12, false);
  if (error && verbose) {
    // Show error message.
    error =
      test_s_type_decode(instruction, opcode, funct3, rs1, rs2, imm12, true);
  }
  return error;
}

// Create R TYPE instruction with necessary parameters.
uint32_t gen_r_type(uint32_t base, uint8_t rd, uint8_t rs1, uint8_t rs2) {
  return base | ((rd & 0x01F) << 7) | ((rs1 & 0x01F) << 15) |
         ((rs2 & 0x01F) << 20);
}

// Create I TYPE instruction with necessary parameters.
uint32_t gen_i_type(uint32_t base, uint8_t rd, uint8_t rs1, int16_t imm12) {
  return base | ((imm12 & 0xFFF) << 20) | ((rs1 & 0x1F) << 15) |
         ((rd & 0x1F) << 7);
}

// Create B TYPE instruction with necessary parameters.
uint32_t gen_b_type(uint32_t base, uint8_t rs1, uint8_t rs2, int16_t imm13) {
  uint32_t instruction = base | ((rs2 & 0x1F) << 20) | ((rs1 & 0x1F) << 15);
  instruction |= ((imm13 >> 12) & 0b01) << 31;
  instruction |= ((imm13 >> 5) & 0b0111111) << 25;
  instruction |= ((imm13 >> 1) & 0b01111) << 8;
  instruction |= ((imm13 >> 11) & 0b01) << 7;
  return instruction;
}

// Create J TYPE instruction with necessary parameters.
uint32_t gen_j_type(uint32_t base, uint8_t rd, int32_t imm21) {
  uint32_t instruction = base | ((rd & 0x1F) << 7);
  instruction |= ((imm21 >> 20) & 0b01) << 31;
  instruction |= ((imm21 >> 1) & 0b01111111111) << 21;
  instruction |= ((imm21 >> 11) & 0b01) << 20;
  instruction |= ((imm21 >> 12) & 0b011111111) << 12;
  return instruction;
}

// Create S TYPE instruction with necessary parameters.
uint32_t gen_s_type(uint32_t base, uint8_t rs1, uint8_t rs2, int16_t imm12) {
  uint32_t instruction = base | ((rs1 & 0x01F) << 15) | ((rs2 & 0x01F) << 20);
  instruction |=
    (((imm12 >> 5) & 0b01111111) << 25) | ((imm12 & 0b011111) << 7);
  return instruction;
}

/// Support function for showing error message at the end of a test sequence.
void print_error_result(std::string &cmdname, int num_test, bool error,
                        bool verbose) {
  if (verbose) {
    printf("Total %d %s random encode & decode test finished. ", num_test,
           cmdname.c_str());
    if (error) {
      printf("%s test failed\n", cmdname.c_str());
    } else {
      printf("%s test passed\n", cmdname.c_str());
    }
  }
}

bool test_amo_type(bool verbose = false) {
  enum TEST_LIST {
    TEST_AMOADDD, TEST_AMOADDW, TEST_AMOANDD, TEST_AMOANDW,
    TEST_AMOMAXD, TEST_AMOMAXW, TEST_AMOMAXUD, TEST_AMOMAXUW,
    TEST_AMOMIND, TEST_AMOMINW, TEST_AMOMINUD, TEST_AMOMINUW,
    TEST_AMOORD, TEST_AMOORW, TEST_AMOSWAPW, TEST_AMOSWAPD,
    TEST_AMOXORD, TEST_AMOXORW,
  };
  bool total_error = false;

  TEST_LIST test_set[] = {TEST_AMOADDD, TEST_AMOADDW, TEST_AMOANDD, TEST_AMOANDW,
                          TEST_AMOMAXD, TEST_AMOMAXW, TEST_AMOMAXUD, TEST_AMOMAXUW,
                          TEST_AMOMIND, TEST_AMOMINW, TEST_AMOMIND, TEST_AMOMINUW,
                          TEST_AMOORD, TEST_AMOORW, TEST_AMOSWAPW, TEST_AMOSWAPD,
                          TEST_AMOXORD, TEST_AMOXORW,
                          };
  for (TEST_LIST testcase : test_set) {
    bool error = false;
    uint32_t base;
    std::string cmdname;
    switch (testcase) {
      case TEST_AMOADDD:
        base = 0b00000000000000000011000000101111;
        cmdname = "AMOADD.D";
        break;
      case TEST_AMOADDW:
        base = 0b00000000000000000010000000101111;
        cmdname = "AMOADD.W";
        break;
      case TEST_AMOANDD:
        base = 0b01100000000000000011000000101111;
        cmdname = "AMOAND.D";
        break;
      case TEST_AMOANDW:
        base = 0b01100000000000000010000000101111;
        cmdname = "AMOAND.W";
        break;
      case TEST_AMOMAXD:
        base = 0b10100000000000000011000000101111;
        cmdname = "AMOMAX.D";
        break;
      case TEST_AMOMAXW:
        base = 0b10100000000000000010000000101111;
        cmdname = "AMOMAX.W";
        break;
      case TEST_AMOMAXUD:
        base = 0b11100000000000000011000000101111;
        cmdname = "AMOMAXU.D";
        break;
      case TEST_AMOMAXUW:
        base = 0b11100000000000000010000000101111;
        cmdname = "AMOMAXU.W";
        break;
      case TEST_AMOMIND:
        base = 0b10000000000000000011000000101111;
        cmdname = "AMOMIN.D";
        break;
      case TEST_AMOMINW:
        base = 0b10000000000000000010000000101111;
        cmdname = "AMOMIN.W";
        break;
      case TEST_AMOMINUD:
        base = 0b11000000000000000011000000101111;
        cmdname = "AMOMINU.D";
        break;
      case TEST_AMOMINUW:
        base = 0b11000000000000000010000000101111;
        cmdname = "AMOMINU.W";
        break;
      case TEST_AMOORD:
        base = 0b01000000000000000011000000101111;
        cmdname = "AMOOR.D";
        break;
      case TEST_AMOORW:
        base = 0b01000000000000000010000000101111;
        cmdname = "AMOOR.W";
        break;
      case TEST_AMOSWAPD:
        base = 0b00001000000000000011000000101111;
        cmdname = "AMOSWAP.D";
        break;
      case TEST_AMOSWAPW:
        base = 0b00001000000000000010000000101111;
        cmdname = "AMOSWAP.W";
        break;
      case TEST_AMOXORD:
        base = 0b00100000000000000011000000101111;
        cmdname = "AMOXOR.D";
        break;
      case TEST_AMOXORW:
        base = 0b00100000000000000010000000101111;
        cmdname = "AMOXOR.W";
        break;

      default:
        printf("Test case is not defined yet\n");
        return true;
        break;
    }

    for (int i = 0; i < TEST_NUM && !error; i++) {
      uint32_t cmd = 0;
      uint32_t rd = rnd() % 32;
      uint32_t rs1 = rnd() % 32;
      uint32_t rs2 = rnd() % 32;
      uint32_t aq = rnd() & 1;
      uint32_t rl = rnd() & 1;
      switch (testcase) {
        case TEST_AMOADDD:
          cmd = AsmAmoAddd(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOADDW:
          cmd = AsmAmoAddw(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOANDD:
          cmd = AsmAmoAndd(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOANDW:
          cmd = AsmAmoAndw(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOMAXD:
          cmd = AsmAmoMaxd(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOMAXW:
          cmd = AsmAmoMaxw(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOMAXUD:
          cmd = AsmAmoMaxud(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOMAXUW:
          cmd = AsmAmoMaxuw(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOMIND:
          cmd = AsmAmoMind(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOMINW:
          cmd = AsmAmoMinw(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOMINUD:
          cmd = AsmAmoMinud(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOMINUW:
          cmd = AsmAmoMinuw(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOORD:
          cmd = AsmAmoOrd(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOORW:
          cmd = AsmAmoOrw(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOSWAPD:
          cmd = AsmAmoSwapd(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOSWAPW:
          cmd = AsmAmoSwapw(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOXORD:
          cmd = AsmAmoXord(rd, rs1, rs2, aq, rl);
          break;
        case TEST_AMOXORW:
          cmd = AsmAmoXorw(rd, rs1, rs2, aq, rl);
          break;

        default:
          break;
      }
      uint32_t base_with_aq_rl = base | ((aq & 0b1) << 26) | ((rl & 0b1) << 25);
      uint8_t opcode = base_with_aq_rl & 0b01111111;
      uint8_t funct3 = (base_with_aq_rl >> 12) & 0b111;
      uint8_t funct7 = (base_with_aq_rl >> 25) & 0b1111111;
      uint32_t exp = gen_r_type(base_with_aq_rl, rd, rs1, rs2);
      std::string test_string = cmdname + " " + std::to_string(rd) + ", " +
                                std::to_string(rs1) + ", " +
                                std::to_string(rs2) + "(aq = " + std::to_string(aq)
                                + ", rl = " + std::to_string(rl) + ")";
      error |= check_equal_quiet(test_string, cmd, exp, verbose);
      error |= test_r_type_decode_quiet(exp, opcode, funct3, funct7, rd, rs1,
                                        rs2, verbose);
    }
    print_error_result(cmdname, TEST_NUM, error, verbose);
    total_error |= error;
  }
  return total_error;
}

bool test_r_type(bool verbose = false) {
  enum TEST_LIST {
    TEST_ADD,
    TEST_SUB,
    TEST_AND,
    TEST_OR,
    TEST_XOR,
    TEST_SLL,
    TEST_SRL,
    TEST_SRA,
    TEST_SLT,
    TEST_SLTU,
    TEST_MRET,
    TEST_SLLW,
    TEST_SRAW,
    TEST_SRLW,
    TEST_SUBW,
    TEST_ADDW,
  };
  bool total_error = false;

  TEST_LIST test_set[] = {TEST_ADD, TEST_SUB, TEST_AND, TEST_OR, TEST_XOR,
                          TEST_SLL, TEST_SRL, TEST_SRA, TEST_SLT,
                          TEST_SLTU, TEST_MRET, TEST_SLLW, TEST_SRAW, TEST_SRLW,
                          TEST_SUBW, TEST_ADDW};
  for (TEST_LIST testcase : test_set) {
    bool error = false;
    uint32_t base;
    std::string cmdname;
    switch (testcase) {
      case TEST_ADD:
        base = 0b00000000000000000000000000110011;
        cmdname = "ADD";
        break;
      case TEST_ADDW:
        base = 0b00000000000000000000000000111011;
        cmdname = "ADDW";
        break;
      case TEST_SUB:
        base = 0b01000000000000000000000000110011;
        cmdname = "SUB";
        break;
      case TEST_SUBW:
        base = 0b01000000000000000000000000111011;
        cmdname = "SUBW";
        break;
      case TEST_AND:
        base = 0b00000000000000000111000000110011;
        cmdname = "AND";
        break;
      case TEST_OR:
        base = 0b00000000000000000110000000110011;
        cmdname = "OR";
        break;
      case TEST_XOR:
        base = 0b00000000000000000100000000110011;
        cmdname = "XOR";
        break;
      case TEST_SLL:
        base = 0b00000000000000000001000000110011;
        cmdname = "SLL";
        break;
      case TEST_SLLW:
        base = 0b00000000000000000001000000111011;
        cmdname = "SLLW";
        break;
      case TEST_SRL:
        base = 0b00000000000000000101000000110011;
        cmdname = "SRL";
        break;
      case TEST_SRLW:
        base = 0b00000000000000000101000000111011;
        cmdname = "SRL";
        break;
      case TEST_SRA:
        base = 0b01000000000000000101000000110011;
        cmdname = "SRA";
        break;
      case TEST_SRAW:
        base = 0b01000000000000000101000000111011;
        cmdname = "SRAW";
        break;
      case TEST_SLT:
        base = 0b00000000000000000010000000110011;
        cmdname = "SLT";
        break;
      case TEST_SLTU:
        base = 0b00000000000000000011000000110011;
        cmdname = "SLTU";
        break;
      case TEST_MRET:
        base = 0b00110000001000000000000001110011;
        cmdname = "MRET";
        break;
      default:
        printf("Test case is not defined yet\n");
        return true;
        break;
    }
    uint8_t opcode = base & 0b01111111;
    uint8_t funct3 = (base >> 12) & 0b111;
    uint8_t funct7 = (base >> 25) & 0b1111111;

    for (int i = 0; i < TEST_NUM && !error; i++) {
      uint32_t cmd = 0;
      uint8_t rd = rnd() % 32;
      uint8_t rs1 = rnd() % 32;
      uint8_t rs2 = rnd() % 32;
      switch (testcase) {
        case TEST_ADD:
          cmd = AsmAdd(rd, rs1, rs2);
          break;
        case TEST_ADDW:
          cmd = AsmAddw(rd, rs1, rs2);
          break;
        case TEST_SUB:
          cmd = AsmSub(rd, rs1, rs2);
          break;
        case TEST_SUBW:
          cmd = AsmSubw(rd, rs1, rs2);
          break;
        case TEST_AND:
          cmd = AsmAnd(rd, rs1, rs2);
          break;
        case TEST_OR:
          cmd = AsmOr(rd, rs1, rs2);
          break;
        case TEST_XOR:
          cmd = AsmXor(rd, rs1, rs2);
          break;
        case TEST_SLL:
          cmd = AsmSll(rd, rs1, rs2);
          break;
        case TEST_SLLW:
          cmd = AsmSllw(rd, rs1, rs2);
          break;
        case TEST_SRL:
          cmd = AsmSrl(rd, rs1, rs2);
          break;
        case TEST_SRLW:
          cmd = AsmSrlw(rd, rs1, rs2);
          break;
        case TEST_SRA:
          cmd = AsmSra(rd, rs1, rs2);
          break;
        case TEST_SRAW:
          cmd = AsmSraw(rd, rs1, rs2);
          break;
        case TEST_SLT:
          cmd = AsmSlt(rd, rs1, rs2);
          break;
        case TEST_SLTU:
          cmd = AsmSltu(rd, rs1, rs2);
          break;
        case TEST_MRET:
          cmd = AsmMret();
          rd = rs1 = 0;
          rs2 = 0b00010;
          break;
        default:
          break;
      }
      uint32_t exp = gen_r_type(base, rd, rs1, rs2);
      std::string test_string = cmdname + " " + std::to_string(rd) + ", " +
                                std::to_string(rs1) + ", " +
                                std::to_string(rs2);
      error |= check_equal_quiet(test_string, cmd, exp, verbose);
      error |= test_r_type_decode_quiet(exp, opcode, funct3, funct7, rd, rs1,
                                        rs2, verbose);
    }
    print_error_result(cmdname, TEST_NUM, error, verbose);
    total_error |= error;
  }
  return total_error;
}

bool test_i_type(bool verbose = false) {
  enum TEST_LIST {
    TEST_ADDI,
    TEST_SLLI,
    TEST_SRLI,
    TEST_SRAI,
    TEST_LB,
    TEST_LBU,
    TEST_LH,
    TEST_LHU,
    TEST_LW,
    TEST_JALR,
    TEST_ANDI,
    TEST_ORI,
    TEST_XORI,
    TEST_SLTI,
    TEST_SLTIU,
    TEST_EBREAK,
    TEST_ECALL,
    TEST_CSRRC,
    TEST_CSRRCI,
    TEST_CSRRS,
    TEST_CSRRSI,
    TEST_CSRRW,
    TEST_CSRRWI,
    TEST_FENCE,
    TEST_FENCEI,
    TEST_ADDIW,
    TEST_LD,
    TEST_LWU,
    TEST_SLLIW,
    TEST_SRAIW,
    TEST_SRLIW
  };
  bool total_error = false;
  TEST_LIST test_set[] = {TEST_ADDI, TEST_SLLI, TEST_SRLI, TEST_SRAI, TEST_LB,
                          TEST_LBU, TEST_LH, TEST_LHU,
                          TEST_LW, TEST_JALR, TEST_ANDI, TEST_ORI, TEST_XORI,
                          TEST_SLTI, TEST_SLTIU,
                          TEST_EBREAK, TEST_ECALL,
                          TEST_CSRRC, TEST_CSRRCI, TEST_CSRRS, TEST_CSRRSI,
                          TEST_CSRRW, TEST_CSRRWI,
                          TEST_FENCE, TEST_FENCEI,
                          TEST_ADDIW, TEST_LD, TEST_LWU, TEST_SLLIW, TEST_SRAIW,
                          TEST_SRLIW
  };
  for (TEST_LIST test_case : test_set) {
    bool error = false;
    uint32_t base;
    std::string cmdname;
    switch (test_case) {
      case TEST_ADDI:
        base = 0b00000000000000000000000000010011;
        cmdname = "ADDI";
        break;
      case TEST_ADDIW:
        base = 0b00000000000000000000000000011011;
        cmdname = "ADDIW";
        break;
      case TEST_SLLI:
        base = 0b00000000000000000001000000010011;
        cmdname = "SLLI";
        break;
      case TEST_SLLIW:
        base = 0b00000000000000000001000000011011;
        cmdname = "SLLIW";
        break;
      case TEST_SRLI:
        base = 0b00000000000000000101000000010011;
        cmdname = "SRLI";
        break;
      case TEST_SRLIW:
        base = 0b00000000000000000101000000011011;
        cmdname = "SRLIW";
        break;
      case TEST_SRAI:
        base = 0b01000000000000000101000000010011;
        cmdname = "SRAI";
        break;
      case TEST_SRAIW:
        base = 0b01000000000000000101000000011011;
        cmdname = "SRAIW";
        break;
      case TEST_ANDI:
        base = 0b00000000000000000111000000010011;
        cmdname = "ANDI";
        break;
      case TEST_ORI:
        base = 0b00000000000000000110000000010011;
        cmdname = "ORI";
        break;
      case TEST_XORI:
        base = 0b00000000000000000100000000010011;
        cmdname = "XORI";
        break;
      case TEST_SLTI:
        base = 0b00000000000000000010000000010011;
        cmdname = "SLTI";
        break;
      case TEST_SLTIU:
        base = 0b00000000000000000011000000010011;
        cmdname = "SLTIU";
        break;
      case TEST_LB:
        base = 0b00000000000000000000000000000011;
        cmdname = "LB";
        break;
      case TEST_LBU:
        base = 0b00000000000000000100000000000011;
        cmdname = "LBU";
        break;
      case TEST_LH:
        base = 0b00000000000000000001000000000011;
        cmdname = "LH";
        break;
      case TEST_LHU:
        base = 0b00000000000000000101000000000011;
        cmdname = "LHU";
        break;
      case TEST_LW:
        base = 0b00000000000000000010000000000011;
        cmdname = "LW";
        break;
      case TEST_LD:
        base = 0b00000000000000000011000000000011;
        cmdname = "LD";
        break;
      case TEST_LWU:
        base = 0b00000000000000000110000000000011;
        cmdname = "LD";
        break;
      case TEST_JALR:
        base = 0b00000000000000000000000001100111;
        cmdname = "JALR";
        break;
      case TEST_EBREAK:
        base = 0b00000000000100000000000001110011;
        cmdname = "EBREAK";
        break;
      case TEST_ECALL:
        cmdname = "ECALL";
        base = 0b00000000000000000000000001110011;
        break;
      case TEST_CSRRC:
        cmdname = "CSRRC";
        base = 0b00000000000000000011000001110011;
        break;
      case TEST_CSRRCI:
        cmdname = "CSRRCI";
        base = 0b00000000000000000111000001110011;
        break;
      case TEST_CSRRS:
        cmdname = "CSRRS";
        base = 0b00000000000000000010000001110011;
        break;
      case TEST_CSRRSI:
        cmdname = "CSRRSI";
        base = 0b00000000000000000110000001110011;
        break;
      case TEST_CSRRW:
        cmdname = "CSRRW";
        base = 0b00000000000000000001000001110011;
        break;
      case TEST_CSRRWI:
        cmdname = "CSRRWI";
        base = 0b00000000000000000101000001110011;
        break;
      case TEST_FENCE:
        cmdname = "FENCE";
        base = 0b00000000000000000000000000001111;
        break;
      case TEST_FENCEI:
        cmdname = "FENCE.I";
        base = 0b00000000000000000001000000001111;
        break;
      default:
        printf("Test case %d is not defined yet\n", test_case);
        return true;
        break;
    }
    uint8_t opcode = base & 0b01111111;
    uint8_t funct3 = (base >> 12) & 0b111;

    for (int i = 0; i < TEST_NUM && !error; i++) {
      uint32_t cmd = 0;
      uint8_t rd = rnd() % 32;
      uint8_t rs1 = rnd() % 32;
      int16_t imm12 = (rnd() % (1 << 12)) - (1 << 11);
      switch (test_case) {
        case TEST_ADDI:
          cmd = AsmAddi(rd, rs1, imm12);
          break;
        case TEST_ADDIW:
          cmd = AsmAddiw(rd, rs1, imm12);
          break;
        case TEST_ANDI:
          cmd = AsmAndi(rd, rs1, imm12);
          break;
        case TEST_ORI:
          cmd = AsmOri(rd, rs1, imm12);
          break;
        case TEST_XORI:
          cmd = AsmXori(rd, rs1, imm12);
          break;
        case TEST_SLLI:
          cmd = AsmSlli(rd, rs1, imm12);
          // SLLI immediate is 6 bit.
          imm12 &= 0b0111111;
          break;
        case TEST_SLLIW:
          cmd = AsmSlliw(rd, rs1, imm12);
          // SLLI immediate is 6 bit.
          imm12 &= 0b0111111;
          break;
        case TEST_SRLI:
          cmd = AsmSrli(rd, rs1, imm12);
          // SRLI immediate is 6 bit.
          imm12 &= 0b0111111;
          break;
        case TEST_SRLIW:
          cmd = AsmSrliw(rd, rs1, imm12);
          // SRLI immediate is 6 bit.
          imm12 &= 0b0111111;
          break;
        case TEST_SRAI:
          cmd = AsmSrai(rd, rs1, imm12);
          // SRAI immediate is 6 bit.
          imm12 &= 0b0111111;
          break;
        case TEST_SRAIW:
          cmd = AsmSraiw(rd, rs1, imm12);
          // SRAI immediate is 6 bit.
          imm12 &= 0b0111111;
          break;
        case TEST_SLTI:
          cmd = AsmSlti(rd, rs1, imm12);
          break;
        case TEST_SLTIU:
          cmd = AsmSltiu(rd, rs1, imm12);
          break;
        case TEST_LB:
          cmd = AsmLb(rd, rs1, imm12);
          break;
        case TEST_LBU:
          cmd = AsmLbu(rd, rs1, imm12);
          break;
        case TEST_LH:
          cmd = AsmLh(rd, rs1, imm12);
          break;
        case TEST_LHU:
          cmd = AsmLhu(rd, rs1, imm12);
          break;
        case TEST_LW:
          cmd = AsmLw(rd, rs1, imm12);
          break;
        case TEST_LD:
          cmd = AsmLd(rd, rs1, imm12);
          break;
        case TEST_LWU:
          cmd = AsmLwu(rd, rs1, imm12);
          break;
        case TEST_JALR:
          cmd = AsmJalr(rd, rs1, imm12);
          break;
        case TEST_EBREAK:
          cmd = AsmEbreak();
          rd = 0;
          rs1 = 0;
          imm12 = 1;
          break;
        case TEST_ECALL:
          cmd = AsmEcall();
          rd = 0;
          rs1 = 0;
          imm12 = 0;
          break;
        case TEST_CSRRC:
          cmd = AsmCsrrc(rd, rs1, imm12);
          break;
        case TEST_CSRRCI:
          cmd = AsmCsrrci(rd, rs1, imm12);
          break;
        case TEST_CSRRS:
          cmd = AsmCsrrs(rd, rs1, imm12);
          break;
        case TEST_CSRRSI:
          cmd = AsmCsrrsi(rd, rs1, imm12);
          break;
        case TEST_CSRRW:
          cmd = AsmCsrrw(rd, rs1, imm12);
          break;
        case TEST_CSRRWI:
          cmd = AsmCsrrwi(rd, rs1, imm12);
          break;
        case TEST_FENCE: {
          uint32_t pred = (imm12 >> 4) & 0x0F;
          uint32_t succ = imm12 & 0x0F;
          imm12 &= 0x0FF;
          cmd = AsmFence(pred, succ);
          rd = rs1 = 0;
        }
          break;
        case TEST_FENCEI:
          rd = rs1 = 0;
          imm12 = 0;
          cmd = AsmFencei();
          break;
        default:
          break;
      }
      uint32_t exp = gen_i_type(base, rd, rs1, imm12);
      std::string test_string = cmdname + " " + std::to_string(rd) + ", " +
                                std::to_string(rs1) + ", " +
                                std::to_string(imm12);
      error |= check_equal_quiet(test_string, cmd, exp, verbose);
      error |= test_i_type_decode_quiet(exp, opcode, funct3, rd, rs1, imm12,
                                        verbose);
    }
    print_error_result(cmdname, TEST_NUM, error, verbose);
    total_error |= error;
  }
  return total_error;
}

bool test_b_type(bool verbose = false) {
  enum TEST_LIST {
    TEST_BEQ, TEST_BGE, TEST_BGEU, TEST_BLT, TEST_BLTU, TEST_BNE
  };
  bool total_error = false;

  for (TEST_LIST testcase : {TEST_BEQ, TEST_BGE, TEST_BGEU, TEST_BLT, TEST_BLTU,
                             TEST_BNE}) {
    bool error = false;
    uint32_t base;
    std::string cmdname;
    switch (testcase) {
      case TEST_BEQ:
        base = 0b00000000000000000000000001100011;
        cmdname = "BEQ";
        break;
      case TEST_BGE:
        base = 0b00000000000000000101000001100011;
        cmdname = "BGE";
        break;
      case TEST_BGEU:
        base = 0b00000000000000000111000001100011;
        cmdname = "BGEU";
        break;
      case TEST_BLT:
        base = 0b00000000000000000100000001100011;
        cmdname = "BLT";
        break;
      case TEST_BLTU:
        base = 0b00000000000000000110000001100011;
        cmdname = "BLTU";
        break;
      case TEST_BNE:
        base = 0b00000000000000000001000001100011;
        cmdname = "BNE";
        break;
      default:
        printf("Test case #%d is not defined yet\n", testcase);
        return true;
        break;
    }
    uint8_t opcode = base & 0b01111111;
    uint8_t funct3 = (base >> 12) & 0b111;

    for (int i = 0; i < TEST_NUM && !error; i++) {
      uint32_t cmd = 0;
      uint8_t rs1 = rnd() % 32;
      uint8_t rs2 = rnd() % 32;
      int16_t imm13 = (rnd() % (1 << 13)) - (1 << 12);
      switch (testcase) {
        case TEST_BEQ:
          cmd = AsmBeq(rs1, rs2, imm13);
          break;
        case TEST_BGE:
          cmd = AsmBge(rs1, rs2, imm13);
          break;
        case TEST_BGEU:
          cmd = AsmBgeu(rs1, rs2, imm13);
          break;
        case TEST_BLT:
          cmd = AsmBlt(rs1, rs2, imm13);
          break;
        case TEST_BLTU:
          cmd = AsmBltu(rs1, rs2, imm13);
          break;
        case TEST_BNE:
          cmd = AsmBne(rs1, rs2, imm13);
          break;
        default:
          break;
      }
      uint32_t exp = gen_b_type(base, rs1, rs2, imm13);
      std::string test_string = cmdname + " " + std::to_string(rs1) + ", " +
                                std::to_string(rs2) + ", " +
                                std::to_string(imm13);
      error |= check_equal_quiet(test_string, cmd, exp, verbose);
      error |= test_b_type_decode_quiet(exp, opcode, funct3, rs1, rs2, imm13,
                                        verbose);
    }
    print_error_result(cmdname, TEST_NUM, error, verbose);
    total_error |= error;
  }
  return total_error;
}

bool test_j_type(bool verbose = false) {
  enum TEST_LIST {
    TEST_JAL
  };
  bool total_error = false;

  for (TEST_LIST testcase : {TEST_JAL}) {
    bool error = false;
    uint32_t base;
    std::string cmdname;
    switch (testcase) {
      case TEST_JAL:
        base = 0b00000000000000000000000001101111;
        cmdname = "JAL";
        break;
      default:
        printf("Test case is not defined yet\n");
        return true;
        break;
    }
    uint8_t opcode = base & 0b01111111;

    for (int i = 0; i < TEST_NUM && !error; i++) {
      uint32_t cmd = 0;
      uint8_t rd = rnd() % 32;
      int32_t imm21 = (rnd() % (1 << 21)) - (1 << 20);
      switch (testcase) {
        case TEST_JAL:
          cmd = AsmJal(rd, imm21);
          break;
        default:
          break;
      }
      uint32_t exp = gen_j_type(base, rd, imm21);
      std::string test_string =
        cmdname + " " + std::to_string(rd) + ", " + ", " +
        std::to_string(imm21);
      error |= check_equal_quiet(test_string, cmd, exp, verbose);
      error |= test_j_type_decode_quiet(exp, opcode, rd, imm21, verbose);
    }
    print_error_result(cmdname, TEST_NUM, error, verbose);
    total_error |= error;
  }
  return total_error;
}

bool test_s_type(bool verbose = false) {
  enum TEST_LIST {
    TEST_SW, TEST_SH, TEST_SB, TEST_SD
  };
  bool total_error = false;

  for (TEST_LIST testcase : {TEST_SW, TEST_SH, TEST_SB, TEST_SD}) {
    bool error = false;
    uint32_t base;
    std::string cmdname;
    switch (testcase) {
      case TEST_SW:
        base = 0b00000000000000000010000000100011;
        cmdname = "SW";
        break;
      case TEST_SH:
        base = 0b00000000000000000001000000100011;
        cmdname = "SH";
        break;
      case TEST_SB:
        base = 0b00000000000000000000000000100011;
        cmdname = "SB";
        break;
      case TEST_SD:
        base = 0b00000000000000000011000000100011;
        cmdname = "SD";
        break;
      default:
        printf("Test case is not defined yet\n");
        return true;
        break;
    }
    uint8_t opcode = base & 0b01111111;
    uint8_t funct3 = (base >> 12) & 0b111;

    for (int i = 0; i < TEST_NUM && !error; i++) {
      uint32_t cmd = 0;
      uint8_t rs1 = rnd() % 32;
      uint8_t rs2 = rnd() % 32;
      int32_t imm12 = (rnd() % (1 << 12)) - (1 << 11);
      switch (testcase) {
        case TEST_SW:
          cmd = AsmSw(rs1, rs2, imm12);
          break;
        case TEST_SH:
          cmd = AsmSh(rs1, rs2, imm12);
          break;
        case TEST_SB:
          cmd = AsmSb(rs1, rs2, imm12);
          break;
        case TEST_SD:
          cmd = AsmSd(rs1, rs2, imm12);
          break;
        default:
          break;
      }
      uint32_t exp = gen_s_type(base, rs1, rs2, imm12);
      std::string test_string = cmdname + " " + std::to_string(rs1) + ", " +
                                std::to_string(rs2) + ", " + ", " +
                                std::to_string(imm12);
      error |= check_equal_quiet(test_string, cmd, exp, verbose);
      error |= test_s_type_decode_quiet(exp, opcode, funct3, rs1, rs2, imm12,
                                        verbose);
    }
    print_error_result(cmdname, TEST_NUM, error, verbose);
    total_error |= error;
  }
  return total_error;
}


bool test_u_type_decode(uint32_t instruction, uint8_t opcode,
                        uint8_t rd, int32_t imm20,
                        bool verbose = false) {
  bool error = false;
  UType cmd;
  cmd.SetValue(instruction);
  error |= check_equal("cmd", cmd.opcode, opcode, verbose);
  error |= check_equal("rd", cmd.rd, rd, verbose);
  error |= check_equal("imm20", SignExtend(cmd.imm20, 20), imm20, verbose);
  return error;
}

// Only shows message when there's an error.
bool test_u_type_decode_quiet(uint32_t instruction, uint8_t opcode,
                              uint8_t rd,
                              int32_t imm24, bool verbose = false) {
  bool error =
    test_u_type_decode(instruction, opcode, rd, imm24, false);
  if (error && verbose) {
    // Show error message.
    error =
      test_u_type_decode(instruction, opcode, rd, imm24, true);
  }
  return error;
}

// Create U TYPE instruction with necessary parameters.
uint32_t gen_u_type(uint32_t base, uint8_t rd, int32_t imm20) {
  uint32_t instruction =
    base | ((rd & 0x01F) << 7) | ((imm20 & 0x0FFFFF) << 12);
  return instruction;
}

bool test_u_type(bool verbose = false) {
  enum TEST_LIST {
    TEST_LUI, TEST_AUIPC
  };
  bool total_error = false;

  for (TEST_LIST testcase : {TEST_LUI, TEST_AUIPC}) {
    bool error = false;
    uint32_t base;
    std::string cmdname;
    switch (testcase) {
      case TEST_LUI:
        base = 0b00000000000000000000000000110111;
        cmdname = "LUI";
        break;
      case TEST_AUIPC:
        base = 0b00000000000000000000000000010111;
        cmdname = "AUIPC";
        break;
      default:
        printf("Test case is not defined yet\n");
        return true;
        break;
    }
    uint8_t opcode = base & 0b01111111;

    for (int i = 0; i < TEST_NUM && !error; i++) {
      uint32_t cmd = 0;
      uint8_t rd = rnd() % 32;
      int32_t imm20 = (rnd() % (1 << 20)) - (1 << 19);
      switch (testcase) {
        case TEST_LUI:
          cmd = AsmLui(rd, imm20);
          break;
        case TEST_AUIPC:
          cmd = AsmAuipc(rd, imm20);
        default:
          break;
      }
      uint32_t exp = gen_u_type(base, rd, imm20);
      std::string test_string = cmdname + " " + std::to_string(rd) + ", "
                                + std::to_string(imm20);
      error |= check_equal_quiet(test_string, cmd, exp, verbose);
      error |= test_u_type_decode_quiet(exp, opcode, rd, imm20,
                                        verbose);
    }
    print_error_result(cmdname, TEST_NUM, error, verbose);
    total_error |= error;
  }
  return total_error;
}

bool test_mult(bool verbose = false) {
  enum TEST_LIST {
    TEST_MUL,
    TEST_MULH,
    TEST_MULHSU,
    TEST_MULHU,
    TEST_MULW,
    TEST_DIV,
    TEST_DIVU,
    TEST_DIVUW,
    TEST_DIVW,
    TEST_REM,
    TEST_REMU,
    TEST_REMW,
    TEST_REMUW,
  };
  bool total_error = false;

  TEST_LIST test_set[] = {
    TEST_MUL, TEST_MULH, TEST_MULHSU, TEST_MULHU, TEST_MULW, TEST_DIV,
    TEST_DIVU,
    TEST_DIVUW, TEST_DIVW, TEST_REM, TEST_REMU, TEST_REMW, TEST_REMUW,
  };
  for (TEST_LIST testcase : test_set) {
    bool error = false;
    uint32_t base;
    std::string cmdname;
    switch (testcase) {
      case TEST_MUL:
        base = 0b00000010000000000000000000110011;
        cmdname = "MUL";
        break;
      case TEST_MULH:
        base = 0b00000010000000000001000000110011;
        cmdname = "MULH";
        break;
      case TEST_MULHSU:
        base = 0b00000010000000000010000000110011;
        cmdname = "MULHSU";
        break;
      case TEST_MULHU:
        base = 0b00000010000000000011000000110011;
        cmdname = "MULHU";
        break;
      case TEST_MULW:
        base = 0b00000010000000000000000000111011;
        cmdname = "MULW";
        break;
      case TEST_DIV:
        base = 0b00000010000000000100000000110011;
        cmdname = "DIV";
        break;
      case TEST_DIVU:
        base = 0b00000010000000000101000000110011;
        cmdname = "DIVU";
        break;
      case TEST_DIVUW:
        base = 0b00000010000000000101000000111011;
        cmdname = "DIVUW";
        break;
      case TEST_DIVW:
        base = 0b00000010000000000100000000111011;
        cmdname = "DIVUW";
        break;
      case TEST_REM:
        base = 0b00000010000000000110000000110011;
        cmdname = "REM";
        break;
      case TEST_REMU:
        base = 0b00000010000000000111000000110011;
        cmdname = "REMU";
        break;
      case TEST_REMW:
        base = 0b00000010000000000110000000111011;
        cmdname = "REMW";
        break;
      case TEST_REMUW:
        base = 0b00000010000000000111000000111011;
        cmdname = "REMUW";
        break;
      default:
        printf("Test case is not defined yet\n");
        return true;
        break;
    }
    uint8_t opcode = base & 0b01111111;
    uint8_t funct3 = (base >> 12) & 0b111;
    uint8_t funct7 = (base >> 25) & 0b1111111;

    for (int i = 0; i < TEST_NUM && !error; i++) {
      uint32_t cmd = 0;
      uint8_t rd = rnd() % 32;
      uint8_t rs1 = rnd() % 32;
      uint8_t rs2 = rnd() % 32;
      switch (testcase) {
        case TEST_MUL:
          cmd = AsmMul(rd, rs1, rs2);
          break;
        case TEST_MULH:
          cmd = AsmMulh(rd, rs1, rs2);
          break;
        case TEST_MULHSU:
          cmd = AsmMulhsu(rd, rs1, rs2);
          break;
        case TEST_MULHU:
          cmd = AsmMulhu(rd, rs1, rs2);
          break;
        case TEST_MULW:
          cmd = AsmMulw(rd, rs1, rs2);
          break;
        case TEST_DIV:
          cmd = AsmDiv(rd, rs1, rs2);
          break;
        case TEST_DIVU:
          cmd = AsmDivu(rd, rs1, rs2);
          break;
        case TEST_DIVUW:
          cmd = AsmDivuw(rd, rs1, rs2);
          break;
        case TEST_DIVW:
          cmd = AsmDivw(rd, rs1, rs2);
          break;
        case TEST_REM:
          cmd = AsmRem(rd, rs1, rs2);
          break;
        case TEST_REMU:
          cmd = AsmRemu(rd, rs1, rs2);
          break;
        case TEST_REMW:
          cmd = AsmRemw(rd, rs1, rs2);
          break;
        case TEST_REMUW:
          cmd = AsmRemuw(rd, rs1, rs2);
          break;
        default:
          break;
      }
      uint32_t exp = gen_r_type(base, rd, rs1, rs2);
      std::string test_string = cmdname + " " + std::to_string(rd) + ", " +
                                std::to_string(rs1) + ", " +
                                std::to_string(rs2);
      error |= check_equal_quiet(test_string, cmd, exp, verbose);
      error |= test_r_type_decode_quiet(exp, opcode, funct3, funct7, rd, rs1,
                                        rs2, verbose);
    }
    print_error_result(cmdname, TEST_NUM, error, verbose);
    total_error |= error;
  }
  return total_error;
}

bool test_compact(bool verbose = false) {
  enum TEST_LIST {
    TEST_CADD, TEST_CEBREAK, TEST_CJALR, TEST_CJR, TEST_CLDSP, TEST_CLWSP,
    TEST_CSDSP,
    TEST_CMV, TEST_SLLI, TEST_CSWSP,
    TEST_CADDI, TEST_CADDI16SP, TEST_CADDIW, TEST_CAND, TEST_COR,
    TEST_CSUB, TEST_CSUBW, TEST_CXOR,
    TEST_CSRAI, TEST_CSRLI,
    TEST_CADDW, TEST_CANDI, TEST_CBEQZ, TEST_CBNEZ,
    TEST_CJ, TEST_CJAL, TEST_CLI, TEST_CLUI,
    TEST_CADDI4SPN,
    TEST_CFLDSP, TEST_CFLWSP, TEST_CFSDSP, TEST_CFSWSP,
    TEST_CFLD, TEST_CFLW, TEST_CFSD, TEST_CFSW,
    TEST_CLD, TEST_CLW, TEST_CSD, TEST_CSW,
  };
  bool total_error = false;

  TEST_LIST test_set[] = {
    TEST_CADD, TEST_CEBREAK, TEST_CJALR, TEST_CJR, TEST_CLDSP, TEST_CLWSP,
    TEST_CSDSP,
    TEST_CMV, TEST_SLLI, TEST_CSWSP,
    TEST_CADDI, TEST_CADDI16SP, TEST_CADDIW, TEST_CAND, TEST_COR,
    TEST_CSUB, TEST_CSUBW, TEST_CXOR,
    TEST_CSRAI, TEST_CSRLI,
    TEST_CADDW, TEST_CANDI, TEST_CBEQZ, TEST_CBNEZ,
    TEST_CJ, TEST_CJAL, TEST_CLI, TEST_CLUI,
    TEST_CADDI4SPN,
    TEST_CFLDSP, TEST_CFLWSP, TEST_CFSDSP, TEST_CFSWSP,
    TEST_CFLD, TEST_CFLW, TEST_CFSD, TEST_CFSW,
    TEST_CLD, TEST_CLW, TEST_CSD, TEST_CSW,
  };
  for (TEST_LIST testcase : test_set) {
    bool error = false;
    std::string cmdname;

    for (int i = 0; i < TEST_NUM && !error; i++) {
      uint16_t cmd;
      uint32_t rd = rnd() % 32;
      uint32_t rs1 = rnd() % 32;
      uint32_t rs2 = rnd() % 32;
      uint32_t uimm = rnd();
      int32_t imm = static_cast<int32_t>(uimm);
      switch (testcase) {
        case TEST_CADD:
          cmd = AsmCAdd(rd, rs2);
          break;
        case TEST_CEBREAK:
          cmd = AsmCEbreak();
          break;
        case TEST_CFLDSP:
          uimm = uimm & 0b0111111000;
          cmd = AsmCFldsp(rd, uimm);
          break;
        case TEST_CFLWSP:
          uimm &= 0b011111100;
          cmd = AsmCFlwsp(rd, uimm);
          break;
        case TEST_CFSDSP:
          uimm &= 0b0111111000;
          cmd = AsmCFsdsp(rs2, uimm);
          break;
        case TEST_CFSWSP:
          uimm &= 0b011111100;
          cmd = AsmCFswsp(rs2, uimm);
          break;
        case TEST_CJALR:
          cmd = AsmCJalr(rs1);
          break;
        case TEST_CJR:
          cmd = AsmCJr(rs1);
          break;
        case TEST_CLDSP:
          uimm &= 0b0111111000;
          cmd = AsmCLdsp(rd, uimm);
          break;
        case TEST_CLWSP:
          uimm &= 0b011111100;
          cmd = AsmCLwsp(rd, uimm);
          break;
        case TEST_CMV:
          cmd = AsmCMv(rd, rs2);
          break;
        case TEST_CSDSP:
          uimm &= 0b0111111000;
          cmd = AsmCSdsp(rs2, uimm);
          break;
        case TEST_SLLI:
          uimm &= 0b0111111;
          cmd = AsmCSlli(rd, uimm);
          break;
        case TEST_CSWSP:
          uimm &= 0b011111100;
          cmd = AsmCSwsp(rs2, uimm);
          break;
        case TEST_CADDI:
        case TEST_CLI:
          imm = SignExtend(imm, 6);
          if (testcase == TEST_CADDI) {
            cmd = AsmCAddi(rd, imm);
          } else {
            cmd = AsmCLi(rd, imm);
          }
          break;
        case TEST_CANDI:
        case TEST_CSRAI:
        case TEST_CSRLI:
          imm = SignExtend(imm, 6);
          rd = 8 + (rd & 0b111);
          if (testcase == TEST_CANDI) {
            cmd = AsmCAndi(rd, imm);
          } else if (testcase == TEST_CSRAI) {
            cmd = AsmCSrai(rd, imm);
          } else if (testcase == TEST_CSRLI) {
            cmd = AsmCSrli(rd, imm);
          }
          break;
        case TEST_CADDI16SP:
          imm &= 0b1111110000;
          imm = SignExtend(imm, 10);
          cmd = AsmCAddi16sp(imm);
          break;
        case TEST_CADDIW:
          imm = SignExtend(imm, 6);
          cmd = AsmCAddiw(rd, imm);
          break;
        case TEST_CAND:
        case TEST_CADDW:
        case TEST_COR:
        case TEST_CSUB:
        case TEST_CSUBW:
        case TEST_CXOR:
          rd = 8 + (rd & 0b111);
          rs2 = 8 + (rs2 & 0b111);
          if (testcase == TEST_CAND) {
            cmd = AsmCAnd(rd, rs2);
          } else if (testcase == TEST_CADDW) {
            cmd = AsmCAddw(rd, rs2);
          } else if (testcase == TEST_COR) {
            cmd = AsmCOr(rd, rs2);
          } else if (testcase == TEST_CSUB) {
            cmd = AsmCSub(rd, rs2);
          } else if (testcase == TEST_CSUBW) {
            cmd = AsmCSubw(rd, rs2);
          } else if (testcase == TEST_CXOR) {
            cmd = AsmCXor(rd, rs2);
          }
          break;
        case TEST_CBEQZ:
        case TEST_CBNEZ:
          rs1 = 8 + (rs1 & 0b111);
          imm = SignExtend(imm & 0b111111110, 9);
          if (testcase == TEST_CBEQZ) {
            cmd = AsmCBeqz(rs1, imm);
          } else if (testcase == TEST_CBNEZ) {
            cmd = AsmCBnez(rs1, imm);
          }
          break;
        case TEST_CJ:
        case TEST_CJAL:
          imm = SignExtend(imm & 0b111111111110, 12);
          if (testcase == TEST_CJ) {
            cmd = AsmCJ(imm);
          } else if (testcase == TEST_CJAL) {
            cmd = AsmCJal(imm);
          }
          break;
        case TEST_CLUI:
          imm = SignExtend(imm & 0b111111000000000000, 18);
          cmd = AsmCLui(rd, imm);
          break;
        case TEST_CADDI4SPN:
          rd = 8 + (rd & 0b111);
          uimm &= 0b01111111000;
          cmd = AsmCAddi4spn(rd, uimm);
          break;
        case TEST_CFLD:
        case TEST_CFLW:
        case TEST_CFSD:
        case TEST_CFSW:
        case TEST_CLD:
        case TEST_CLW:
        case TEST_CSD:
        case TEST_CSW:
          rd = 8 + (rd & 0b111);
          rs1 = 8 + (rs1 & 0b111);
          rs2 = 8 + (rs2 & 0b111);
          uimm = (testcase == TEST_CLW || testcase == TEST_CSW || testcase == TEST_CFLW || testcase == TEST_CFSW) ? uimm & 0b1111100 : uimm & 0b11111000;
          if (testcase == TEST_CFLD) {
            cmd = AsmCFld(rd, rs1, uimm);
          } else if (testcase == TEST_CFSD) {
            cmd = AsmCFsd(rs1, rs2, uimm);
          } else if (testcase == TEST_CFLW) {
            cmd = AsmCFlw(rd, rs1, uimm);
          } else if (testcase == TEST_CFSW) {
            cmd = AsmCFsw(rs1, rs2, uimm);
          } else if (testcase == TEST_CLD) {
            cmd = AsmCLd(rd, rs1, uimm);
          } else if (testcase == TEST_CLW) {
            cmd = AsmCLw(rd, rs1, uimm);
          } else if (testcase == TEST_CSD) {
            cmd = AsmCSd(rs1, rs2, uimm);
          } else if (testcase == TEST_CSW) {
            cmd = AsmCsw(rs1, rs2, uimm);
          }
          break;
        default:
          break;
      }

      // Generate expectation and decoded.
      uint32_t rd_dec = rd;
      uint32_t rs1_dec = rs1;
      uint32_t rs2_dec = rs2;
      uint32_t uimm_dec = uimm;
      int32_t imm_dec = imm;
      uint16_t exp = 0;
      uint16_t msk = 0b1110000000000011;
      switch (testcase) {
        case TEST_CADD:
          exp = 0b1001000000000010;
          rd_dec = bitcrop(cmd, 5, 7);
          rs2_dec = bitcrop(cmd, 5, 2);
          cmdname = "C.ADD";
          break;
        case TEST_CEBREAK:
          exp = 0b1001000000000010;
          msk = 0b1111111111111111;
          cmdname = "C.EBREAK";
          break;
        case TEST_CFLDSP:
          exp = 0b0010000000000010;
          rd_dec = bitcrop(cmd, 5, 7);
          uimm_dec = bitcrop(cmd, 1, 12) << 5;
          uimm_dec |= bitcrop(cmd, 2, 5) << 3;
          uimm_dec |= bitcrop(cmd, 3, 2) << 6;
          cmdname = "C.FLDSP";
          break;
        case TEST_CFLWSP:
          exp = 0b0110000000000010;
          rd_dec = bitcrop(cmd, 5, 7);
          uimm_dec = bitcrop(cmd, 1, 12) << 5;
          uimm_dec |= bitcrop(cmd, 3, 4) << 2;
          uimm_dec |= bitcrop(cmd, 2, 2) << 6;
          cmdname = "C.FLWSP";
          break;
        case TEST_CFSDSP:
          exp = 0b1010000000000010;
          rs2_dec = bitcrop(cmd, 5, 2);
          uimm_dec = bitcrop(cmd, 3, 10) << 3;
          uimm_dec |= bitcrop(cmd, 3, 7) << 6;
          cmdname = "C.FSDSP";
          break;
        case TEST_CFSWSP:
          exp = 0b1110000000000010;
          rs2_dec = bitcrop(cmd, 5, 2);
          uimm_dec = bitcrop(cmd, 4, 9) << 2;
          uimm_dec |= bitcrop(cmd, 2, 7) << 6;
          cmdname = "C.FSWSP";
          break;
        case TEST_CJALR:
          exp = 0b1001000000000010;
          msk = 0b1111000001111111;
          rs1_dec = bitcrop(cmd, 5, 7);
          cmdname = "C.JALR";
          break;
        case TEST_CJR:
          exp = 0b1000000000000010;
          msk = 0b1111000001111111;
          rs1_dec = bitcrop(cmd, 5, 7);
          cmdname = "C.JR";
          break;
        case TEST_CLDSP:
          exp = 0b0110000000000010;
          rd_dec = bitcrop(cmd, 5, 7);
          uimm_dec = bitcrop(cmd, 1, 12) << 5;
          uimm_dec |= bitcrop(cmd, 2, 5) << 3;
          uimm_dec |= bitcrop(cmd, 3, 2) << 6;
          cmdname = "C.LDSP";
          break;
        case TEST_CLWSP:
          exp = 0b0100000000000010;
          rd_dec = bitcrop(cmd, 5, 7);
          uimm_dec = bitcrop(cmd, 1, 12) << 5;
          uimm_dec |= bitcrop(cmd, 3, 4) << 2;
          uimm_dec |= bitcrop(cmd, 2, 2) << 6;
          cmdname = "C.LWSP";
          break;
        case TEST_CMV:
          exp = 0b1000000000000010;
          msk = 0b1111000000000011;
          rd_dec = bitcrop(cmd, 5, 7);
          rs2_dec = bitcrop(cmd, 5, 2);
          cmdname = "C.MV";
          break;
        case TEST_CSDSP:
          exp = 0b1110000000000010;
          rs2_dec = bitcrop(cmd, 5, 2);
          uimm_dec = bitcrop(cmd, 3, 10) << 3;
          uimm_dec |= bitcrop(cmd, 3, 7) << 6;
          cmdname = "C.SDSP";
          break;
        case TEST_SLLI:
          exp = 0b0000000000000010;
          rd_dec = bitcrop(cmd, 5, 7);
          uimm_dec = bitcrop(cmd, 1, 12) << 5;
          uimm_dec |= bitcrop(cmd, 5, 2);
          cmdname = "C.SLLI";
          break;
        case TEST_CSWSP:
          exp = 0b1100000000000010;
          rs2 = bitcrop(cmd, 5, 2);
          uimm_dec = bitcrop(cmd, 4, 9) << 2;
          uimm_dec |= bitcrop(cmd, 2, 7) << 6;
          cmdname = "C.SWSP";
          break;
        case TEST_CADDI:
        case TEST_CADDIW:
        case TEST_CLI:
          if (testcase == TEST_CADDI) {
            exp = 0b0000000000000001;
            cmdname = "C.ADDI";
          } else if (testcase == TEST_CADDIW) {
            exp = 0b0010000000000001;
            cmdname = "C.ADDIW";
          } else if (testcase == TEST_CLI) {
            exp = 0b0100000000000001;
            cmdname = "C.LI";
          }
          rd = bitcrop(cmd, 5, 7);
          imm_dec = bitcrop(cmd, 1, 12) << 5;
          imm_dec |= bitcrop(cmd, 5, 2);
          imm_dec = SignExtend(imm_dec, 6);
          break;
        case TEST_CADDI16SP:
          exp = 0b0110000100000001;
          msk = 0b1110111110000011;
          imm_dec = bitcrop(cmd, 1, 12) << 9;
          imm_dec |= bitcrop(cmd, 1, 2) << 5;
          imm_dec |= bitcrop(cmd, 2, 3) << 7;
          imm_dec |= bitcrop(cmd, 1, 5) << 6;
          imm_dec |= bitcrop(cmd, 1, 6) << 4;
          imm_dec = SignExtend(imm_dec, 10);
          cmdname = "C.ADDI16SP";
          break;
        case TEST_CAND:
        case TEST_CADDW:
        case TEST_COR:
        case TEST_CSUB:
        case TEST_CSUBW:
        case TEST_CXOR:
          if (testcase == TEST_CAND) {
            exp = 0b1000110001100001;
            cmdname = "C.AND";
          } else if (testcase == TEST_CADDW) {
            exp = 0b1001110000100001;
            cmdname = "C.AND";
          } else if (testcase == TEST_COR) {
            exp = 0b1000110001000001;
            cmdname = "C.OR";
          } else if (testcase == TEST_CSUB) {
            exp = 0b1000110000000001;
            cmdname = "C.SUB";
          } else if (testcase == TEST_CSUBW) {
            exp = 0b1001110000000001;
            cmdname = "C.SUBW";
          } else if (testcase == TEST_CXOR) {
            exp = 0b1000110000100001;
            cmdname = "C.XOR";
          }
          msk = 0b1111110001100011;
          rd_dec = bitcrop(cmd, 3, 7) + 8;
          rs2_dec = bitcrop(cmd, 3, 2) + 8;
          break;
        case TEST_CANDI:
        case TEST_CSRAI:
        case TEST_CSRLI:
          if (testcase == TEST_CANDI) {
            exp = 0b1000100000000001;
            cmdname = "C.ANDI";
          } else if (testcase == TEST_CSRAI) {
            exp = 0b1000010000000001;
            cmdname = "C.CSRAI";
          } else if (testcase == TEST_CSRLI) {
            exp = 0b1000000000000001;
            cmdname = "C.CSRLI";
          }
          msk = 0b1110110000000011;
          rd = bitcrop(cmd, 3, 7) + 8;
          imm_dec = bitcrop(cmd, 1, 12) << 5;
          imm_dec |= bitcrop(cmd, 5, 2);
          imm_dec = SignExtend(imm_dec, 6);
          break;
        case TEST_CBEQZ:
        case TEST_CBNEZ:
          if (testcase == TEST_CBEQZ) {
            exp = 0b1100000000000001;
            cmdname = "C.BEQZ";
          } else if (testcase == TEST_CBNEZ) {
            exp = 0b1110000000000001;
            cmdname = "C.BNEZ";
          }
          rs1 = bitcrop(cmd, 3, 7) + 8;
          imm_dec = bitcrop(cmd, 1, 12) << 8;
          imm_dec |= bitcrop(cmd, 2, 10) << 3;
          imm_dec |= bitcrop(cmd, 2, 5) << 6;
          imm_dec |= bitcrop(cmd, 2, 3) << 1;
          imm_dec |= bitcrop(cmd, 1, 2) << 5;
          imm_dec = SignExtend(imm_dec, 9);
          break;
        case TEST_CJ:
        case TEST_CJAL:
          if (testcase == TEST_CJ) {
            exp = 0b1010000000000001;
            cmdname = "C.J";
          } else {
            exp = 0b0010000000000001;
            cmdname = "C.JAL";
          }
          imm_dec = bitcrop(cmd, 1, 12) << 11;
          imm_dec |= bitcrop(cmd, 1, 11) << 4;
          imm_dec |= bitcrop(cmd, 2, 9) << 8;
          imm_dec |= bitcrop(cmd, 1, 8) << 10;
          imm_dec |= bitcrop(cmd, 1, 7) << 6;
          imm_dec |= bitcrop(cmd, 1, 6) << 7;
          imm_dec |= bitcrop(cmd, 3, 3) << 1;
          imm_dec |= bitcrop(cmd, 1, 2) << 5;
          imm_dec = SignExtend(imm_dec, 12);
          break;
        case TEST_CLUI:
          exp = 0b0110000000000001;
          cmdname = "C.LUI";
          imm_dec = bitcrop(cmd, 1, 12) << 17;
          imm_dec |= bitcrop(cmd, 5, 2) << 12;
          imm_dec = SignExtend(imm_dec, 18);
          break;
        case TEST_CADDI4SPN:
          exp = 0b0000000000000000;
          cmdname = "C.ADDI4SPN";
          rd_dec = bitcrop(cmd, 3, 2) + 8;
          uimm_dec = bitcrop(cmd, 2, 11) << 4;
          uimm_dec |= bitcrop(cmd, 4, 7) << 6;
          uimm_dec |= bitcrop(cmd, 1, 6) << 2;
          uimm_dec |= bitcrop(cmd, 1, 5) << 3;
          break;
        case TEST_CFLD:
          exp = 0b0010000000000000;
          cmdname = "C.FLD";
          rd_dec = bitcrop(cmd, 3, 2) + 8;
          rs1_dec = bitcrop(cmd, 3, 7) + 8;
          uimm_dec = bitcrop(cmd, 3, 10) << 3;
          uimm_dec |= bitcrop(cmd, 2, 5) << 6;
          break;
        case TEST_CFLW:
          exp = 0b0110000000000000;
          cmdname = "C.FLW";
          rd_dec = bitcrop(cmd, 3, 2) + 8;
          rs1_dec = bitcrop(cmd, 3, 7) + 8;
          uimm_dec = bitcrop(cmd, 3, 10) << 3;
          uimm_dec |= bitcrop(cmd, 1, 6) << 2;
          uimm_dec |= bitcrop(cmd, 1, 5) << 6;
          break;
        case TEST_CFSD:
          exp = 0b1010000000000000;
          cmdname = "C.FSD";
          rs1_dec = bitcrop(cmd, 3, 7) + 8;
          rs2_dec = bitcrop(cmd, 3, 2) + 8;
          uimm_dec = bitcrop(cmd, 3, 10) << 3;
          uimm_dec |= bitcrop(cmd, 2, 5) << 6;
          break;
        case TEST_CFSW:
          exp = 0b1110000000000000;
          cmdname = "C.FSW";
          rs1_dec = bitcrop(cmd, 3, 7) + 8;
          rs2_dec = bitcrop(cmd, 3, 2) + 8;
          uimm_dec = bitcrop(cmd, 3, 10) << 3;
          uimm_dec |= bitcrop(cmd, 1, 6) << 2;
          uimm_dec |= bitcrop(cmd, 1, 5) << 6;
          break;
        case TEST_CLD:
          exp = 0b0110000000000000;
          cmdname = "C.LD";
          rs1_dec = bitcrop(cmd, 3, 7) + 8;
          rd_dec = bitcrop(cmd, 3, 2) + 8;
          uimm_dec = bitcrop(cmd, 3, 10) << 3;
          uimm_dec |= bitcrop(cmd, 2, 5) << 6;
          break;
        case TEST_CLW:
          exp = 0b0100000000000000;
          cmdname = "C.LW";
          rs1_dec = bitcrop(cmd, 3, 7) + 8;
          rd_dec = bitcrop(cmd, 3, 2) + 8;
          uimm_dec = bitcrop(cmd, 3, 10) << 3;
          uimm_dec |= bitcrop(cmd, 1, 6) << 2;
          uimm_dec |= bitcrop(cmd, 1, 5) << 6;
          break;
        case TEST_CSD:
          exp = 0b1110000000000000;
          cmdname = "C.SD";
          rs1_dec = bitcrop(cmd, 3, 7) + 8;
          rs2_dec = bitcrop(cmd, 3, 2) + 8;
          uimm_dec = bitcrop(cmd, 3, 10) << 3;
          uimm_dec |= bitcrop(cmd, 2, 5) << 6;
          break;
        case TEST_CSW:
          exp = 0b1100000000000000;
          cmdname = "C.SW";
          rs1_dec = bitcrop(cmd, 3, 7) + 8;
          rs2_dec = bitcrop(cmd, 3, 2) + 8;
          uimm_dec = bitcrop(cmd, 3, 10) << 3;
          uimm_dec |= bitcrop(cmd, 1, 6) << 2;
          uimm_dec |= bitcrop(cmd, 1, 5) << 6;
          break;
        default:
          std::cerr << "Test case is not defined yet" << std::endl;
          return true;
          break;
      }
      std::string test_string = cmdname + " " + std::to_string(rd) + ", " +
                                std::to_string(rs1) + ", " +
                                std::to_string(rs2) + ", " +
                                std::to_string(uimm);
      if ((exp & msk) != (cmd & msk) || rd != rd_dec || rs1 != rs1_dec ||
          rs2 != rs2_dec || uimm != uimm_dec || imm != imm_dec) {
        error = true;
        if (verbose) {
          std::cerr << test_string << " failed." << std::endl;
          std::cerr << "Expected: " << std::bitset<16>(exp & msk);
          std::cerr << ", Actual: " << std::bitset<16>(cmd & msk) << std::endl;
          std::cerr << "Decoded rd: " << rd_dec << "(" << rd << ")"
                    << std::endl;
          std::cerr << "Decoded rs1: " << rs1_dec << "(" << rs1 << ")"
                    << std::endl;
          std::cerr << "Decoded rs2: " << rs2_dec << "(" << rs2 << ")"
                    << std::endl;
          std::cerr << "Decoded uimm: " << uimm_dec << "(" << uimm << ")"
                    << std::endl;
          std::cerr << "Decoded imm: " << imm_dec << "(" << imm << ")"
                    << std::endl;
        }
      }
    }
    print_error_result(cmdname, TEST_NUM, error, verbose);
    total_error |= error;
  }
  return total_error;
}

bool RunAllTests() {
  init_random();
  bool verbose = true;
  bool error = false;
  error |= test_r_type(verbose);
  error |= test_i_type(verbose);
  error |= test_b_type(verbose);
  error |= test_j_type(verbose);
  error |= test_s_type(verbose);
  error |= test_u_type(verbose);
  error |= test_amo_type(verbose);
  error |= test_mult(verbose);
  error |= test_compact(verbose);

  if (error) {
    printf("Test failed\n");
  } else {
    printf("Test passed\n");
  }
  return error;
}

} // namespace anonymous

int main() {
  return RunAllTests();
}
