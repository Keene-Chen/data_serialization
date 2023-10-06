#[[
# Author : KeeneChen
# Date   : 2023.10.06-23:16:51
]]

project(test_yyjson DESCRIPTION "test_yyjson")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})

function(add_exec BIN_NAME BIN_FILE)
  add_executable(${BIN_NAME} ${BIN_FILE})
  target_link_libraries(${BIN_NAME} PRIVATE yyjson)
endfunction()

add_exec(test_yyjson test_yyjson.c)
add_exec(test_read test_read.c)
add_exec(test_write test_write.c)
