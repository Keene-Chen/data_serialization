#[[
# Author : KeeneChen
# Date   : 2023.10.06-23:15:54
]]

project(test_libxml2 DESCRIPTION "test_libxml2")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})

include_directories(/usr/include/libxml2/)

function(add_exec BIN_NAME BIN_FILE)
  add_executable(${BIN_NAME} ${BIN_FILE})
  target_link_libraries(${BIN_NAME} PRIVATE xml2)
endfunction()

add_exec(test_libxml2 test_libxml2.c)
add_exec(01_parse_file 01_parse_file.c)
