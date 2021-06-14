#ifndef RX_VEHICLE_BALL_DEVICE_H
#define RX_VEHICLE_BALL_DEVICE_H

#include "main.h"

void ball_device_init(void);//����װ�õĶ����ʼ��

// Ͱ
#define bucket_PMW(price)            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, price);
// ��
#define door_PMW(price)              __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, price);

//Ͱ����
#define bucket_fall                 bucket_PMW(50)
//Ͱ����
#define bucket_return               bucket_PMW(100)

//�ţ���
#define door_open                   door_PMW(150)
//�ţ���
#define door_close                  door_PMW(50)

//��Ͱ
#define reladling_barrel            free_control("1000", 50, 0, 0, 0); \
                                    HAL_Delay(200); \
                                    bucket_fall;    \
                                    door_open
//��Ͱ
#define Collecting_barrel           bucket_return; \
                                    door_close;    \
                                    HAL_Delay(200); \
                                    free_control("1000", 154, 0, 0, 0)


#endif //RX_VEHICLE_BALL_DEVICE_H
