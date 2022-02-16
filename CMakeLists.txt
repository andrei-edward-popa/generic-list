cmake_minimum_required(VERSION 3.20)
project(GenericList)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_STANDARD 23)

set(CMAKE_C_FLAGS
"-Ofast -Wall -Wextra -Wpedantic -Werror -Wchar-subscripts \
-Wformat -Wnull-dereference -Winfinite-recursion -Wimplicit"
)

include_directories(include/list)
include_directories(unit-tests)

add_executable(test
        include/list/linked_list.h
        unit-tests/u32.h
        unit-tests/f64.h
        unit-tests/charptr.h
        unit-tests/struct_pair.h
        unit-tests/list_f80.h
        unit-tests/main.c
)

target_link_libraries(test cunit)
