# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/grape/Projects/Interview/NetCheckers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/grape/Projects/Interview/NetCheckers/build

# Include any dependencies generated for this target.
include Checkers/CMakeFiles/Checkers.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Checkers/CMakeFiles/Checkers.dir/compiler_depend.make

# Include the progress variables for this target.
include Checkers/CMakeFiles/Checkers.dir/progress.make

# Include the compile flags for this target's objects.
include Checkers/CMakeFiles/Checkers.dir/flags.make

Checkers/CMakeFiles/Checkers.dir/main.cpp.o: Checkers/CMakeFiles/Checkers.dir/flags.make
Checkers/CMakeFiles/Checkers.dir/main.cpp.o: ../Checkers/main.cpp
Checkers/CMakeFiles/Checkers.dir/main.cpp.o: Checkers/CMakeFiles/Checkers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/grape/Projects/Interview/NetCheckers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Checkers/CMakeFiles/Checkers.dir/main.cpp.o"
	cd /home/grape/Projects/Interview/NetCheckers/build/Checkers && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Checkers/CMakeFiles/Checkers.dir/main.cpp.o -MF CMakeFiles/Checkers.dir/main.cpp.o.d -o CMakeFiles/Checkers.dir/main.cpp.o -c /home/grape/Projects/Interview/NetCheckers/Checkers/main.cpp

Checkers/CMakeFiles/Checkers.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Checkers.dir/main.cpp.i"
	cd /home/grape/Projects/Interview/NetCheckers/build/Checkers && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/grape/Projects/Interview/NetCheckers/Checkers/main.cpp > CMakeFiles/Checkers.dir/main.cpp.i

Checkers/CMakeFiles/Checkers.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Checkers.dir/main.cpp.s"
	cd /home/grape/Projects/Interview/NetCheckers/build/Checkers && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/grape/Projects/Interview/NetCheckers/Checkers/main.cpp -o CMakeFiles/Checkers.dir/main.cpp.s

# Object files for target Checkers
Checkers_OBJECTS = \
"CMakeFiles/Checkers.dir/main.cpp.o"

# External object files for target Checkers
Checkers_EXTERNAL_OBJECTS =

bin/Checkers: Checkers/CMakeFiles/Checkers.dir/main.cpp.o
bin/Checkers: Checkers/CMakeFiles/Checkers.dir/build.make
bin/Checkers: lib/libCore.a
bin/Checkers: Checkers/CMakeFiles/Checkers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/grape/Projects/Interview/NetCheckers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/Checkers"
	cd /home/grape/Projects/Interview/NetCheckers/build/Checkers && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Checkers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Checkers/CMakeFiles/Checkers.dir/build: bin/Checkers
.PHONY : Checkers/CMakeFiles/Checkers.dir/build

Checkers/CMakeFiles/Checkers.dir/clean:
	cd /home/grape/Projects/Interview/NetCheckers/build/Checkers && $(CMAKE_COMMAND) -P CMakeFiles/Checkers.dir/cmake_clean.cmake
.PHONY : Checkers/CMakeFiles/Checkers.dir/clean

Checkers/CMakeFiles/Checkers.dir/depend:
	cd /home/grape/Projects/Interview/NetCheckers/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/grape/Projects/Interview/NetCheckers /home/grape/Projects/Interview/NetCheckers/Checkers /home/grape/Projects/Interview/NetCheckers/build /home/grape/Projects/Interview/NetCheckers/build/Checkers /home/grape/Projects/Interview/NetCheckers/build/Checkers/CMakeFiles/Checkers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Checkers/CMakeFiles/Checkers.dir/depend
