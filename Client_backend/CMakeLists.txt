include(FetchContent)

cmake_minimum_required(VERSION 3.18)
project(chat_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

FetchContent_Declare(
  libpqxx
  GIT_REPOSITORY https://github.com/jtv/libpqxx.git
  GIT_TAG a6b1d60e74c1427c8ac2324b85cd4a0dc2068332
)
set(PQXX_LIBRARIES pqxx_static)

FetchContent_MakeAvailable(libpqxx)

add_executable(OnlyClientSide OnlyClientSide.cpp)

target_link_libraries(OnlyClientSide "${PQXX_LIBRARIES}")
