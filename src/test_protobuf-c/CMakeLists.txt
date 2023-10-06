#[[
# Author : KeeneChen
# Date   : 2023.10.06-23:30:21
]]

project(test_protobuf-c DESCRIPTION "test_protobuf-c")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})

include_directories(${CMAKE_SOURCE_DIR}/res/protobuf)
add_executable(test_protobuf-c test_protobuf-c.c
                               ${CMAKE_SOURCE_DIR}/res/protobuf/student.pb-c.c)
target_link_libraries(test_protobuf-c ${protobuf-c})
