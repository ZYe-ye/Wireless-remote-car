#ifndef SERIAL_K210_CS_SERIAL_H
#define SERIAL_K210_CS_SERIAL_H

#include "main.h"

#define MAX_LENGTH            20


void deal_USART1_data(void);//������1���յ�������,���ڵ���
void Serial_debugging(void);//���ڵ���


// ���û�������ַ�������str���տո�ָ��ɶ���ַ��������η���cmd��ά������
void cmdsplit(char cmd[][MAX_LENGTH], const char *str);

#endif //SERIAL_K210_CS_SERIAL_H
