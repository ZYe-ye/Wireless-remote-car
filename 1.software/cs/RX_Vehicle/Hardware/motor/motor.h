#ifndef RX_VEHICLE_MOTOR_H
#define RX_VEHICLE_MOTOR_H

#include "main.h"

#define EN1     PCout(14)
#define EN2     PCout(15)
#define EN3     PAout(4)
#define EN4     PBout(12)
#define EN5     PBout(3)
#define EN6     PAout(3)
#define EN7     PAout(11)
#define EN8     PBout(15)


#define ENA_PWM(speed)      __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, speed)
#define ENB_PWM(speed)      __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, speed)
#define ENC_PWM(speed)      __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, speed)
#define END_PWM(speed)      __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, speed)

#define ALL_PWM(speed)      ENA_PWM(speed);ENB_PWM(speed);ENC_PWM(speed);END_PWM(speed)

#define Motor_1_front       EN1 = 0;EN2 = 1
#define Motor_1_back        EN1 = 1;EN2 = 0
#define Motor_1_stop        EN1 = 0;EN2 = 0

#define Motor_2_front       EN3 = 0;EN4 = 1
#define Motor_2_back        EN3 = 1;EN4 = 0
#define Motor_2_stop        EN3 = 0;EN4 = 0

#define Motor_3_front       EN5 = 1;EN6 = 0
#define Motor_3_back        EN5 = 0;EN6 = 1
#define Motor_3_stop        EN5 = 0;EN6 = 0

#define Motor_4_front       EN7 = 1;EN8 = 0
#define Motor_4_back        EN7 = 0;EN8 = 1
#define Motor_4_stop        EN7 = 0;EN8 = 0

#define vehicle_forward          Motor_1_front;Motor_2_front;Motor_3_front;Motor_4_front
#define vehicle_backward         Motor_1_back;Motor_2_back;Motor_3_back;Motor_4_back
#define vehicle_left             Motor_1_front;Motor_2_front;Motor_3_back;Motor_4_back
#define vehicle_right            Motor_1_back;Motor_2_back;Motor_3_front;Motor_4_front
#define vehicle_stop             Motor_1_stop;Motor_2_stop;Motor_3_stop;Motor_4_stop

void motor_pwm_init(void);//四轮电机PWM部分初始化

#endif //RX_VEHICLE_MOTOR_H
