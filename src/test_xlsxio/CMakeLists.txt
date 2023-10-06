#[[
# Author : KeeneChen
# Date   : 2023.10.06-23:16:40
]]

project(test_xlsxio DESCRIPTION "test_xlsxio")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})

function(add_exec BIN_NAME BIN_FILE)
  add_executable(${BIN_NAME} ${BIN_FILE})
  target_link_libraries(${BIN_NAME} PRIVATE ${XLSXIO_READ} ${XLSXIO_WRITE})
endfunction()

add_exec(test_xlsxio_read test_xlsxio_read.c)
add_exec(test_xlsxio_write test_xlsxio_write.c)
