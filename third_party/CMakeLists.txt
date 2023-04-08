#[[
  file    : third_party/CMakeLists.txt
  author  : KeeneChen
  date    : 2023.03.01-14:26:27
  details : This is the CMakeLists.txt for submodules of third-party libraries
]]

project(
  test_3rd
  VERSION 1.0.0
  DESCRIPTION "test_3rd")

# Custom functions are used to compile third-party libraries
function(kc_add_library LIB_NAME LIB_TYPE LIB_PATH)
  add_library(${LIB_NAME} SHARED "")
  target_sources(
    ${LIB_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/${LIB_PATH}.c
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/${LIB_PATH}.h)
  target_include_directories(${LIB_NAME}
                             PUBLIC ${CMAKE_CURRENT_LIST_DIR}/${LIB_NAME})
  message(STATUS "${BoldMagenta}>>> ${LIB_NAME}.so >>>${ColourReset}")
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
kc_add_library(yyjson SHARED yyjson/yyjson)

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
message(STATUS "${BoldMagenta}>>> json_parser.so >>>${ColourReset}")

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
message(STATUS "${BoldMagenta}>>> ${yaml} >>>${ColourReset}")

#[[
  libxml2: https://github.com/GNOME/libxml2
  Doc: https://gitlab.gnome.org/GNOME/libxml2/-/wikis/home
]]
find_package(LibXml2 REQUIRED)
message(STATUS "${BoldMagenta}>>> ${LibXml2} >>>${ColourReset}")

#[[ protobuf-c: https://github.com/protobuf-c/protobuf-c ]]
find_library(protobuf-c libprotobuf-c.so /usr/lib64)
message(STATUS "${BoldBlue}>>> ${protobuf-c} >>>${ColourReset}")

#[[
  EasyLogger: https://github.com/armink/EasyLogger
  Doc: https://github.com/armink/EasyLogger/tree/master/docs/zh
  Note: This library needs to be configured by yourself
]]
message(
  STATUS
    "${BoldBlue}>>> see also ${CMAKE_SOURCE_DIR}/src/test_easylogger >>>${ColourReset}"
)
