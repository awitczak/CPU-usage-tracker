# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/awitczak/Desktop/CPU_Usage_Tracker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/awitczak/Desktop/CPU_Usage_Tracker/build

# Include any dependencies generated for this target.
include CMakeFiles/CPU_Usage_Tracker.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CPU_Usage_Tracker.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CPU_Usage_Tracker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CPU_Usage_Tracker.dir/flags.make

CMakeFiles/CPU_Usage_Tracker.dir/src/main.c.o: CMakeFiles/CPU_Usage_Tracker.dir/flags.make
CMakeFiles/CPU_Usage_Tracker.dir/src/main.c.o: /home/awitczak/Desktop/CPU_Usage_Tracker/src/main.c
CMakeFiles/CPU_Usage_Tracker.dir/src/main.c.o: CMakeFiles/CPU_Usage_Tracker.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/awitczak/Desktop/CPU_Usage_Tracker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CPU_Usage_Tracker.dir/src/main.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CPU_Usage_Tracker.dir/src/main.c.o -MF CMakeFiles/CPU_Usage_Tracker.dir/src/main.c.o.d -o CMakeFiles/CPU_Usage_Tracker.dir/src/main.c.o -c /home/awitczak/Desktop/CPU_Usage_Tracker/src/main.c

CMakeFiles/CPU_Usage_Tracker.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CPU_Usage_Tracker.dir/src/main.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/awitczak/Desktop/CPU_Usage_Tracker/src/main.c > CMakeFiles/CPU_Usage_Tracker.dir/src/main.c.i

CMakeFiles/CPU_Usage_Tracker.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CPU_Usage_Tracker.dir/src/main.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/awitczak/Desktop/CPU_Usage_Tracker/src/main.c -o CMakeFiles/CPU_Usage_Tracker.dir/src/main.c.s

CMakeFiles/CPU_Usage_Tracker.dir/src/fileread.c.o: CMakeFiles/CPU_Usage_Tracker.dir/flags.make
CMakeFiles/CPU_Usage_Tracker.dir/src/fileread.c.o: /home/awitczak/Desktop/CPU_Usage_Tracker/src/fileread.c
CMakeFiles/CPU_Usage_Tracker.dir/src/fileread.c.o: CMakeFiles/CPU_Usage_Tracker.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/awitczak/Desktop/CPU_Usage_Tracker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/CPU_Usage_Tracker.dir/src/fileread.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CPU_Usage_Tracker.dir/src/fileread.c.o -MF CMakeFiles/CPU_Usage_Tracker.dir/src/fileread.c.o.d -o CMakeFiles/CPU_Usage_Tracker.dir/src/fileread.c.o -c /home/awitczak/Desktop/CPU_Usage_Tracker/src/fileread.c

CMakeFiles/CPU_Usage_Tracker.dir/src/fileread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CPU_Usage_Tracker.dir/src/fileread.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/awitczak/Desktop/CPU_Usage_Tracker/src/fileread.c > CMakeFiles/CPU_Usage_Tracker.dir/src/fileread.c.i

CMakeFiles/CPU_Usage_Tracker.dir/src/fileread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CPU_Usage_Tracker.dir/src/fileread.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/awitczak/Desktop/CPU_Usage_Tracker/src/fileread.c -o CMakeFiles/CPU_Usage_Tracker.dir/src/fileread.c.s

CMakeFiles/CPU_Usage_Tracker.dir/src/analyzer.c.o: CMakeFiles/CPU_Usage_Tracker.dir/flags.make
CMakeFiles/CPU_Usage_Tracker.dir/src/analyzer.c.o: /home/awitczak/Desktop/CPU_Usage_Tracker/src/analyzer.c
CMakeFiles/CPU_Usage_Tracker.dir/src/analyzer.c.o: CMakeFiles/CPU_Usage_Tracker.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/awitczak/Desktop/CPU_Usage_Tracker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/CPU_Usage_Tracker.dir/src/analyzer.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CPU_Usage_Tracker.dir/src/analyzer.c.o -MF CMakeFiles/CPU_Usage_Tracker.dir/src/analyzer.c.o.d -o CMakeFiles/CPU_Usage_Tracker.dir/src/analyzer.c.o -c /home/awitczak/Desktop/CPU_Usage_Tracker/src/analyzer.c

CMakeFiles/CPU_Usage_Tracker.dir/src/analyzer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CPU_Usage_Tracker.dir/src/analyzer.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/awitczak/Desktop/CPU_Usage_Tracker/src/analyzer.c > CMakeFiles/CPU_Usage_Tracker.dir/src/analyzer.c.i

CMakeFiles/CPU_Usage_Tracker.dir/src/analyzer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CPU_Usage_Tracker.dir/src/analyzer.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/awitczak/Desktop/CPU_Usage_Tracker/src/analyzer.c -o CMakeFiles/CPU_Usage_Tracker.dir/src/analyzer.c.s

CMakeFiles/CPU_Usage_Tracker.dir/src/queue.c.o: CMakeFiles/CPU_Usage_Tracker.dir/flags.make
CMakeFiles/CPU_Usage_Tracker.dir/src/queue.c.o: /home/awitczak/Desktop/CPU_Usage_Tracker/src/queue.c
CMakeFiles/CPU_Usage_Tracker.dir/src/queue.c.o: CMakeFiles/CPU_Usage_Tracker.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/awitczak/Desktop/CPU_Usage_Tracker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/CPU_Usage_Tracker.dir/src/queue.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CPU_Usage_Tracker.dir/src/queue.c.o -MF CMakeFiles/CPU_Usage_Tracker.dir/src/queue.c.o.d -o CMakeFiles/CPU_Usage_Tracker.dir/src/queue.c.o -c /home/awitczak/Desktop/CPU_Usage_Tracker/src/queue.c

CMakeFiles/CPU_Usage_Tracker.dir/src/queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CPU_Usage_Tracker.dir/src/queue.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/awitczak/Desktop/CPU_Usage_Tracker/src/queue.c > CMakeFiles/CPU_Usage_Tracker.dir/src/queue.c.i

CMakeFiles/CPU_Usage_Tracker.dir/src/queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CPU_Usage_Tracker.dir/src/queue.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/awitczak/Desktop/CPU_Usage_Tracker/src/queue.c -o CMakeFiles/CPU_Usage_Tracker.dir/src/queue.c.s

# Object files for target CPU_Usage_Tracker
CPU_Usage_Tracker_OBJECTS = \
"CMakeFiles/CPU_Usage_Tracker.dir/src/main.c.o" \
"CMakeFiles/CPU_Usage_Tracker.dir/src/fileread.c.o" \
"CMakeFiles/CPU_Usage_Tracker.dir/src/analyzer.c.o" \
"CMakeFiles/CPU_Usage_Tracker.dir/src/queue.c.o"

# External object files for target CPU_Usage_Tracker
CPU_Usage_Tracker_EXTERNAL_OBJECTS =

CPU_Usage_Tracker: CMakeFiles/CPU_Usage_Tracker.dir/src/main.c.o
CPU_Usage_Tracker: CMakeFiles/CPU_Usage_Tracker.dir/src/fileread.c.o
CPU_Usage_Tracker: CMakeFiles/CPU_Usage_Tracker.dir/src/analyzer.c.o
CPU_Usage_Tracker: CMakeFiles/CPU_Usage_Tracker.dir/src/queue.c.o
CPU_Usage_Tracker: CMakeFiles/CPU_Usage_Tracker.dir/build.make
CPU_Usage_Tracker: CMakeFiles/CPU_Usage_Tracker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/awitczak/Desktop/CPU_Usage_Tracker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable CPU_Usage_Tracker"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CPU_Usage_Tracker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CPU_Usage_Tracker.dir/build: CPU_Usage_Tracker
.PHONY : CMakeFiles/CPU_Usage_Tracker.dir/build

CMakeFiles/CPU_Usage_Tracker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CPU_Usage_Tracker.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CPU_Usage_Tracker.dir/clean

CMakeFiles/CPU_Usage_Tracker.dir/depend:
	cd /home/awitczak/Desktop/CPU_Usage_Tracker/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/awitczak/Desktop/CPU_Usage_Tracker /home/awitczak/Desktop/CPU_Usage_Tracker /home/awitczak/Desktop/CPU_Usage_Tracker/build /home/awitczak/Desktop/CPU_Usage_Tracker/build /home/awitczak/Desktop/CPU_Usage_Tracker/build/CMakeFiles/CPU_Usage_Tracker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CPU_Usage_Tracker.dir/depend

