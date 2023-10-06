#[[
# Author : KeeneChen
# Date   : 2023.10.06-23:15:40
]]

project(test_libxl DESCRIPTION "test_libxl")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})

function(add_exec BIN_NAME BIN_FILE)
  add_executable(${BIN_NAME} ${BIN_FILE})
  target_link_libraries(${BIN_NAME} PRIVATE ${LIBXL})
endfunction()

add_exec(test_xl_read test_xl_read.c)
add_exec(test_xl_write test_xl_write.c)
