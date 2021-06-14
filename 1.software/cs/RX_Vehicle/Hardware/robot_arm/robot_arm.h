#ifndef RX_VEHICLE_ROBOT_ARM_H
#define RX_VEHICLE_ROBOT_ARM_H

#include "main.h"

extern uint16_t Chassis_price;
extern uint16_t Forearm_price;
extern uint16_t Postbrachium_price;
//extern uint16_t Claw_price;

// ����
#define   Chassis_PMW(price)            __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, price);
// ǰ��
#define   Forearm_PMW(price)            __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, price);
// ���
#define   Postbrachium_PMW(price)       __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, price);
// צ
#define   Claw_PMW(price)               __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, price);

#define   claw_Open                     Claw_PMW(250)
#define   claw_Close                    Claw_PMW(200)

#define   arm_delay                     HAL_Delay(20)

void robot_arm_init(void);//��е�۵Ķ����ʼ��

#endif //RX_VEHICLE_ROBOT_ARM_H
