cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#
# (翻译) 该文件仅在初始化时生成一次，转换器被多次调用时不会重新生成。
# (翻译) 用户可以根据需要自由修改此文件。

# Setup compiler settings
# (翻译) 设置编译器相关选项
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
# (翻译) 定义构建类型（如果未设置则默认使用 Debug）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
# (翻译) 设置项目名称
set(CMAKE_PROJECT_NAME Temple_Project)

# Enable compile command to ease indexing with e.g. clangd
# (翻译) 启用导出编译命令，便于 clangd 等工具进行索引
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
# (翻译) 核心项目设置
project(${CMAKE_PROJECT_NAME} LANGUAGES C ASM)
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
# (翻译) 为汇编（ASM）和 C 语言启用 CMake 语言支持
enable_language(C ASM)

# Create an executable object type
# (翻译) 创建一个可执行目标
# add_executable(${CMAKE_PROJECT_NAME})
# We'll collect sources and create the executable target with sources below

# --- User configuration: sources, startup and includes ---
# You can override these variables from command line if needed.
set(STARTUP_FILE "${CMAKE_SOURCE_DIR}/startup_stm32f103xb.s")

# Gather project sources. For determinism you can list files explicitly.
# Using simple GLOB here for convenience; feel free to replace with explicit lists.
file(GLOB USER_SOURCES
    "${CMAKE_SOURCE_DIR}/User/*.c"
)
file(GLOB HARDWARE_SOURCES
    "${CMAKE_SOURCE_DIR}/Hardware/*.c"
)
# Library sources (STM32 peripheral drivers) are built by cmake/stm32cubemx
# as an OBJECT library (STM32_Drivers). Do not add them twice to the main
# executable target to avoid multiple-definition linker errors.
# file(GLOB LIBRARY_SOURCES
#     "${CMAKE_SOURCE_DIR}/Library/*.c"
# )
file(GLOB SYSTEM_SOURCES
    "${CMAKE_SOURCE_DIR}/System/*.c"
)

set(ALL_SOURCES ${STARTUP_FILE} ${USER_SOURCES} ${HARDWARE_SOURCES} ${SYSTEM_SOURCES})

add_executable(${CMAKE_PROJECT_NAME} ${ALL_SOURCES})

add_subdirectory(cmake/stm32cubemx)

# Link directories setup
# (翻译) 链接目录设置（在此处可以添加用户自定义的库搜索路径）
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add include paths
# (翻译) 添加头文件包含路径（在此列出用户自定义包含目录）
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Library
    ${CMAKE_SOURCE_DIR}/Start
    ${CMAKE_SOURCE_DIR}/User
    ${CMAKE_SOURCE_DIR}/Hardware
    ${CMAKE_SOURCE_DIR}/System
)

# Add project symbols (macros)
# (翻译) 添加项目宏定义（在此列出用户自定义宏）
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    STM32F10X_MD
)

# Compiler options: rely on toolchain defaults, but add common warnings and section flags
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -mfloat-abi=soft
    -ffunction-sections
    -fdata-sections
    -Wall
    -Wextra
)

# Link options: linker script and GC sections are set in toolchain file, but ensure map output
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -Wl,-Map=${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.map
    -Wl,--cref
)

# Remove wrong libob.a library dependency when using cpp files
# (翻译) 在使用 C++ 文件时，移除错误的 libob.a 链接依赖
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
# (翻译) 链接库到可执行目标（此处将 STM32CubeMX 接口库和其他用户库链接进来）
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
)

# Post-build: generate BIN and HEX files using objcopy
find_program(ARM_NONE_EABI_OBJCOPY NAMES ${TOOLCHAIN_PREFIX}objcopy objcopy)
if(ARM_NONE_EABI_OBJCOPY)
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${ARM_NONE_EABI_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
        COMMAND ${ARM_NONE_EABI_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex
        COMMENT "Generating BIN/HEX files"
    )
else()
    message(WARNING "objcopy not found. BIN/HEX generation disabled. Make sure arm-none-eabi-objcopy is in PATH or set TOOLCHAIN_PREFIX in toolchain file.")
endif()

# Optional: simple flash target using st-flash (if available)
find_program(ST_FLASH_EXECUTABLE NAMES st-flash)
if(ST_FLASH_EXECUTABLE)
    add_custom_target(flash
        COMMAND ${ST_FLASH_EXECUTABLE} write ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin 0x8000000
        DEPENDS ${CMAKE_PROJECT_NAME}
        COMMENT "Flashing via st-flash"
    )
endif()
