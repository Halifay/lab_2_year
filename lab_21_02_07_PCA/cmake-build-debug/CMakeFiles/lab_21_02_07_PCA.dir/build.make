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
CMAKE_SOURCE_DIR = /home/mikhail/Garage/C++/lab_21_02_07_PCA

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mikhail/Garage/C++/lab_21_02_07_PCA/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lab_21_02_07_PCA.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab_21_02_07_PCA.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab_21_02_07_PCA.dir/flags.make

CMakeFiles/lab_21_02_07_PCA.dir/main.cpp.o: CMakeFiles/lab_21_02_07_PCA.dir/flags.make
CMakeFiles/lab_21_02_07_PCA.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mikhail/Garage/C++/lab_21_02_07_PCA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab_21_02_07_PCA.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab_21_02_07_PCA.dir/main.cpp.o -c /home/mikhail/Garage/C++/lab_21_02_07_PCA/main.cpp

CMakeFiles/lab_21_02_07_PCA.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab_21_02_07_PCA.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mikhail/Garage/C++/lab_21_02_07_PCA/main.cpp > CMakeFiles/lab_21_02_07_PCA.dir/main.cpp.i

CMakeFiles/lab_21_02_07_PCA.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab_21_02_07_PCA.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mikhail/Garage/C++/lab_21_02_07_PCA/main.cpp -o CMakeFiles/lab_21_02_07_PCA.dir/main.cpp.s

CMakeFiles/lab_21_02_07_PCA.dir/matrix.cpp.o: CMakeFiles/lab_21_02_07_PCA.dir/flags.make
CMakeFiles/lab_21_02_07_PCA.dir/matrix.cpp.o: ../matrix.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mikhail/Garage/C++/lab_21_02_07_PCA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/lab_21_02_07_PCA.dir/matrix.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab_21_02_07_PCA.dir/matrix.cpp.o -c /home/mikhail/Garage/C++/lab_21_02_07_PCA/matrix.cpp

CMakeFiles/lab_21_02_07_PCA.dir/matrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab_21_02_07_PCA.dir/matrix.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mikhail/Garage/C++/lab_21_02_07_PCA/matrix.cpp > CMakeFiles/lab_21_02_07_PCA.dir/matrix.cpp.i

CMakeFiles/lab_21_02_07_PCA.dir/matrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab_21_02_07_PCA.dir/matrix.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mikhail/Garage/C++/lab_21_02_07_PCA/matrix.cpp -o CMakeFiles/lab_21_02_07_PCA.dir/matrix.cpp.s

CMakeFiles/lab_21_02_07_PCA.dir/PCA.cpp.o: CMakeFiles/lab_21_02_07_PCA.dir/flags.make
CMakeFiles/lab_21_02_07_PCA.dir/PCA.cpp.o: ../PCA.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mikhail/Garage/C++/lab_21_02_07_PCA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/lab_21_02_07_PCA.dir/PCA.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab_21_02_07_PCA.dir/PCA.cpp.o -c /home/mikhail/Garage/C++/lab_21_02_07_PCA/PCA.cpp

CMakeFiles/lab_21_02_07_PCA.dir/PCA.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab_21_02_07_PCA.dir/PCA.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mikhail/Garage/C++/lab_21_02_07_PCA/PCA.cpp > CMakeFiles/lab_21_02_07_PCA.dir/PCA.cpp.i

CMakeFiles/lab_21_02_07_PCA.dir/PCA.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab_21_02_07_PCA.dir/PCA.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mikhail/Garage/C++/lab_21_02_07_PCA/PCA.cpp -o CMakeFiles/lab_21_02_07_PCA.dir/PCA.cpp.s

# Object files for target lab_21_02_07_PCA
lab_21_02_07_PCA_OBJECTS = \
"CMakeFiles/lab_21_02_07_PCA.dir/main.cpp.o" \
"CMakeFiles/lab_21_02_07_PCA.dir/matrix.cpp.o" \
"CMakeFiles/lab_21_02_07_PCA.dir/PCA.cpp.o"

# External object files for target lab_21_02_07_PCA
lab_21_02_07_PCA_EXTERNAL_OBJECTS =

lab_21_02_07_PCA: CMakeFiles/lab_21_02_07_PCA.dir/main.cpp.o
lab_21_02_07_PCA: CMakeFiles/lab_21_02_07_PCA.dir/matrix.cpp.o
lab_21_02_07_PCA: CMakeFiles/lab_21_02_07_PCA.dir/PCA.cpp.o
lab_21_02_07_PCA: CMakeFiles/lab_21_02_07_PCA.dir/build.make
lab_21_02_07_PCA: CMakeFiles/lab_21_02_07_PCA.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mikhail/Garage/C++/lab_21_02_07_PCA/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable lab_21_02_07_PCA"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab_21_02_07_PCA.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab_21_02_07_PCA.dir/build: lab_21_02_07_PCA

.PHONY : CMakeFiles/lab_21_02_07_PCA.dir/build

CMakeFiles/lab_21_02_07_PCA.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab_21_02_07_PCA.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab_21_02_07_PCA.dir/clean

CMakeFiles/lab_21_02_07_PCA.dir/depend:
	cd /home/mikhail/Garage/C++/lab_21_02_07_PCA/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mikhail/Garage/C++/lab_21_02_07_PCA /home/mikhail/Garage/C++/lab_21_02_07_PCA /home/mikhail/Garage/C++/lab_21_02_07_PCA/cmake-build-debug /home/mikhail/Garage/C++/lab_21_02_07_PCA/cmake-build-debug /home/mikhail/Garage/C++/lab_21_02_07_PCA/cmake-build-debug/CMakeFiles/lab_21_02_07_PCA.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab_21_02_07_PCA.dir/depend
