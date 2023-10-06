#[[
# Author : KeeneChen
# Date   : 2023.10.06-23:15:11
]]

project(test_inih DESCRIPTION "test_inih")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})

function(add_exec BIN_NAME BIN_FILE)
  add_executable(${BIN_NAME} ${BIN_FILE})
  target_link_libraries(${BIN_NAME} PRIVATE inih)
endfunction()

add_exec(test_inih test_inih.c)
