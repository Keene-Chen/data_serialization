#[[
# Author : KeeneChen
# Date   : 2022.09.04-15:06:17
# File   : kc_conf.cmake
# Copyright (c) 2019-2023 KeeneChen
]]

#[[
# colorize CMake output code adapted from stackoverflow:
# http://stackoverflow.com/a/19578320 from post authored by
# https://stackoverflow.com/users/2556117/fraser
]]

# >>> color define >>>
macro(enable_kc_colors)
  if(WIN32)
    # has no effect on WIN32
    set(CReset "")
    set(ColourBold "")
    set(Red "")
    set(Green "")
    set(Yellow "")
    set(Blue "")
    set(Magenta "")
    set(Cyan "")
    set(White "")
    set(BRed "")
    set(BGreen "")
    set(BYellow "")
    set(BBlue "")
    set(BMagenta "")
    set(BCyan "")
    set(BWhite "")
  else()
    string(ASCII 27 Esc)
    set(CReset "${Esc}[m")
    set(ColourBold "${Esc}[1m")
    set(Red "${Esc}[31m")
    set(Green "${Esc}[32m")
    set(Yellow "${Esc}[33m")
    set(Blue "${Esc}[34m")
    set(Magenta "${Esc}[35m")
    set(Cyan "${Esc}[36m")
    set(White "${Esc}[37m")
    set(BRed "${Esc}[1;31m")
    set(BGreen "${Esc}[1;32m")
    set(BYellow "${Esc}[1;33m")
    set(BBlue "${Esc}[1;34m")
    set(BMagenta "${Esc}[1;35m")
    set(BCyan "${Esc}[1;36m")
    set(BWhite "${Esc}[1;37m")
  endif()
endmacro()
# <<< color define <<<

# >>> message color define >>>
macro(kc_message color text)
  if(${color} STREQUAL "red")
    message(STATUS "${BRed}>>> ${text} ${CReset}")
  elseif(${color} STREQUAL "green")
    message(STATUS "${BGreen}>>> ${text} ${CReset}")
  elseif(${color} STREQUAL "yellow")
    message(STATUS "${BYellow}>>> ${text} ${CReset}")
  elseif(${color} STREQUAL "blue")
    message(STATUS "${BBlue}>>> ${text} ${CReset}")
  elseif(${color} STREQUAL "magenta")
    message(STATUS "${BMagenta}>>> ${text} ${CReset}")
  elseif(${color} STREQUAL "cyan")
    message(STATUS "${BCyan}>>> ${text} ${CReset}")
  elseif(${color} STREQUAL "white")
    message(STATUS "${BWhite}>>> ${text} ${CReset}")
  endif()
endmacro()

macro(kc_msg text)
  message(STATUS "${BYellow}>>> ${text} ${CReset}")
endmacro()
# <<< message color define <<<

# >>> debug information >>>
macro(enable_kc_debug)
  # 设置语言标准
  set(CMAKE_C_STANDARD 11)
  set(CMAKE_C_STANDARD_REQUIRED True)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED True)

  # 顶层项目信息
  kc_msg("Name           ${BRed}│ ${PROJECT_NAME}")
  kc_msg("Version        ${BRed}│ ${PROJECT_VERSION}")
  kc_msg("Homepage       ${BRed}│ ${PROJECT_HOMEPAGE_URL}")
  kc_msg("Description    ${BRed}│ ${PROJECT_DESCRIPTION}")

  # 设置默认构建类型
  if(NOT CMAKE_BUILD_TYPE)
    # 将该变量设置为缓存变量，可以通过缓存进行编辑
    set(CMAKE_BUILD_TYPE
        Release
        CACHE STRING "Build Type" FORCE)
    kc_message(yellow "Build Type     ${BRed}│ Release")

  elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    kc_message(red "Build Type     ${BRed}│ Debug")

  elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    kc_message(green "Build Type     ${BRed}│ RelWithDebInfo")

  elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    kc_message(blue "Build Type     ${BRed}│ MinSizeRel")
  endif()

  # CMake 调试信息
  string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%d-%H:%M:%S")
  kc_msg("CMake System   ${BRed}│ ${CMAKE_SYSTEM_NAME}")
  kc_msg("CMake Version  ${BRed}│ ${CMAKE_VERSION}")
  kc_msg("Build DateTime ${BRed}│ ${BUILD_TIMESTAMP}")

  # 设置CMAKE_VERBOSE_MAKEFILE为ON,以显示详细信息
  set(CMAKE_VERBOSE_MAKEFILE OFF)

  # 导出编译命令配置,供clangd使用
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endmacro()
# <<< debug information <<<
