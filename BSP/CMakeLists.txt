cmake_minimum_required(VERSION 3.22)

# 启用 OSAL 源码构建所需的 C 和汇编语言支持。
enable_language(C ASM)

# 收集 osal/osal 目录下的全部 C 源文件。
file(GLOB BSP_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/Common/modbus/*.c


)

# 设置 OSAL 对外暴露的头文件目录，供链接该库的目标继承。
set(BSP_INC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
    # ${CMAKE_CURRENT_SOURCE_DIR}/Common/modbus


)


add_library(BSP OBJECT)
target_sources(BSP PRIVATE ${BSP_SRC})
target_include_directories(BSP PUBLIC ${BSP_INC})
target_link_libraries(BSP PUBLIC STM32_Drivers_Inc)
