# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/moiz/bin/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/moiz/bin/clion/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/moiz/work/BuildCPU/Emulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/moiz/work/BuildCPU/Emulator/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Emulator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Emulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Emulator.dir/flags.make

CMakeFiles/Emulator.dir/assembler.cc.o: CMakeFiles/Emulator.dir/flags.make
CMakeFiles/Emulator.dir/assembler.cc.o: ../assembler.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/moiz/work/BuildCPU/Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Emulator.dir/assembler.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Emulator.dir/assembler.cc.o -c /home/moiz/work/BuildCPU/Emulator/assembler.cc

CMakeFiles/Emulator.dir/assembler.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Emulator.dir/assembler.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/moiz/work/BuildCPU/Emulator/assembler.cc > CMakeFiles/Emulator.dir/assembler.cc.i

CMakeFiles/Emulator.dir/assembler.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Emulator.dir/assembler.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/moiz/work/BuildCPU/Emulator/assembler.cc -o CMakeFiles/Emulator.dir/assembler.cc.s

CMakeFiles/Emulator.dir/bit_tools.cc.o: CMakeFiles/Emulator.dir/flags.make
CMakeFiles/Emulator.dir/bit_tools.cc.o: ../bit_tools.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/moiz/work/BuildCPU/Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Emulator.dir/bit_tools.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Emulator.dir/bit_tools.cc.o -c /home/moiz/work/BuildCPU/Emulator/bit_tools.cc

CMakeFiles/Emulator.dir/bit_tools.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Emulator.dir/bit_tools.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/moiz/work/BuildCPU/Emulator/bit_tools.cc > CMakeFiles/Emulator.dir/bit_tools.cc.i

CMakeFiles/Emulator.dir/bit_tools.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Emulator.dir/bit_tools.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/moiz/work/BuildCPU/Emulator/bit_tools.cc -o CMakeFiles/Emulator.dir/bit_tools.cc.s

CMakeFiles/Emulator.dir/cpu_test.cc.o: CMakeFiles/Emulator.dir/flags.make
CMakeFiles/Emulator.dir/cpu_test.cc.o: ../cpu_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/moiz/work/BuildCPU/Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Emulator.dir/cpu_test.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Emulator.dir/cpu_test.cc.o -c /home/moiz/work/BuildCPU/Emulator/cpu_test.cc

CMakeFiles/Emulator.dir/cpu_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Emulator.dir/cpu_test.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/moiz/work/BuildCPU/Emulator/cpu_test.cc > CMakeFiles/Emulator.dir/cpu_test.cc.i

CMakeFiles/Emulator.dir/cpu_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Emulator.dir/cpu_test.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/moiz/work/BuildCPU/Emulator/cpu_test.cc -o CMakeFiles/Emulator.dir/cpu_test.cc.s

CMakeFiles/Emulator.dir/instruction_encdec.cc.o: CMakeFiles/Emulator.dir/flags.make
CMakeFiles/Emulator.dir/instruction_encdec.cc.o: ../instruction_encdec.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/moiz/work/BuildCPU/Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Emulator.dir/instruction_encdec.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Emulator.dir/instruction_encdec.cc.o -c /home/moiz/work/BuildCPU/Emulator/instruction_encdec.cc

CMakeFiles/Emulator.dir/instruction_encdec.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Emulator.dir/instruction_encdec.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/moiz/work/BuildCPU/Emulator/instruction_encdec.cc > CMakeFiles/Emulator.dir/instruction_encdec.cc.i

CMakeFiles/Emulator.dir/instruction_encdec.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Emulator.dir/instruction_encdec.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/moiz/work/BuildCPU/Emulator/instruction_encdec.cc -o CMakeFiles/Emulator.dir/instruction_encdec.cc.s

CMakeFiles/Emulator.dir/load_assembler.cc.o: CMakeFiles/Emulator.dir/flags.make
CMakeFiles/Emulator.dir/load_assembler.cc.o: ../load_assembler.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/moiz/work/BuildCPU/Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Emulator.dir/load_assembler.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Emulator.dir/load_assembler.cc.o -c /home/moiz/work/BuildCPU/Emulator/load_assembler.cc

CMakeFiles/Emulator.dir/load_assembler.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Emulator.dir/load_assembler.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/moiz/work/BuildCPU/Emulator/load_assembler.cc > CMakeFiles/Emulator.dir/load_assembler.cc.i

CMakeFiles/Emulator.dir/load_assembler.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Emulator.dir/load_assembler.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/moiz/work/BuildCPU/Emulator/load_assembler.cc -o CMakeFiles/Emulator.dir/load_assembler.cc.s

CMakeFiles/Emulator.dir/load_assembler_test.cc.o: CMakeFiles/Emulator.dir/flags.make
CMakeFiles/Emulator.dir/load_assembler_test.cc.o: ../load_assembler_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/moiz/work/BuildCPU/Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Emulator.dir/load_assembler_test.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Emulator.dir/load_assembler_test.cc.o -c /home/moiz/work/BuildCPU/Emulator/load_assembler_test.cc

CMakeFiles/Emulator.dir/load_assembler_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Emulator.dir/load_assembler_test.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/moiz/work/BuildCPU/Emulator/load_assembler_test.cc > CMakeFiles/Emulator.dir/load_assembler_test.cc.i

CMakeFiles/Emulator.dir/load_assembler_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Emulator.dir/load_assembler_test.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/moiz/work/BuildCPU/Emulator/load_assembler_test.cc -o CMakeFiles/Emulator.dir/load_assembler_test.cc.s

CMakeFiles/Emulator.dir/RISCV_cpu.cc.o: CMakeFiles/Emulator.dir/flags.make
CMakeFiles/Emulator.dir/RISCV_cpu.cc.o: ../RISCV_cpu.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/moiz/work/BuildCPU/Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Emulator.dir/RISCV_cpu.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Emulator.dir/RISCV_cpu.cc.o -c /home/moiz/work/BuildCPU/Emulator/RISCV_cpu.cc

CMakeFiles/Emulator.dir/RISCV_cpu.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Emulator.dir/RISCV_cpu.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/moiz/work/BuildCPU/Emulator/RISCV_cpu.cc > CMakeFiles/Emulator.dir/RISCV_cpu.cc.i

CMakeFiles/Emulator.dir/RISCV_cpu.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Emulator.dir/RISCV_cpu.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/moiz/work/BuildCPU/Emulator/RISCV_cpu.cc -o CMakeFiles/Emulator.dir/RISCV_cpu.cc.s

# Object files for target Emulator
Emulator_OBJECTS = \
"CMakeFiles/Emulator.dir/assembler.cc.o" \
"CMakeFiles/Emulator.dir/bit_tools.cc.o" \
"CMakeFiles/Emulator.dir/cpu_test.cc.o" \
"CMakeFiles/Emulator.dir/instruction_encdec.cc.o" \
"CMakeFiles/Emulator.dir/load_assembler.cc.o" \
"CMakeFiles/Emulator.dir/load_assembler_test.cc.o" \
"CMakeFiles/Emulator.dir/RISCV_cpu.cc.o"

# External object files for target Emulator
Emulator_EXTERNAL_OBJECTS =

Emulator: CMakeFiles/Emulator.dir/assembler.cc.o
Emulator: CMakeFiles/Emulator.dir/bit_tools.cc.o
Emulator: CMakeFiles/Emulator.dir/cpu_test.cc.o
Emulator: CMakeFiles/Emulator.dir/instruction_encdec.cc.o
Emulator: CMakeFiles/Emulator.dir/load_assembler.cc.o
Emulator: CMakeFiles/Emulator.dir/load_assembler_test.cc.o
Emulator: CMakeFiles/Emulator.dir/RISCV_cpu.cc.o
Emulator: CMakeFiles/Emulator.dir/build.make
Emulator: CMakeFiles/Emulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/moiz/work/BuildCPU/Emulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable Emulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Emulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Emulator.dir/build: Emulator

.PHONY : CMakeFiles/Emulator.dir/build

CMakeFiles/Emulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Emulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Emulator.dir/clean

CMakeFiles/Emulator.dir/depend:
	cd /home/moiz/work/BuildCPU/Emulator/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/moiz/work/BuildCPU/Emulator /home/moiz/work/BuildCPU/Emulator /home/moiz/work/BuildCPU/Emulator/cmake-build-debug /home/moiz/work/BuildCPU/Emulator/cmake-build-debug /home/moiz/work/BuildCPU/Emulator/cmake-build-debug/CMakeFiles/Emulator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Emulator.dir/depend

