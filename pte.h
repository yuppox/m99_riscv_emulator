//
// Created by moiz on 2/15/20.
//

#ifndef ASSEMBLER_TEST_PTE_H
#define ASSEMBLER_TEST_PTE_H

#include <cstdint>

namespace RISCV_EMULATOR {

class Pte32 {
public:
  Pte32();

  Pte32(uint32_t pte_value);

  Pte32 &operator=(uint32_t pte_value);

  uint32_t GetValue() const;

  uint32_t GetPpn() const;

  uint32_t GetPpn1() const;

  uint32_t GetPpn0() const;

  uint32_t GetRsw() const;

  uint32_t GetD() const;

  uint32_t GetA() const;

  uint32_t GetG() const;

  uint32_t GetU() const;

  uint32_t GetX() const;

  uint32_t GetW() const;

  uint32_t GetR() const;

  uint32_t GetV() const;

  void SetPpn(uint32_t);

  void SetRsw(uint32_t);

  void SetD(int value);

  void SetA(int value);

  void SetG(int value);

  void SetU(int value);

  void SetX(int value);

  void SetW(int value);

  void SetR(int value);

  void SetV(int value);

  bool IsLeaf() const;

  bool IsValid() const;

private:
  uint32_t pte_;
};

class Pte64 {
public:
  Pte64();

  Pte64(uint64_t pte_value);

  Pte64 &operator=(uint64_t pte_value);

  uint64_t GetValue() const;

  uint32_t GetPpn() const;

  uint32_t GetPpn2() const;

  uint32_t GetPpn1() const;

  uint32_t GetPpn0() const;

  uint32_t GetRsw() const;

  uint32_t GetD() const;

  uint32_t GetA() const;

  uint32_t GetG() const;

  uint32_t GetU() const;

  uint32_t GetX() const;

  uint32_t GetW() const;

  uint32_t GetR() const;

  uint32_t GetV() const;

  void SetPpn(uint64_t);

  void SetRsw(uint32_t);

  void SetD(int value);

  void SetA(int value);

  void SetG(int value);

  void SetU(int value);

  void SetX(int value);

  void SetW(int value);

  void SetR(int value);

  void SetV(int value);

  bool IsLeaf() const;

  bool IsValid() const;

private:
  uint64_t pte_;
};

} // namespace RISCV_EMULATOR

#endif //ASSEMBLER_TEST_PTE_H
