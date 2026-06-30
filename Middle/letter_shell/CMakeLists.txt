cmake_minimum_required(VERSION 3.22)

# 启用 OSAL 源码构建所需的 C 和汇编语言支持。
enable_language(C ASM)

# 收集 osal/osal 目录下的全部 C 源文件。
file(GLOB Letter_shell_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Log/*.c


)

# 设置 OSAL 对外暴露的头文件目录，供链接该库的目标继承。
set(Letter_shell_INC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Src
    ${CMAKE_CURRENT_SOURCE_DIR}/Log


)


add_library(Letter_shell OBJECT)
target_sources(Letter_shell PRIVATE ${Letter_shell_SRC})
target_include_directories(Letter_shell PUBLIC ${Letter_shell_INC})
target_compile_definitions(Letter_shell PUBLIC
    SHELL_CFG_USER="shell_cfg_user.h"
)
target_link_libraries(Letter_shell PUBLIC 
    STM32_Drivers_Inc
    BSP
    )
