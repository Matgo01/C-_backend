cmake_minimum_required(VERSION 3.10)

project(My_c++_backend VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE__CXX_STANDARD_REQUIRED True)

include_directories(/usr/include/mysql /usr/local/include/crow)

set(SOURCES
   main.cpp
   database.cpp
   user.cpp
   usercontroller.cpp)

add_executable(My_C++_backend ${SOURCES})

target_link_libraries(My_c++_backend
   crow
   mysqlcppcon
   pthread
   )

install(TARGETS My_c++_backend DESTINATION bin)