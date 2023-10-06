#[[
# Author : KeeneChen
# Date   : 2023.10.06-23:03:31
# details : This is the CMakeLists.txt for submodules of third-party libraries
]]

project(test_3rd DESCRIPTION "test_3rd")

# Custom functions are used to compile third-party libraries
function(kc_add_library LIB_NAME LIB_TYPE LIB_PATH)
  add_library(${LIB_NAME} SHARED "")
  target_sources(
    ${LIB_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/${LIB_PATH}.c
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/${LIB_PATH}.h)
  target_include_directories(${LIB_NAME}
                             PUBLIC ${CMAKE_CURRENT_LIST_DIR}/${LIB_NAME})
  kc_message(cyan ${LIB_NAME}.so)
endfunction(kc_add_library)

#[[
  cJSON: https://github.com/DaveGamble/cJSON
  Doc: https://github.com/DaveGamble/cJSON#usage
]]
kc_add_library(cJSON SHARED cJSON/cJSON)
kc_add_library(cJSON_Utils SHARED cJSON/cJSON_Utils)

#[[
  yyjson: https://github.com/ibireme/yyjson
  Doc: https://ibireme.github.io/yyjson/doc/doxygen/html/
]]
# kc_add_library(yyjson SHARED yyjson/yyjson)

# Let CMake download yyjson
include(FetchContent)
FetchContent_Declare(
  yyjson
  GIT_REPOSITORY https://github.com/ibireme/yyjson.git
  GIT_TAG master # master, or version number, e.g. 0.8.0
)
FetchContent_GetProperties(yyjson)
if(NOT yyjson_POPULATED)
  FetchContent_Populate(yyjson)
  add_subdirectory(${yyjson_SOURCE_DIR} ${yyjson_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

#[[
json_parser: https://github.com/Barenboim/json_parser
Doc: https://ibireme.github.io/yyjson/doc/doxygen/html/
]]
add_library(json_parser SHARED "")
target_sources(
  json_parser
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/json_parser/json_parser.c
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}/json_parser/rbtree.c
  PUBLIC ${CMAKE_CURRENT_LIST_DIR}/json_parser/json_parser.h)
target_include_directories(json_parser
                           PUBLIC ${CMAKE_CURRENT_LIST_DIR}/json_parser)
kc_message(cyan json_parser.so)

#[[ inih: https://github.com/benhoyt/inih ]]
kc_add_library(inih SHARED inih/ini)

#[[ rxi_ini: https://github.com/rxi/ini ]]
kc_add_library(rxi_ini SHARED rxi_ini/rxi_ini)

#[[ rxi_log: https://github.com/rxi/log.c ]]
kc_add_library(rxi_log SHARED rxi_log/rxi_log)
target_compile_definitions(rxi_log PRIVATE -DLOG_USE_COLOR)

#[[
  libyaml: https://github.com/yaml/libyaml
  Doc: https://pyyaml.org/wiki/LibYAML
]]
find_library(yaml libyaml.a /usr/local/lib REQUIRED)
kc_message(cyan ${yaml})

#[[
  libxml2: https://github.com/GNOME/libxml2
  Doc: https://gitlab.gnome.org/GNOME/libxml2/-/wikis/home
]]
find_package(LibXml2 REQUIRED)
# kc_message(cyan ${LibXml2})

#[[ protobuf-c: https://github.com/protobuf-c/protobuf-c ]]
find_library(protobuf-c libprotobuf-c.so /usr/lib64)
kc_message(cyan ${protobuf-c})

#[[
  EasyLogger: https://github.com/armink/EasyLogger
  Doc: https://github.com/armink/EasyLogger/tree/master/docs/zh
  Note: This library needs to be configured by yourself
]]
kc_msg("see also ${CMAKE_SOURCE_DIR}/src/test_easylogger")

#[[
  xlsxio: https://github.com/brechtsanders/xlsxio
  Note:
]]
find_library(XLSXIO_READ libxlsxio_read.so /usr/local/lib REQUIRED)
find_library(XLSXIO_WRITE libxlsxio_write.so /usr/local/lib REQUIRED)
kc_message(cyan ${XLSXIO_READ})

#[[
  xlsxio: https://www.libxl.com/home.html
  Doc: https://www.libxl.com/documentation.html
  Note: closed source and paid
]]
find_library(LIBXL libxl.so /usr/local/lib64 REQUIRED)
kc_message(cyan ${LIBXL})
