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
CMAKE_COMMAND = /snap/clion/129/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/129/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/OS/practice3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/OS/practice3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/practice3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/practice3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/practice3.dir/flags.make

CMakeFiles/practice3.dir/main.cpp.o: CMakeFiles/practice3.dir/flags.make
CMakeFiles/practice3.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/OS/practice3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/practice3.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/practice3.dir/main.cpp.o -c /home/user/OS/practice3/main.cpp

CMakeFiles/practice3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/practice3.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/OS/practice3/main.cpp > CMakeFiles/practice3.dir/main.cpp.i

CMakeFiles/practice3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/practice3.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/OS/practice3/main.cpp -o CMakeFiles/practice3.dir/main.cpp.s

# Object files for target practice3
practice3_OBJECTS = \
"CMakeFiles/practice3.dir/main.cpp.o"

# External object files for target practice3
practice3_EXTERNAL_OBJECTS =

practice3: CMakeFiles/practice3.dir/main.cpp.o
practice3: CMakeFiles/practice3.dir/build.make
practice3: CMakeFiles/practice3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/OS/practice3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable practice3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/practice3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/practice3.dir/build: practice3

.PHONY : CMakeFiles/practice3.dir/build

CMakeFiles/practice3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/practice3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/practice3.dir/clean

CMakeFiles/practice3.dir/depend:
	cd /home/user/OS/practice3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/OS/practice3 /home/user/OS/practice3 /home/user/OS/practice3/cmake-build-debug /home/user/OS/practice3/cmake-build-debug /home/user/OS/practice3/cmake-build-debug/CMakeFiles/practice3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/practice3.dir/depend

