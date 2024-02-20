#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libpqxx::pqxx" for configuration "MinSizeRel"
set_property(TARGET libpqxx::pqxx APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(libpqxx::pqxx PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/pqxx.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/pqxx.dll"
  )

list(APPEND _cmake_import_check_targets libpqxx::pqxx )
list(APPEND _cmake_import_check_files_for_libpqxx::pqxx "${_IMPORT_PREFIX}/lib/pqxx.lib" "${_IMPORT_PREFIX}/bin/pqxx.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
