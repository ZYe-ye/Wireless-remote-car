#include "ball_device.h"

//����װ�õĶ����ʼ��
void ball_device_init(void) {
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
//    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);

    bucket_return;//Ͱ����
    door_close;//�ţ���


}