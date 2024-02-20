cmake_minimum_required(VERSION 3.18)
project(chat_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set (LIBVERSION "7.8.1")

# (First set LIBVERSION to the libpqxx version you have.)
set(libpqxxdir "libpqxx")

# You can usually skip building the tests.
set(SKIP_BUILD_TEST ON)

# On Windows we generally recommend building libpqxx as a shared
# library.  On other platforms, we recommend a static library.
IF (WIN32)
    set(BUILD_SHARED_LIBS ON)
ELSE()
    set(BUILD_SHARED_LIBS OFF)
ENDIF()

add_subdirectory(${libpqxxdir})

#list(APPEND CMAKE_PREFIX_PATH "libpqxx/cmake/")

add_executable(ClientServer ClientServerApp.cpp)

find_package(libpqxx REQUIRED)
target_link_libraries(ClientServer PRIVATE pqxx)
