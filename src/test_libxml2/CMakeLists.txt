project(
  test_libxml2
  VERSION 1.0.0
  DESCRIPTION "test_libxml2")

# 设置可执行文件、库生成位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})

include_directories(/usr/include/libxml2/)

# 自定义函数,将生成可执行文件和链接操作合并
function(add_test_file TEST_NAME TEST_FILE)
  string(APPEND TEST_NAME "_demo")
  add_executable(${TEST_NAME} ${TEST_FILE})
  target_link_libraries(${TEST_NAME} PRIVATE xml2)
endfunction()

add_test_file(test_libxml2 test_libxml2.c)
add_test_file(01_parse_file 01_parse_file.c)
