# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-src"
  "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-build"
  "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-subbuild/libpqxx-populate-prefix"
  "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-subbuild/libpqxx-populate-prefix/tmp"
  "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-subbuild/libpqxx-populate-prefix/src/libpqxx-populate-stamp"
  "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-subbuild/libpqxx-populate-prefix/src"
  "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-subbuild/libpqxx-populate-prefix/src/libpqxx-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-subbuild/libpqxx-populate-prefix/src/libpqxx-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-subbuild/libpqxx-populate-prefix/src/libpqxx-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
