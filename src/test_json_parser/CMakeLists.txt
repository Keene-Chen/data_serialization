#[[
# Author : KeeneChen
# Date   : 2023.10.06-23:15:32
]]

project(test_json_parser DESCRIPTION "test_json_parser")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})

function(add_exec BIN_NAME BIN_FILE)
  add_executable(${BIN_NAME} ${BIN_FILE})
  target_link_libraries(${BIN_NAME} PRIVATE json_parser)
endfunction()

add_exec(test test.c)
