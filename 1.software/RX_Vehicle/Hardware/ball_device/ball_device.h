#ifndef RX_VEHICLE_BALL_DEVICE_H
#define RX_VEHICLE_BALL_DEVICE_H

#include "main.h"

void ball_device_init(void);//放球装置的舵机初始化

// 桶
#define bucket_PMW(price)            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, price);
// 门
#define door_PMW(price)              __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, price);

//桶：倒
#define bucket_fall                 bucket_PMW(50)
//桶：回
#define bucket_return               bucket_PMW(100)

//门：开
#define door_open                   door_PMW(150)
//门：关
#define door_close                  door_PMW(50)

//倒桶
#define reladling_barrel            free_control("1000", 50, 0, 0, 0); \
                                    HAL_Delay(200); \
                                    bucket_fall;    \
                                    door_open
//收桶
#define Collecting_barrel           bucket_return; \
                                    door_close;    \
                                    HAL_Delay(200); \
                                    free_control("1000", 154, 0, 0, 0)


#endif //RX_VEHICLE_BALL_DEVICE_H
