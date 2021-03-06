//
// Created by moiz on 1/19/20.
//

#ifndef MEMORY_WRAPPER_H
#define MEMORY_WRAPPER_H

#include <vector>
#include <cstdint>
#include <array>
#include <stdexcept>

namespace RISCV_EMULATOR {

class MemoryWrapperIterator; // Forward declaration.
class MemoryWrapper;

constexpr int GenerateBitMask(const int bits) {
  int mask = 0;
  for (int i = 0; i < bits; i++) {
    mask = (mask << 1) | 0b1;
  }
  return mask;
}

class MemoryWrapper {
  static constexpr int kTotalBits = 32;
  static constexpr int kOffsetBits = 20;
  static constexpr int kWordBits = 2;
  static constexpr int kOffsetMask = GenerateBitMask(kOffsetBits);
  static constexpr int kEntryBits = kTotalBits - kOffsetBits;
  static constexpr int kEntryMask = GenerateBitMask(kEntryBits);
  static constexpr int kMapEntry = 1 << kEntryBits;
  static constexpr size_t kMaxAddress = ((1ull << kTotalBits) - 1);
public:
  MemoryWrapper();

  const uint8_t ReadByte(size_t i) const;

  const uint16_t Read16(size_t i) const;

  const uint32_t Read32(size_t i) const;

  const uint64_t Read64(size_t i) const;

  void WriteByte(size_t i, uint8_t data);

  void Write16(size_t i, uint16_t value);

  void Write32(size_t i, uint32_t value);

  void Write64(size_t i, uint64_t value);

  MemoryWrapperIterator begin();

  MemoryWrapperIterator end();

  bool operator==(MemoryWrapper &r);

  bool operator!=(MemoryWrapper &r);

private:
  inline bool CheckRange(int entry) const {
    if (entry < 0 || entry >= kMapEntry) {
      throw std::out_of_range("Memory wrapper size out of range.");
    }
    return assigned_[entry];
  }

  std::array<std::vector<uint32_t>, kMapEntry> mapping_;
  std::array<bool, kMapEntry> assigned_;
};


} // namespace RISCV_EMULATOR

#endif //MEMORY_WRAPPER_H
