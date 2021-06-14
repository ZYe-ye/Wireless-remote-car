#include "serial.h"

uint32_t debug_message = 0;//�ô��ڵ���ʱʹ��
uint32_t serial_instructions = 0;//���������͵�����ʱʹ��

/**
  * @brief  ������1���յ������ݣ����ڵ���
  * @param  ��
  * @retval ��
  */
void deal_USART1_data(void) {
    //���յ���ȷ��ָ���Ϊ1
    char okCmd_1 = 0;
    //����Ƿ���յ�ָ��
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
            printf("\n\r ������������������...\n\r");
        }

        //��մ��ڽ��ջ�������
        receive_cmd = 0;
        uart_FlushRxBuffer();
    }
}

//����1����
void Serial_debugging() {

    deal_USART1_data();//������1����

    //�Խ��յ�����1�����ݽ��д���
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



// ���û�������ַ�������str���տո�ָ��ɶ���ַ��������η���cmd��ά������
void cmdsplit(char cmd[][MAX_LENGTH], const char *str) {
    int m = 0, n = 0;    // m��ʾ��λ�����һά��n��ʾ�ڶ�ά
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
