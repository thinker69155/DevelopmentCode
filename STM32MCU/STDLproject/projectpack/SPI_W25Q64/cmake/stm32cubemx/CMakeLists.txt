cmake_minimum_required(VERSION 3.22)
# 为汇编（ASM）和 C 语言启用 CMake 语言支持
enable_language(C ASM)
# STM32CubeMX 生成的符号（宏）
# Ensure we enable the Standard Peripheral Library (SPL) and select the device
set(MX_Defines_Syms
    USE_STDPERIPH_DRIVER
    STM32F10X_MD
    $<$<CONFIG:Debug>:DEBUG>
)

# STM32CubeMX 生成的包含目录
# set(MX_Include_Dirs
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Inc
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32F1xx_HAL_Driver/Inc
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Device/ST/STM32F1xx/Include
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Include
# )
# Adjust include dirs to match this repository layout
set(MX_Include_Dirs
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Library
    ${CMAKE_SOURCE_DIR}/Start
    ${CMAKE_SOURCE_DIR}/User
    ${CMAKE_SOURCE_DIR}/Hardware
    ${CMAKE_SOURCE_DIR}/System
)

# STM32CubeMX 生成的应用程序源文件
# set(MX_Application_Src
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/main.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stm32f1xx_it.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stm32f1xx_hal_msp.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/sysmem.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/syscalls.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../startup_stm32f103xb.s
# )
set(MX_Application_Src
    ${CMAKE_SOURCE_DIR}/User/main.c
    ${CMAKE_SOURCE_DIR}/User/stm32f10x_it.c
    ${CMAKE_SOURCE_DIR}/startup_stm32f103xb.s
    ${CMAKE_SOURCE_DIR}/Start/system_stm32f10x.c
)

# STM32 HAL/低级（LL）驱动源码
# set(STM32_Drivers_Src
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/system_stm32f1xx.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
# )
# Collect available STM32F1 peripheral driver sources from Library/ (if any)
file(GLOB STM32_Drivers_Src
    "${CMAKE_SOURCE_DIR}/Library/stm32f10x_*.c"
    "${CMAKE_SOURCE_DIR}/Library/misc.c"
)

# Also include core/cm3 support if present
# if(EXISTS "${CMAKE_SOURCE_DIR}/Start/core_cm3.c")
#     list(APPEND STM32_Drivers_Src ${CMAKE_SOURCE_DIR}/Start/core_cm3.c)
# endif()

# core_cm3.c in Start/ can contain compiler-specific assembly that may not compile
# cleanly with our toolchain; do not auto-compile it. If you need it, add it
# explicitly after verifying compatibility.
# if(EXISTS "${CMAKE_SOURCE_DIR}/Start/core_cm3.c")
#    list(APPEND STM32_Drivers_Src ${CMAKE_SOURCE_DIR}/Start/core_cm3.c)
# endif()

# 驱动中间件（当前为空，可在此处添加中间件源或目录）
# （无条目）

# 链接目录设置（用于 target_link_directories）
set(MX_LINK_DIRS

)
# 项目静态库列表（供 target_link_libraries 使用）
set(MX_LINK_LIBS
    ${TOOLCHAIN_LINK_LIBRARIES}
)
# 接口库：用于传递包含路径和宏定义给依赖目标
add_library(stm32cubemx INTERFACE)
target_include_directories(stm32cubemx INTERFACE ${MX_Include_Dirs})
target_compile_definitions(stm32cubemx INTERFACE ${MX_Defines_Syms})

# 创建 STM32_Drivers（OBJECT）库并将 HAL 驱动源加入其中
# add_library(STM32_Drivers OBJECT)
# target_sources(STM32_Drivers PRIVATE ${STM32_Drivers_Src})
# target_link_libraries(STM32_Drivers PUBLIC stm32cubemx)
#
#
# 将 STM32CubeMX 生成的应用源文件添加到主项目目标
# target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MX_Application_Src})
#
if(STM32_Drivers_Src)
    add_library(STM32_Drivers OBJECT)
    target_sources(STM32_Drivers PRIVATE ${STM32_Drivers_Src})
    target_link_libraries(STM32_Drivers PUBLIC stm32cubemx)
    list(APPEND MX_LINK_LIBS STM32_Drivers)
endif()

# 将 STM32CubeMX 生成的应用源文件添加到主项目目标
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MX_Application_Src})

# 为主项目目标设置链接目录
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${MX_LINK_DIRS})

# 将预定义的库链接到主项目目标
target_link_libraries(${CMAKE_PROJECT_NAME} ${MX_LINK_LIBS})

# 将生成的 .map 文件加入 clean 清理列表（在 clean 时删除）
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

# 校验生成代码所需的 C 标准：如果当前 C 标准为 C90/C99，则报错（需要 C11 或更高）
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()
