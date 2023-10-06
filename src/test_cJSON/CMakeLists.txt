#[[
# Author : KeeneChen
# Date   : 2023.10.06-23:14:21
]]

project(test_cJSON DESCRIPTION "test_cJSON")

# 设置可执行文件生成位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})

# 自定义函数,将生成可执行文件和链接操作合并
function(add_exec BIN_NAME BIN_FILE)
  add_executable(${BIN_NAME} ${BIN_FILE})
  target_link_libraries(${BIN_NAME} PRIVATE cJSON)
endfunction()

add_exec(01_test_cJSON 01_test_cJSON.c)
add_exec(02_test_cJSON 02_test_cJSON.c)
