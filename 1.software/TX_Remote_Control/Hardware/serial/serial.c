#include "serial.h"

uint32_t debug_message = 0;//用串口调试时使用
uint32_t serial_instructions = 0;//串口屏发送的数据时使用

/**
  * @brief  处理串口1接收到的数据，用于调试
  * @param  无
  * @retval 无
  */
void deal_USART1_data(void) {
    //接收到正确的指令才为1
    char okCmd_1 = 0;
    //检查是否接收到指令
    if (receive_cmd == 1) {
        if (!strcmp(UART_RxBuffer, "x1!")) {
            okCmd_1 = 1;
            debug_message = 1;
        } else if (!strcmp(UART_RxBuffer, "x2!")) {
            okCmd_1 = 1;
            debug_message = 2;
        }
//        else if (!strcmp(UART_RxBuffer, "YH!")) {
//            okCmd_1 = 1;
//            debug_message = 3;
//        } else if (!strcmp(UART_RxBuffer, "QT!")) {
//            okCmd_1 = 1;
//            debug_message = 4;
//        } else if (!strcmp(UART_RxBuffer, "DQ!")) {
//            okCmd_1 = 1;
//            debug_message = 5;
//        }

        if (okCmd_1 != 1) {
            printf("\n\r 输入有误，请重新输入...\n\r");
        }

        //清空串口接收缓冲数组
        receive_cmd = 0;
        uart_FlushRxBuffer();
    }
}

//串口1调试
void Serial_debugging() {

    deal_USART1_data();//处理串口1数据

    //对接收到串口1的数据进行处理
    switch (debug_message) {
        case 1:
            debug_message = 0;
            printf("x1.\n");
            tf = 1;
            txbuf[0] = 1;
            break;
        case 2:
            debug_message = 0;
            printf("x2.\n");
            tf = 1;
            txbuf[1] = 1;
            break;
//        case 3:
//            debug_message = 0;
//            break;
//        case 4:
//            debug_message = 0;
//            break;
//        case 5:
//            debug_message = 0;
//            break;

        default:
            break;
    }

}



// 将用户输入的字符串命令str按照空格分隔成多个字符串，依次放入cmd二维数组中
void cmdsplit(char cmd[][MAX_LENGTH], const char *str) {
    int m = 0, n = 0;    // m表示二位数组第一维，n表示第二维
    while (*str != '\0') {
        if (*str != ' ') {
            cmd[m][n] = *str;
            n++;
        } else {
            cmd[m][n] = '\0';
            n = 0;
            m++;
        }
        str++;
    }
    cmd[m][n] = '\0';
}
