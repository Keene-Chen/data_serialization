#[[
# Author : KeeneChen
# Date   : 2023.10.06-23:16:03
]]

project(test_libyaml DESCRIPTION "test_libyaml")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})

function(add_exec BIN_NAME BIN_FILE)
  add_executable(${BIN_NAME} ${BIN_FILE})
  target_link_libraries(${BIN_NAME} PRIVATE yaml)
endfunction()

add_exec(test_libyaml test_libyaml.c)
