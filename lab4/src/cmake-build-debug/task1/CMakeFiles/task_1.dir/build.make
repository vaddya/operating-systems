# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.10

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.1\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.1\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Git\os\lab4\src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Git\os\lab4\src\cmake-build-debug

# Include any dependencies generated for this target.
include task1/CMakeFiles/task_1.dir/depend.make

# Include the progress variables for this target.
include task1/CMakeFiles/task_1.dir/progress.make

# Include the compile flags for this target's objects.
include task1/CMakeFiles/task_1.dir/flags.make

task1/CMakeFiles/task_1.dir/task1.cpp.obj: task1/CMakeFiles/task_1.dir/flags.make
task1/CMakeFiles/task_1.dir/task1.cpp.obj: ../task1/task1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Git\os\lab4\src\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object task1/CMakeFiles/task_1.dir/task1.cpp.obj"
	cd /d D:\Git\os\lab4\src\cmake-build-debug\task1 && C:\Qt\Tools\mingw530_32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\task_1.dir\task1.cpp.obj -c D:\Git\os\lab4\src\task1\task1.cpp

task1/CMakeFiles/task_1.dir/task1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task_1.dir/task1.cpp.i"
	cd /d D:\Git\os\lab4\src\cmake-build-debug\task1 && C:\Qt\Tools\mingw530_32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Git\os\lab4\src\task1\task1.cpp > CMakeFiles\task_1.dir\task1.cpp.i

task1/CMakeFiles/task_1.dir/task1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task_1.dir/task1.cpp.s"
	cd /d D:\Git\os\lab4\src\cmake-build-debug\task1 && C:\Qt\Tools\mingw530_32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Git\os\lab4\src\task1\task1.cpp -o CMakeFiles\task_1.dir\task1.cpp.s

task1/CMakeFiles/task_1.dir/task1.cpp.obj.requires:

.PHONY : task1/CMakeFiles/task_1.dir/task1.cpp.obj.requires

task1/CMakeFiles/task_1.dir/task1.cpp.obj.provides: task1/CMakeFiles/task_1.dir/task1.cpp.obj.requires
	$(MAKE) -f task1\CMakeFiles\task_1.dir\build.make task1/CMakeFiles/task_1.dir/task1.cpp.obj.provides.build
.PHONY : task1/CMakeFiles/task_1.dir/task1.cpp.obj.provides

task1/CMakeFiles/task_1.dir/task1.cpp.obj.provides.build: task1/CMakeFiles/task_1.dir/task1.cpp.obj


# Object files for target task_1
task_1_OBJECTS = \
"CMakeFiles/task_1.dir/task1.cpp.obj"

# External object files for target task_1
task_1_EXTERNAL_OBJECTS =

task1/task_1.exe: task1/CMakeFiles/task_1.dir/task1.cpp.obj
task1/task_1.exe: task1/CMakeFiles/task_1.dir/build.make
task1/task_1.exe: task1/CMakeFiles/task_1.dir/linklibs.rsp
task1/task_1.exe: task1/CMakeFiles/task_1.dir/objects1.rsp
task1/task_1.exe: task1/CMakeFiles/task_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Git\os\lab4\src\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable task_1.exe"
	cd /d D:\Git\os\lab4\src\cmake-build-debug\task1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\task_1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
task1/CMakeFiles/task_1.dir/build: task1/task_1.exe

.PHONY : task1/CMakeFiles/task_1.dir/build

task1/CMakeFiles/task_1.dir/requires: task1/CMakeFiles/task_1.dir/task1.cpp.obj.requires

.PHONY : task1/CMakeFiles/task_1.dir/requires

task1/CMakeFiles/task_1.dir/clean:
	cd /d D:\Git\os\lab4\src\cmake-build-debug\task1 && $(CMAKE_COMMAND) -P CMakeFiles\task_1.dir\cmake_clean.cmake
.PHONY : task1/CMakeFiles/task_1.dir/clean

task1/CMakeFiles/task_1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Git\os\lab4\src D:\Git\os\lab4\src\task1 D:\Git\os\lab4\src\cmake-build-debug D:\Git\os\lab4\src\cmake-build-debug\task1 D:\Git\os\lab4\src\cmake-build-debug\task1\CMakeFiles\task_1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : task1/CMakeFiles/task_1.dir/depend

