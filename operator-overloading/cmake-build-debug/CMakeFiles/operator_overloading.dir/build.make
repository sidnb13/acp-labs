# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = "/Users/sidbaskaran/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.6397.106/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/sidbaskaran/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.6397.106/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sidbaskaran/Desktop/adv-cs/operator-overloading

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sidbaskaran/Desktop/adv-cs/operator-overloading/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/operator_overloading.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/operator_overloading.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/operator_overloading.dir/flags.make

CMakeFiles/operator_overloading.dir/main.cpp.o: CMakeFiles/operator_overloading.dir/flags.make
CMakeFiles/operator_overloading.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sidbaskaran/Desktop/adv-cs/operator-overloading/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/operator_overloading.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/operator_overloading.dir/main.cpp.o -c /Users/sidbaskaran/Desktop/adv-cs/operator-overloading/main.cpp

CMakeFiles/operator_overloading.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/operator_overloading.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sidbaskaran/Desktop/adv-cs/operator-overloading/main.cpp > CMakeFiles/operator_overloading.dir/main.cpp.i

CMakeFiles/operator_overloading.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/operator_overloading.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sidbaskaran/Desktop/adv-cs/operator-overloading/main.cpp -o CMakeFiles/operator_overloading.dir/main.cpp.s

# Object files for target operator_overloading
operator_overloading_OBJECTS = \
"CMakeFiles/operator_overloading.dir/main.cpp.o"

# External object files for target operator_overloading
operator_overloading_EXTERNAL_OBJECTS =

operator_overloading: CMakeFiles/operator_overloading.dir/main.cpp.o
operator_overloading: CMakeFiles/operator_overloading.dir/build.make
operator_overloading: CMakeFiles/operator_overloading.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/sidbaskaran/Desktop/adv-cs/operator-overloading/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable operator_overloading"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/operator_overloading.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/operator_overloading.dir/build: operator_overloading

.PHONY : CMakeFiles/operator_overloading.dir/build

CMakeFiles/operator_overloading.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/operator_overloading.dir/cmake_clean.cmake
.PHONY : CMakeFiles/operator_overloading.dir/clean

CMakeFiles/operator_overloading.dir/depend:
	cd /Users/sidbaskaran/Desktop/adv-cs/operator-overloading/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sidbaskaran/Desktop/adv-cs/operator-overloading /Users/sidbaskaran/Desktop/adv-cs/operator-overloading /Users/sidbaskaran/Desktop/adv-cs/operator-overloading/cmake-build-debug /Users/sidbaskaran/Desktop/adv-cs/operator-overloading/cmake-build-debug /Users/sidbaskaran/Desktop/adv-cs/operator-overloading/cmake-build-debug/CMakeFiles/operator_overloading.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/operator_overloading.dir/depend

