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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/khurshudov/Desktop/MADE/Algo/HW19

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/khurshudov/Desktop/MADE/Algo/HW19/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HW19.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HW19.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HW19.dir/flags.make

CMakeFiles/HW19.dir/main.cpp.o: CMakeFiles/HW19.dir/flags.make
CMakeFiles/HW19.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/khurshudov/Desktop/MADE/Algo/HW19/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HW19.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HW19.dir/main.cpp.o -c /Users/khurshudov/Desktop/MADE/Algo/HW19/main.cpp

CMakeFiles/HW19.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW19.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/khurshudov/Desktop/MADE/Algo/HW19/main.cpp > CMakeFiles/HW19.dir/main.cpp.i

CMakeFiles/HW19.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW19.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/khurshudov/Desktop/MADE/Algo/HW19/main.cpp -o CMakeFiles/HW19.dir/main.cpp.s

# Object files for target HW19
HW19_OBJECTS = \
"CMakeFiles/HW19.dir/main.cpp.o"

# External object files for target HW19
HW19_EXTERNAL_OBJECTS =

HW19: CMakeFiles/HW19.dir/main.cpp.o
HW19: CMakeFiles/HW19.dir/build.make
HW19: CMakeFiles/HW19.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/khurshudov/Desktop/MADE/Algo/HW19/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HW19"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HW19.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HW19.dir/build: HW19

.PHONY : CMakeFiles/HW19.dir/build

CMakeFiles/HW19.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HW19.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HW19.dir/clean

CMakeFiles/HW19.dir/depend:
	cd /Users/khurshudov/Desktop/MADE/Algo/HW19/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/khurshudov/Desktop/MADE/Algo/HW19 /Users/khurshudov/Desktop/MADE/Algo/HW19 /Users/khurshudov/Desktop/MADE/Algo/HW19/cmake-build-debug /Users/khurshudov/Desktop/MADE/Algo/HW19/cmake-build-debug /Users/khurshudov/Desktop/MADE/Algo/HW19/cmake-build-debug/CMakeFiles/HW19.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HW19.dir/depend

