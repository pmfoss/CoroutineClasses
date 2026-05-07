cmake_minimum_required(VERSION 3.15)

project(
  CoroutineClasses
  VERSION 1.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

option(COROUTINECLASSES_PKGCONFIG "Build pkg-config .pc file for CoroutineClasses" OFF)
option(COROUTINECLASSES_EXAMPLES "Build examples for CoroutineClasses" OFF)

set(INCLUDE_INSTALL_DIR
      "${CMAKE_INSTALL_INCLUDEDIR}/CoroutineClasses"
	  CACHE PATH "The directory relative to CMAKE_INSTALL_PREFIX where CoroutineClasses header files are installed")


set(PKGCONFIG_INSTALL_DIR
    "${CMAKE_INSTALL_DATADIR}/pkgconfig"
    CACHE PATH "The directory relative to CMAKE_INSTALL_PREFIX where coroutineclasses.pc is installed"
   )

foreach(var INCLUDE_INSTALL_DIR CMAKEPACKAGE_INSTALL_DIR PKGCONFIG_INSTALL_DIR)
  # If an absolute path is specified, make it relative to "{CMAKE_INSTALL_PREFIX}".
  if(IS_ABSOLUTE "${${var}}")
    file(RELATIVE_PATH "${var}" "${CMAKE_INSTALL_PREFIX}" "${${var}}")
  endif()
endforeach()

add_subdirectory(sources)

if(COROUTINECLASSES_EXAMPLES)
    include_directories(sources)
    add_subdirectory(examples)
endif()

if(COROUTINECLASSES_PKGCONFIG)
    configure_file(coroutineclasses.pc.in coroutineclasses.pc @ONLY)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/coroutineclasses.pc
        DESTINATION ${PKGCONFIG_INSTALL_DIR})
endif()