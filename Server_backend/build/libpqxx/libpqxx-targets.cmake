# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.8)
   message(FATAL_ERROR "CMake >= 2.8.0 required")
endif()
if(CMAKE_VERSION VERSION_LESS "2.8.3")
   message(FATAL_ERROR "CMake >= 2.8.3 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.8.3...3.26)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_cmake_targets_defined "")
set(_cmake_targets_not_defined "")
set(_cmake_expected_targets "")
foreach(_cmake_expected_target IN ITEMS libpqxx::pqxx)
  list(APPEND _cmake_expected_targets "${_cmake_expected_target}")
  if(TARGET "${_cmake_expected_target}")
    list(APPEND _cmake_targets_defined "${_cmake_expected_target}")
  else()
    list(APPEND _cmake_targets_not_defined "${_cmake_expected_target}")
  endif()
endforeach()
unset(_cmake_expected_target)
if(_cmake_targets_defined STREQUAL _cmake_expected_targets)
  unset(_cmake_targets_defined)
  unset(_cmake_targets_not_defined)
  unset(_cmake_expected_targets)
  unset(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT _cmake_targets_defined STREQUAL "")
  string(REPLACE ";" ", " _cmake_targets_defined_text "${_cmake_targets_defined}")
  string(REPLACE ";" ", " _cmake_targets_not_defined_text "${_cmake_targets_not_defined}")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_cmake_targets_defined_text}\nTargets not yet defined: ${_cmake_targets_not_defined_text}\n")
endif()
unset(_cmake_targets_defined)
unset(_cmake_targets_not_defined)
unset(_cmake_expected_targets)


# Create imported target libpqxx::pqxx
add_library(libpqxx::pqxx SHARED IMPORTED)

set_target_properties(libpqxx::pqxx PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "PQXX_SHARED"
  INTERFACE_INCLUDE_DIRECTORIES "C:/Users/79085/source/repos/Messanger_project/Server_backend/build/libpqxx/include;C:/Users/79085/source/repos/Messanger_project/Server_backend/libpqxx/include"
  INTERFACE_LINK_LIBRARIES "wsock32;ws2_32"
)

# Import target "libpqxx::pqxx" for configuration "Debug"
set_property(TARGET libpqxx::pqxx APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libpqxx::pqxx PROPERTIES
  IMPORTED_IMPLIB_DEBUG "C:/Users/79085/source/repos/Messanger_project/Server_backend/build/libpqxx/src/Debug/pqxx.lib"
  IMPORTED_LOCATION_DEBUG "C:/Users/79085/source/repos/Messanger_project/Server_backend/build/libpqxx/src/Debug/pqxx.dll"
  )

# Import target "libpqxx::pqxx" for configuration "Release"
set_property(TARGET libpqxx::pqxx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libpqxx::pqxx PROPERTIES
  IMPORTED_IMPLIB_RELEASE "C:/Users/79085/source/repos/Messanger_project/Server_backend/build/libpqxx/src/Release/pqxx.lib"
  IMPORTED_LOCATION_RELEASE "C:/Users/79085/source/repos/Messanger_project/Server_backend/build/libpqxx/src/Release/pqxx.dll"
  )

# Import target "libpqxx::pqxx" for configuration "MinSizeRel"
set_property(TARGET libpqxx::pqxx APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(libpqxx::pqxx PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "C:/Users/79085/source/repos/Messanger_project/Server_backend/build/libpqxx/src/MinSizeRel/pqxx.lib"
  IMPORTED_LOCATION_MINSIZEREL "C:/Users/79085/source/repos/Messanger_project/Server_backend/build/libpqxx/src/MinSizeRel/pqxx.dll"
  )

# Import target "libpqxx::pqxx" for configuration "RelWithDebInfo"
set_property(TARGET libpqxx::pqxx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(libpqxx::pqxx PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "C:/Users/79085/source/repos/Messanger_project/Server_backend/build/libpqxx/src/RelWithDebInfo/pqxx.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "C:/Users/79085/source/repos/Messanger_project/Server_backend/build/libpqxx/src/RelWithDebInfo/pqxx.dll"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)