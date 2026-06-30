/**
 * @file shell_port.c
 * @author Letter (NevermindZZT@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-02-22
 * 
 * @copyright (c) 2019 Letter
 * 
 */


#include "shell_port.h"
#include "bsp.h"

Shell shell;
static char shellBuffer[512];
UART_HandleTypeDef huart1;
#define SHELL_RX_BUFFER_SIZE 128U

static uint8_t shellRxBuffer[SHELL_RX_BUFFER_SIZE];
static uint8_t shellRxByte;
static volatile uint16_t shellRxHead;
static volatile uint16_t shellRxTail;

static void ShellUart1Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler(__FILE__, __LINE__);
    }
}

short userShellWrite(char *data, unsigned short len)
{
    if (data == NULL || len == 0)
    {
        return 0;
    }

    if (HAL_UART_Transmit(&huart1, (uint8_t *)data, len, HAL_MAX_DELAY) == HAL_OK)
    {
        return (short)len;
    }

    return 0;
}

short userShellRead(char *data, unsigned short len)
{
    unsigned short count = 0;

    if (data == NULL || len == 0)
    {
        return 0;
    }

    while (count < len && shellRxTail != shellRxHead)
    {
        data[count++] = (char)shellRxBuffer[shellRxTail];
        shellRxTail = (shellRxTail + 1U) % SHELL_RX_BUFFER_SIZE;
    }

    return (short)count;
}

void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        uint16_t next = (shellRxHead + 1U) % SHELL_RX_BUFFER_SIZE;

        if (next != shellRxTail)
        {
            shellRxBuffer[shellRxHead] = shellRxByte;
            shellRxHead = next;
        }

        HAL_UART_Receive_IT(&huart1, &shellRxByte, 1U);
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        __HAL_UART_CLEAR_OREFLAG(huart);    /* 清除溢出错误标志 */
        __HAL_UART_CLEAR_FEFLAG(huart);     /* 清除帧错误标志 */
        __HAL_UART_CLEAR_PEFLAG(huart);     /* 清除奇偶校验错误标志 */
        HAL_UART_Receive_IT(&huart1, &shellRxByte, 1U);
    }
}


void userShellInit(void)
{
    ShellUart1Init();

    shell.write = userShellWrite;
    shell.read = userShellRead;

    shellRxHead = 0U;
    shellRxTail = 0U;
    HAL_NVIC_SetPriority(USART1_IRQn, 2U, 0U);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

    __HAL_UART_CLEAR_FLAG(&huart1, UART_FLAG_ORE | UART_FLAG_FE | UART_FLAG_PE);
    HAL_UART_Receive_IT(&huart1, &shellRxByte, 1U);

    shellInit(&shell, shellBuffer, sizeof(shellBuffer));
}

void userShellTask(void)
{
    shellTask(&shell);
}

















 
// #include "FreeRTOS.h"
// #include "task.h"
// #include "shell.h"
// #include "serial.h"
// #include "stm32f1xx_hal.h"
// #include "usart.h"
// #include "cevent.h"
// #include "log.h"


// Shell shell;
// char shellBuffer[512];

// static SemaphoreHandle_t shellMutex;

// /**
//  * @brief 用户shell写
//  * 
//  * @param data 数据
//  * @param len 数据长度
//  * 
//  * @return short 实际写入的数据长度
//  */
// short userShellWrite(char *data, unsigned short len)
// {
//     serialTransmit(&debugSerial, (uint8_t *)data, len, 0x1FF);
//     return len;
// }


// /**
//  * @brief 用户shell读
//  * 
//  * @param data 数据
//  * @param len 数据长度
//  * 
//  * @return short 实际读取到
//  */
// short userShellRead(char *data, unsigned short len)
// {
//     return serialReceive(&debugSerial, (uint8_t *)data, len, 0);
// }

// /**
//  * @brief 用户shell上锁
//  * 
//  * @param shell shell
//  * 
//  * @return int 0
//  */
// int userShellLock(Shell *shell)
// {
//     xSemaphoreTakeRecursive(shellMutex, portMAX_DELAY);
//     return 0;
// }

// /**
//  * @brief 用户shell解锁
//  * 
//  * @param shell shell
//  * 
//  * @return int 0
//  */
// int userShellUnlock(Shell *shell)
// {
//     xSemaphoreGiveRecursive(shellMutex);
//     return 0;
// }

// /**
//  * @brief 用户shell初始化
//  * 
//  */
// void userShellInit(void)
// {
//     shellMutex = xSemaphoreCreateMutex();

//     shell.write = userShellWrite;
//     shell.read = userShellRead;
//     shell.lock = userShellLock;
//     shell.unlock = userShellUnlock;
//     shellInit(&shell, shellBuffer, 512);
//     if (xTaskCreate(shellTask, "shell", 256, &shell, 5, NULL) != pdPASS)
//     {
//         logError("shell task creat failed");
//     }
// }
// CEVENT_EXPORT(EVENT_INIT_STAGE2, userShellInit);

