#include "ball_device.h"

//放球装置的舵机初始化
void ball_device_init(void) {
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
//    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);

    bucket_return;//桶：回
    door_close;//门：关


}