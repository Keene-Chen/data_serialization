#[[
# Author : KeeneChen
# Date   : 2023.10.06-23:16:51
]]

project(test_yyjson DESCRIPTION "test_yyjson")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})

#[[
function(add_exec BIN_FILE)
  get_filename_component(BIN_NAME ${BIN_FILE} NAME_WE)
  add_executable(${BIN_NAME} ${BIN_FILE})
  target_link_libraries(${BIN_NAME} PRIVATE yyjson)
  endfunction()
  add_exec(01_demo_read.c)
]]

file(
  GLOB
  SRC
  01_demo_read.c
  02_demo_write.c
  03_test_read.c
  04_test_write.c
  test_yyjson.c)
foreach(INDEX ${SRC})
  get_filename_component(BIN_NAME ${INDEX} NAME_WE)
  add_executable(${BIN_NAME} ${INDEX})
  target_link_libraries(${BIN_NAME} PRIVATE yyjson)
endforeach()
