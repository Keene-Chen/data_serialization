project(
  test_libxl
  VERSION 1.0.0
  DESCRIPTION "test_libxl")

# 设置可执行文件、库生成位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})

# 自定义函数,将生成可执行文件和链接操作合并
function(add_test_file TEST_NAME TEST_FILE)
  string(APPEND TEST_NAME "_demo")
  add_executable(${TEST_NAME} ${TEST_FILE})
  target_link_libraries(${TEST_NAME} PRIVATE ${LIBXL})
endfunction()

add_test_file(test_xl_read test_xl_read.c)
add_test_file(test_xl_write test_xl_write.c)
