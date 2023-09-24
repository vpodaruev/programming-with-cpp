cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")

set(LIB_DIR "./lib")

include_directories(
    ${LIB_DIR}
)

add_subdirectory(07/calculator)
