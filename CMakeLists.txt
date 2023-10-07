#[[
# File    : data_serialization/CMakeLists.txt
# Author  : KeeneChen
# Date    : 2023.03.01-14:26:27
# Details : This is the top-level CMakeLists.txt for the project
# GitHub  : https://github.com/Keene-Chen/data_serialization
]]

cmake_minimum_required(VERSION 3.10...3.20)

project(
  cmake_template
  VERSION 1.0.1
  DESCRIPTION "cmake_template"
  LANGUAGES C)

# 包括kc_conf.cmake模块,调用其中定义的宏
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(kc_conf)
enable_kc_colors()
enable_kc_debug()

# 开启测试
enable_testing()

# 获取上级目录的名称并设置生成二进制文件路径
macro(set_bin_dir)
  get_filename_component(PARENT_DIR ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)
  get_filename_component(PARENT_DIR_NAME ${PARENT_DIR} NAME)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PARENT_DIR_NAME})
endmacro()

# 添加子目录
set(SUBDIR
    # test_cJSON
    test_yyjson
    # test_json_parser
    # test_inih
    # test_rxi_ini
    # test_rxi_log
    # test_easylogger
    # test_libyaml
    # test_libxml2
    # test_protobuf-c
    # test_xlsxio
    test_libxl)
add_subdirectory(third_party)
foreach(index ${SUBDIR})
  add_subdirectory(src/${index})
endforeach()
