# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\lolo1\Desktop\STUDIA\INFA\drive_tsp\tsp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\lolo1\Desktop\STUDIA\INFA\drive_tsp\tsp\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/tsp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tsp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tsp.dir/flags.make

CMakeFiles/tsp.dir/tsp.cpp.obj: CMakeFiles/tsp.dir/flags.make
CMakeFiles/tsp.dir/tsp.cpp.obj: ../tsp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\lolo1\Desktop\STUDIA\INFA\drive_tsp\tsp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tsp.dir/tsp.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\tsp.dir\tsp.cpp.obj -c C:\Users\lolo1\Desktop\STUDIA\INFA\drive_tsp\tsp\tsp.cpp

CMakeFiles/tsp.dir/tsp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tsp.dir/tsp.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\lolo1\Desktop\STUDIA\INFA\drive_tsp\tsp\tsp.cpp > CMakeFiles\tsp.dir\tsp.cpp.i

CMakeFiles/tsp.dir/tsp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tsp.dir/tsp.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\lolo1\Desktop\STUDIA\INFA\drive_tsp\tsp\tsp.cpp -o CMakeFiles\tsp.dir\tsp.cpp.s

# Object files for target tsp
tsp_OBJECTS = \
"CMakeFiles/tsp.dir/tsp.cpp.obj"

# External object files for target tsp
tsp_EXTERNAL_OBJECTS =

tsp.exe: CMakeFiles/tsp.dir/tsp.cpp.obj
tsp.exe: CMakeFiles/tsp.dir/build.make
tsp.exe: CMakeFiles/tsp.dir/linklibs.rsp
tsp.exe: CMakeFiles/tsp.dir/objects1.rsp
tsp.exe: CMakeFiles/tsp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\lolo1\Desktop\STUDIA\INFA\drive_tsp\tsp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tsp.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\tsp.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tsp.dir/build: tsp.exe

.PHONY : CMakeFiles/tsp.dir/build

CMakeFiles/tsp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\tsp.dir\cmake_clean.cmake
.PHONY : CMakeFiles/tsp.dir/clean

CMakeFiles/tsp.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\lolo1\Desktop\STUDIA\INFA\drive_tsp\tsp C:\Users\lolo1\Desktop\STUDIA\INFA\drive_tsp\tsp C:\Users\lolo1\Desktop\STUDIA\INFA\drive_tsp\tsp\cmake-build-debug C:\Users\lolo1\Desktop\STUDIA\INFA\drive_tsp\tsp\cmake-build-debug C:\Users\lolo1\Desktop\STUDIA\INFA\drive_tsp\tsp\cmake-build-debug\CMakeFiles\tsp.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tsp.dir/depend

