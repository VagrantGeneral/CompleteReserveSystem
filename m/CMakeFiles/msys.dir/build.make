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
CMAKE_SOURCE_DIR = /home/hankangkai/Project2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hankangkai/Project2/m

# Include any dependencies generated for this target.
include CMakeFiles/msys.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/msys.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/msys.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/msys.dir/flags.make

CMakeFiles/msys.dir/m_text.cpp.o: CMakeFiles/msys.dir/flags.make
CMakeFiles/msys.dir/m_text.cpp.o: ../m_text.cpp
CMakeFiles/msys.dir/m_text.cpp.o: CMakeFiles/msys.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hankangkai/Project2/m/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/msys.dir/m_text.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/msys.dir/m_text.cpp.o -MF CMakeFiles/msys.dir/m_text.cpp.o.d -o CMakeFiles/msys.dir/m_text.cpp.o -c /home/hankangkai/Project2/m_text.cpp

CMakeFiles/msys.dir/m_text.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/msys.dir/m_text.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hankangkai/Project2/m_text.cpp > CMakeFiles/msys.dir/m_text.cpp.i

CMakeFiles/msys.dir/m_text.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/msys.dir/m_text.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hankangkai/Project2/m_text.cpp -o CMakeFiles/msys.dir/m_text.cpp.s

# Object files for target msys
msys_OBJECTS = \
"CMakeFiles/msys.dir/m_text.cpp.o"

# External object files for target msys
msys_EXTERNAL_OBJECTS =

msys: CMakeFiles/msys.dir/m_text.cpp.o
msys: CMakeFiles/msys.dir/build.make
msys: CMakeFiles/msys.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hankangkai/Project2/m/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable msys"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/msys.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/msys.dir/build: msys
.PHONY : CMakeFiles/msys.dir/build

CMakeFiles/msys.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/msys.dir/cmake_clean.cmake
.PHONY : CMakeFiles/msys.dir/clean

CMakeFiles/msys.dir/depend:
	cd /home/hankangkai/Project2/m && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hankangkai/Project2 /home/hankangkai/Project2 /home/hankangkai/Project2/m /home/hankangkai/Project2/m /home/hankangkai/Project2/m/CMakeFiles/msys.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/msys.dir/depend

