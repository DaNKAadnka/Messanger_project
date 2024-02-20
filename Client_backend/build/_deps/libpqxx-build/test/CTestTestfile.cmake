# CMake generated Testfile for 
# Source directory: C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-src/test
# Build directory: C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(runner "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-build/test/Debug/runner.exe")
  set_tests_properties(runner PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-src/test/CMakeLists.txt;93;add_test;C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-src/test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(runner "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-build/test/Release/runner.exe")
  set_tests_properties(runner PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-src/test/CMakeLists.txt;93;add_test;C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-src/test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(runner "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-build/test/MinSizeRel/runner.exe")
  set_tests_properties(runner PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-src/test/CMakeLists.txt;93;add_test;C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-src/test/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(runner "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-build/test/RelWithDebInfo/runner.exe")
  set_tests_properties(runner PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-src/test/CMakeLists.txt;93;add_test;C:/Users/79085/source/repos/Messanger_project/Client_backend/build/_deps/libpqxx-src/test/CMakeLists.txt;0;")
else()
  add_test(runner NOT_AVAILABLE)
endif()
subdirs("unit")
