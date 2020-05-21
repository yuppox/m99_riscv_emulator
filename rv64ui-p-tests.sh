#!/bin/bash
test_list=(
  "target/share/riscv-tests/isa/rv64ui-p-add"
  "target/share/riscv-tests/isa/rv64ui-p-sb"
  "target/share/riscv-tests/isa/rv64ui-p-addi"
  "target/share/riscv-tests/isa/rv64ui-p-sd"
  "target/share/riscv-tests/isa/rv64ui-p-addiw"
  "target/share/riscv-tests/isa/rv64ui-p-sh"
  "target/share/riscv-tests/isa/rv64ui-p-addw"
  "target/share/riscv-tests/isa/rv64ui-p-simple"
  "target/share/riscv-tests/isa/rv64ui-p-and"
  "target/share/riscv-tests/isa/rv64ui-p-sll"
  "target/share/riscv-tests/isa/rv64ui-p-andi"
  "target/share/riscv-tests/isa/rv64ui-p-slli"
  "target/share/riscv-tests/isa/rv64ui-p-auipc"
  "target/share/riscv-tests/isa/rv64ui-p-slliw"
  "target/share/riscv-tests/isa/rv64ui-p-beq"
  "target/share/riscv-tests/isa/rv64ui-p-sllw"
  "target/share/riscv-tests/isa/rv64ui-p-bge"
  "target/share/riscv-tests/isa/rv64ui-p-slt"
  "target/share/riscv-tests/isa/rv64ui-p-bgeu"          
  "target/share/riscv-tests/isa/rv64ui-p-slti"
  "target/share/riscv-tests/isa/rv64ui-p-blt"
  "target/share/riscv-tests/isa/rv64ui-p-sltiu"
  "target/share/riscv-tests/isa/rv64ui-p-bltu"
  "target/share/riscv-tests/isa/rv64ui-p-sltu"
  "target/share/riscv-tests/isa/rv64ui-p-bne"
  "target/share/riscv-tests/isa/rv64ui-p-sra"
  "target/share/riscv-tests/isa/rv64ui-p-fence_i"
  "target/share/riscv-tests/isa/rv64ui-p-srai"
  "target/share/riscv-tests/isa/rv64ui-p-jal"
  "target/share/riscv-tests/isa/rv64ui-p-sraiw"
  "target/share/riscv-tests/isa/rv64ui-p-jalr"
  "target/share/riscv-tests/isa/rv64ui-p-sraw"
  "target/share/riscv-tests/isa/rv64ui-p-lb"
  "target/share/riscv-tests/isa/rv64ui-p-srl"
  "target/share/riscv-tests/isa/rv64ui-p-lbu"
  "target/share/riscv-tests/isa/rv64ui-p-srli"
  "target/share/riscv-tests/isa/rv64ui-p-ld"
  "target/share/riscv-tests/isa/rv64ui-p-srliw"
  "target/share/riscv-tests/isa/rv64ui-p-lh"
  "target/share/riscv-tests/isa/rv64ui-p-srlw"
  "target/share/riscv-tests/isa/rv64ui-p-lhu"
  "target/share/riscv-tests/isa/rv64ui-p-sub"
  "target/share/riscv-tests/isa/rv64ui-p-lui"
  "target/share/riscv-tests/isa/rv64ui-p-subw"
  "target/share/riscv-tests/isa/rv64ui-p-lw"
  "target/share/riscv-tests/isa/rv64ui-p-sw"
  "target/share/riscv-tests/isa/rv64ui-p-lwu"
  "target/share/riscv-tests/isa/rv64ui-p-xor"
  "target/share/riscv-tests/isa/rv64ui-p-or"
  "target/share/riscv-tests/isa/rv64ui-p-xori"
  "target/share/riscv-tests/isa/rv64ui-p-ori"
)
emulater="./RISCV_Emulator"
flag="-h -64"
for test in "${test_list[@]}"; do
  echo -n "Run ${test} test: "
  $(eval "${emulater}  ${flag} ${test} 2> /dev/null")
  exit_status=$?
  if [[ ${exit_status} -eq 0 ]]; then
    echo "Pass"
  else
    echo "Fail"
    exit ${exit_status}
  fi
done
echo "All tests passed."
exit 0
