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
include task4/CMakeFiles/task4.dir/depend.make

# Include the progress variables for this target.
include task4/CMakeFiles/task4.dir/progress.make

# Include the compile flags for this target's objects.
include task4/CMakeFiles/task4.dir/flags.make

task4/CMakeFiles/task4.dir/task4.cpp.obj: task4/CMakeFiles/task4.dir/flags.make
task4/CMakeFiles/task4.dir/task4.cpp.obj: ../task4/task4.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Git\os\lab4\src\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object task4/CMakeFiles/task4.dir/task4.cpp.obj"
	cd /d D:\Git\os\lab4\src\cmake-build-debug\task4 && C:\Qt\Tools\mingw530_32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\task4.dir\task4.cpp.obj -c D:\Git\os\lab4\src\task4\task4.cpp

task4/CMakeFiles/task4.dir/task4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task4.dir/task4.cpp.i"
	cd /d D:\Git\os\lab4\src\cmake-build-debug\task4 && C:\Qt\Tools\mingw530_32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Git\os\lab4\src\task4\task4.cpp > CMakeFiles\task4.dir\task4.cpp.i

task4/CMakeFiles/task4.dir/task4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task4.dir/task4.cpp.s"
	cd /d D:\Git\os\lab4\src\cmake-build-debug\task4 && C:\Qt\Tools\mingw530_32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Git\os\lab4\src\task4\task4.cpp -o CMakeFiles\task4.dir\task4.cpp.s

task4/CMakeFiles/task4.dir/task4.cpp.obj.requires:

.PHONY : task4/CMakeFiles/task4.dir/task4.cpp.obj.requires

task4/CMakeFiles/task4.dir/task4.cpp.obj.provides: task4/CMakeFiles/task4.dir/task4.cpp.obj.requires
	$(MAKE) -f task4\CMakeFiles\task4.dir\build.make task4/CMakeFiles/task4.dir/task4.cpp.obj.provides.build
.PHONY : task4/CMakeFiles/task4.dir/task4.cpp.obj.provides

task4/CMakeFiles/task4.dir/task4.cpp.obj.provides.build: task4/CMakeFiles/task4.dir/task4.cpp.obj


# Object files for target task4
task4_OBJECTS = \
"CMakeFiles/task4.dir/task4.cpp.obj"

# External object files for target task4
task4_EXTERNAL_OBJECTS =

task4/task4.exe: task4/CMakeFiles/task4.dir/task4.cpp.obj
task4/task4.exe: task4/CMakeFiles/task4.dir/build.make
task4/task4.exe: task4/CMakeFiles/task4.dir/linklibs.rsp
task4/task4.exe: task4/CMakeFiles/task4.dir/objects1.rsp
task4/task4.exe: task4/CMakeFiles/task4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Git\os\lab4\src\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable task4.exe"
	cd /d D:\Git\os\lab4\src\cmake-build-debug\task4 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\task4.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
task4/CMakeFiles/task4.dir/build: task4/task4.exe

.PHONY : task4/CMakeFiles/task4.dir/build

task4/CMakeFiles/task4.dir/requires: task4/CMakeFiles/task4.dir/task4.cpp.obj.requires

.PHONY : task4/CMakeFiles/task4.dir/requires

task4/CMakeFiles/task4.dir/clean:
	cd /d D:\Git\os\lab4\src\cmake-build-debug\task4 && $(CMAKE_COMMAND) -P CMakeFiles\task4.dir\cmake_clean.cmake
.PHONY : task4/CMakeFiles/task4.dir/clean

task4/CMakeFiles/task4.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Git\os\lab4\src D:\Git\os\lab4\src\task4 D:\Git\os\lab4\src\cmake-build-debug D:\Git\os\lab4\src\cmake-build-debug\task4 D:\Git\os\lab4\src\cmake-build-debug\task4\CMakeFiles\task4.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : task4/CMakeFiles/task4.dir/depend

