# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /home/ubuntu/cmake-3.27.1-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/ubuntu/cmake-3.27.1-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/YouShuangExample/chapter6/chapter6.3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/YouShuangExample/chapter6/chapter6.3/build_test

# Include any dependencies generated for this target.
include CMakeFiles/YouShuangExample_6.3_client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/YouShuangExample_6.3_client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/YouShuangExample_6.3_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/YouShuangExample_6.3_client.dir/flags.make

CMakeFiles/YouShuangExample_6.3_client.dir/src/client.cpp.o: CMakeFiles/YouShuangExample_6.3_client.dir/flags.make
CMakeFiles/YouShuangExample_6.3_client.dir/src/client.cpp.o: /home/ubuntu/YouShuangExample/chapter6/chapter6.3/src/client.cpp
CMakeFiles/YouShuangExample_6.3_client.dir/src/client.cpp.o: CMakeFiles/YouShuangExample_6.3_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ubuntu/YouShuangExample/chapter6/chapter6.3/build_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/YouShuangExample_6.3_client.dir/src/client.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/YouShuangExample_6.3_client.dir/src/client.cpp.o -MF CMakeFiles/YouShuangExample_6.3_client.dir/src/client.cpp.o.d -o CMakeFiles/YouShuangExample_6.3_client.dir/src/client.cpp.o -c /home/ubuntu/YouShuangExample/chapter6/chapter6.3/src/client.cpp

CMakeFiles/YouShuangExample_6.3_client.dir/src/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/YouShuangExample_6.3_client.dir/src/client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/YouShuangExample/chapter6/chapter6.3/src/client.cpp > CMakeFiles/YouShuangExample_6.3_client.dir/src/client.cpp.i

CMakeFiles/YouShuangExample_6.3_client.dir/src/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/YouShuangExample_6.3_client.dir/src/client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/YouShuangExample/chapter6/chapter6.3/src/client.cpp -o CMakeFiles/YouShuangExample_6.3_client.dir/src/client.cpp.s

# Object files for target YouShuangExample_6.3_client
YouShuangExample_6_3_client_OBJECTS = \
"CMakeFiles/YouShuangExample_6.3_client.dir/src/client.cpp.o"

# External object files for target YouShuangExample_6.3_client
YouShuangExample_6_3_client_EXTERNAL_OBJECTS =

YouShuangExample_6.3_client: CMakeFiles/YouShuangExample_6.3_client.dir/src/client.cpp.o
YouShuangExample_6.3_client: CMakeFiles/YouShuangExample_6.3_client.dir/build.make
YouShuangExample_6.3_client: CMakeFiles/YouShuangExample_6.3_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ubuntu/YouShuangExample/chapter6/chapter6.3/build_test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable YouShuangExample_6.3_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/YouShuangExample_6.3_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/YouShuangExample_6.3_client.dir/build: YouShuangExample_6.3_client
.PHONY : CMakeFiles/YouShuangExample_6.3_client.dir/build

CMakeFiles/YouShuangExample_6.3_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/YouShuangExample_6.3_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/YouShuangExample_6.3_client.dir/clean

CMakeFiles/YouShuangExample_6.3_client.dir/depend:
	cd /home/ubuntu/YouShuangExample/chapter6/chapter6.3/build_test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/YouShuangExample/chapter6/chapter6.3 /home/ubuntu/YouShuangExample/chapter6/chapter6.3 /home/ubuntu/YouShuangExample/chapter6/chapter6.3/build_test /home/ubuntu/YouShuangExample/chapter6/chapter6.3/build_test /home/ubuntu/YouShuangExample/chapter6/chapter6.3/build_test/CMakeFiles/YouShuangExample_6.3_client.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/YouShuangExample_6.3_client.dir/depend

