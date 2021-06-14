#include "robot_arm.h"

uint16_t Chassis_price = 150;
uint16_t Forearm_price = 70;
uint16_t Postbrachium_price = 250;
//uint16_t Claw_price = 200;


//机械臂的舵机初始化
void robot_arm_init(void) {
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);

    Chassis_PMW(Chassis_price);
    Forearm_PMW(Forearm_price);
    Postbrachium_PMW(Postbrachium_price);
    claw_Close;
//    Claw_PMW(Claw_price);
}

