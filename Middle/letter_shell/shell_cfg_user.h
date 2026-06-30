/**
 * @file shell_cfg_user.h
 * @brief letter shell user config for bare-metal STM32F1.
 */

#ifndef __SHELL_CFG_USER_H__
#define __SHELL_CFG_USER_H__

#include "stm32f1xx_hal.h"

/**
 * @brief 是否使用默认 shell 任务 while 循环
 *        使能此宏后，shellTask() 会一直循环读取输入，一般用于操作系统任务。
 *        裸机环境下关闭此宏，并在主循环中周期调用 shellTask()。
 */
#define SHELL_TASK_WHILE            0

/**
 * @brief 是否使用命令导出方式
 *        使能后可通过 SHELL_EXPORT_CMD() 等宏将命令导出到指定链接段。
 *        关闭后使用 shell_cmd_list.c 中的静态命令表。
 */
#define SHELL_USING_CMD_EXPORT      0

/**
 * @brief 是否使用 shell 伴生对象
 *        文件系统支持、日志工具等扩展组件可能需要使用伴生对象。
 */
#define SHELL_USING_COMPANION       0

/**
 * @brief 是否支持 shell 尾行模式
 */
#define SHELL_SUPPORT_END_LINE      0

/**
 * @brief 使用 LF 作为命令行回车触发字符
 *        可以和 SHELL_ENTER_CR 同时开启。
 */
#define SHELL_ENTER_LF              1

/**
 * @brief 使用 CR 作为命令行回车触发字符
 *        可以和 SHELL_ENTER_LF 同时开启。
 */
#define SHELL_ENTER_CR              1

/**
 * @brief 使用 CRLF 作为命令行回车触发字符
 *        不可与 SHELL_ENTER_LF 或 SHELL_ENTER_CR 同时开启。
 */
#define SHELL_ENTER_CRLF            0

/**
 * @brief shell 格式化输入缓冲区大小
 *        设置为 0 时不使用 shell 格式化输入。
 * @note  shell 格式化输入会阻塞 shellTask，仅适合有操作系统的环境。
 */
#define SHELL_SCAN_BUFFER           0

/**
 * @brief 获取系统时间，单位为 ms
 *        用于双击 Tab 补全命令帮助和 shell 超时锁定。
 */
#define SHELL_GET_TICK()            HAL_GetTick()

/**
 * @brief 是否使用 shell 锁
 * @note  使用 shell 锁时，需要实现加锁和解锁接口。
 */
#define SHELL_USING_LOCK            0

#endif





// #ifndef __SHELL_CFG_USER_H__
// #define __SHELL_CFG_USER_H__

// #include "stm32f1xx_hal.h"
// // #include "FreeRTOS.h"
// // #include "portable.h"

// /**
//  * @brief 是否使用shell伴生对象
//  *        一些扩展的组件(文件系统支持，日志工具等)需要使用伴生对象
//  */
// #define     SHELL_USING_COMPANION       1


// /**
//  * @brief 支持shell尾行模式
//  */
// #define     SHELL_SUPPORT_END_LINE      1


// /**
//  * @brief 使用LF作为命令行回车触发
//  *        可以和SHELL_ENTER_CR同时开启
//  */
// #define     SHELL_ENTER_LF              1

// /**
//  * @brief 使用CR作为命令行回车触发
//  *        可以和SHELL_ENTER_LF同时开启
//  */
// #define     SHELL_ENTER_CR              0

// /**
//  * @brief 使用CRLF作为命令行回车触发
//  *        不可以和SHELL_ENTER_LF或SHELL_ENTER_CR同时开启
//  */
// #define     SHELL_ENTER_CRLF            1

// /**
//  * @brief shell格式化输入的缓冲大小
//  *        为0时不使用shell格式化输入
//  * @note shell格式化输入会阻塞shellTask, 仅适用于在有操作系统的情况下使用
//  */
// #define     SHELL_SCAN_BUFFER          128

// /**
//  * @brief 获取系统时间(ms)
//  *        定义此宏为获取系统Tick，如`HAL_GetTick()`
//  * @note 此宏不定义时无法使用双击tab补全命令help，无法使用shell超时锁定
//  */
// #define     SHELL_GET_TICK()            HAL_GetTick()

// /**
//  * @brief 使用锁
//  * @note 使用shell锁时，需要对加锁和解锁进行实现
//  */
// #define     SHELL_USING_LOCK            1

// /**
//  * @brief shell内存分配
//  *        shell本身不需要此接口，若使用shell伴生对象，需要进行定义
//  */
// #define     SHELL_MALLOC(size)          pvPortMalloc(size)

// /**
//  * @brief shell内存释放
//  *        shell本身不需要此接口，若使用shell伴生对象，需要进行定义
//  */
// #define     SHELL_FREE(obj)             vPortFree(obj)

// #endif
