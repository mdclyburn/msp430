cmake_minimum_required(VERSION 2.8.11)

#set(CMAKE_VERBOSE_MAKEFILE TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# === add_sources
# Add a list of source files to the final executable build.
# SOURCES - list of source files to add
macro(add_sources SOURCES)
  foreach(src_file ${SOURCES})
	if(MSP430_SOURCES)
	  set(full_path "${CMAKE_CURRENT_SOURCE_DIR}/${src_file}")
	  list(APPEND MSP430_SOURCES ${full_path})
	  set(MSP430_SOURCES ${MSP430_SOURCES} PARENT_SCOPE)
	else()
	  set(MSP430_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${src_file}")
	  set(MSP430_SOURCES ${MSP430_SOURCES} PARENT_SCOPE)
	endif()
  endforeach()
endmacro()

set(MSP430_SOURCES
  digital-io.cpp
  watchdog.cpp)

add_library(mdlmsp430 STATIC ${MSP430_SOURCES})
