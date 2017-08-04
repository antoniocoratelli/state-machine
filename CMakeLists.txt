cmake_minimum_required(VERSION 2.8)
project(StateMachine)

include_directories("include")

add_executable(${PROJECT_NAME} "src/main.cpp")


## Dummy target to show all files in QtCreator
##
file(GLOB_RECURSE GLOB_STATEMACHINE_INCLUDES "include/*.h")
file(GLOB_RECURSE GLOB_STATEMACHINE_SOURCES "src/*.cc")
message(STATUS ${GLOB_STATEMACHINE_INCLUDES})
message(STATUS ${GLOB_STATEMACHINE_SOURCES})
add_custom_target(GLOB_DUMMY
    ${GLOB_STATEMACHINE_INCLUDES}
    ${GLOB_STATEMACHINE_SOURCES}
)
