project(
  test_protobuf-c
  VERSION 1.0.0
  DESCRIPTION "test_protobuf-c")

# 自定义函数,将生成可执行文件和链接操作合并
#[[
  function(add_test_file TEST_NAME TEST_FILE)
  string(APPEND TEST_NAME "_demo")
  add_executable(${TEST_NAME} ${TEST_FILE})
  target_link_libraries(${TEST_NAME} PRIVATE ${LIBZIP})
  endfunction()
]]

# 设置可执行文件、库生成位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME})

include_directories(${CMAKE_SOURCE_DIR}/res/protobuf)
add_executable(test_protobuf-c test_protobuf-c.c
                               ${CMAKE_SOURCE_DIR}/res/protobuf/student.pb-c.c)
target_link_libraries(test_protobuf-c ${protobuf-c})
