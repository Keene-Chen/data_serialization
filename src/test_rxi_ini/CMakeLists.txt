#[[
# Author : KeeneChen
# Date   : 2023.10.06-23:16:17
]]

project(test_rxi_ini DESCRIPTION "test_rxi_ini")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})

function(add_exec BIN_NAME BIN_FILE)
  add_executable(${BIN_NAME} ${BIN_FILE})
  target_link_libraries(${BIN_NAME} PRIVATE rxi_ini)
endfunction()

add_exec(test_rxi_ini test_rxi_ini.c)
