# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /snap/clion/121/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/121/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mikhail/Garage/C++/lab2_1C++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mikhail/Garage/C++/lab2_1C++/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lab2_1C__.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab2_1C__.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab2_1C__.dir/flags.make

CMakeFiles/lab2_1C__.dir/main.cpp.o: CMakeFiles/lab2_1C__.dir/flags.make
CMakeFiles/lab2_1C__.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mikhail/Garage/C++/lab2_1C++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab2_1C__.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab2_1C__.dir/main.cpp.o -c /home/mikhail/Garage/C++/lab2_1C++/main.cpp

CMakeFiles/lab2_1C__.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab2_1C__.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mikhail/Garage/C++/lab2_1C++/main.cpp > CMakeFiles/lab2_1C__.dir/main.cpp.i

CMakeFiles/lab2_1C__.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab2_1C__.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mikhail/Garage/C++/lab2_1C++/main.cpp -o CMakeFiles/lab2_1C__.dir/main.cpp.s

CMakeFiles/lab2_1C__.dir/matrix.cpp.o: CMakeFiles/lab2_1C__.dir/flags.make
CMakeFiles/lab2_1C__.dir/matrix.cpp.o: ../matrix.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mikhail/Garage/C++/lab2_1C++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/lab2_1C__.dir/matrix.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab2_1C__.dir/matrix.cpp.o -c /home/mikhail/Garage/C++/lab2_1C++/matrix.cpp

CMakeFiles/lab2_1C__.dir/matrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab2_1C__.dir/matrix.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mikhail/Garage/C++/lab2_1C++/matrix.cpp > CMakeFiles/lab2_1C__.dir/matrix.cpp.i

CMakeFiles/lab2_1C__.dir/matrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab2_1C__.dir/matrix.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mikhail/Garage/C++/lab2_1C++/matrix.cpp -o CMakeFiles/lab2_1C__.dir/matrix.cpp.s

# Object files for target lab2_1C__
lab2_1C___OBJECTS = \
"CMakeFiles/lab2_1C__.dir/main.cpp.o" \
"CMakeFiles/lab2_1C__.dir/matrix.cpp.o"

# External object files for target lab2_1C__
lab2_1C___EXTERNAL_OBJECTS =

lab2_1C__: CMakeFiles/lab2_1C__.dir/main.cpp.o
lab2_1C__: CMakeFiles/lab2_1C__.dir/matrix.cpp.o
lab2_1C__: CMakeFiles/lab2_1C__.dir/build.make
lab2_1C__: CMakeFiles/lab2_1C__.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mikhail/Garage/C++/lab2_1C++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable lab2_1C__"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab2_1C__.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab2_1C__.dir/build: lab2_1C__

.PHONY : CMakeFiles/lab2_1C__.dir/build

CMakeFiles/lab2_1C__.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab2_1C__.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab2_1C__.dir/clean

CMakeFiles/lab2_1C__.dir/depend:
	cd /home/mikhail/Garage/C++/lab2_1C++/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mikhail/Garage/C++/lab2_1C++ /home/mikhail/Garage/C++/lab2_1C++ /home/mikhail/Garage/C++/lab2_1C++/cmake-build-debug /home/mikhail/Garage/C++/lab2_1C++/cmake-build-debug /home/mikhail/Garage/C++/lab2_1C++/cmake-build-debug/CMakeFiles/lab2_1C__.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab2_1C__.dir/depend

