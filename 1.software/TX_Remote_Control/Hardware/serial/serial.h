#ifndef SERIAL_K210_CS_SERIAL_H
#define SERIAL_K210_CS_SERIAL_H

#include "main.h"

#define MAX_LENGTH            20


void deal_USART1_data(void);//处理串口1接收到的数据,用于调试
void Serial_debugging(void);//串口调试


// 将用户输入的字符串命令str按照空格分隔成多个字符串，依次放入cmd二维数组中
void cmdsplit(char cmd[][MAX_LENGTH], const char *str);

#endif //SERIAL_K210_CS_SERIAL_H
