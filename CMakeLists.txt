#
# Copyright 2017 Antonio Coratelli - All Rights Reserved
# You may use, distribute and modify this code under the
# terms of the BSD 3-Clause license.
#
cmake_minimum_required(VERSION 3.2.2)
project(StateMachine)

add_compile_options(-std=c++14)
add_compile_options(-pthread)
add_compile_options(-Werror=return-type)
add_compile_options(-Werror=format)
add_compile_options(-Werror=parentheses)
add_compile_options(-Werror=reorder)
add_compile_options(-Wall)
add_compile_options(-Wextra)

include_directories("include")

set(STATEMACHINE_EXTERNAL_GTEST "${CMAKE_CURRENT_LIST_DIR}/external/googletest-1.8.0")
include_directories("${STATEMACHINE_EXTERNAL_GTEST}" "${STATEMACHINE_EXTERNAL_GTEST}/include")
file(GLOB_RECURSE STATEMACHINE_TESTS "${CMAKE_CURRENT_LIST_DIR}/examples/*.cpp")
add_executable(unit_tests "${STATEMACHINE_EXTERNAL_GTEST}/src/gtest-all.cc" "${STATEMACHINE_TESTS}")
target_link_libraries(unit_tests pthread)
add_custom_command(TARGET unit_tests POST_BUILD COMMAND unit_tests)
