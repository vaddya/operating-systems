# Install script for directory: D:/Git/os/lab4/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/src")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/Git/os/lab4/src/cmake-build-debug/task1/cmake_install.cmake")
  include("D:/Git/os/lab4/src/cmake-build-debug/task2/cmake_install.cmake")
  include("D:/Git/os/lab4/src/cmake-build-debug/task3/cmake_install.cmake")
  include("D:/Git/os/lab4/src/cmake-build-debug/task4/cmake_install.cmake")
  include("D:/Git/os/lab4/src/cmake-build-debug/task5/cmake_install.cmake")
  include("D:/Git/os/lab4/src/cmake-build-debug/task6/cmake_install.cmake")
  include("D:/Git/os/lab4/src/cmake-build-debug/task7/cmake_install.cmake")
  include("D:/Git/os/lab4/src/cmake-build-debug/task8/cmake_install.cmake")
  include("D:/Git/os/lab4/src/cmake-build-debug/task9/cmake_install.cmake")
  include("D:/Git/os/lab4/src/cmake-build-debug/parent_son/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/Git/os/lab4/src/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
