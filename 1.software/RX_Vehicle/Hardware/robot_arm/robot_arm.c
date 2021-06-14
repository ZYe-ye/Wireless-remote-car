#include "robot_arm.h"

//�������ռ�ձȵ�ֵ
uint16_t Chassis_price = 154;
uint16_t Forearm_price = 50;
uint16_t Postbrachium_price = 194;
uint16_t claw_state = 0;    //צ�ӵ�״̬��0Ϊ�أ�1Ϊ��

int32_t C_time = 0, F_time = 0, P_time = 0;//ѭ������
int32_t C_judge = 1, F_judge = 1, P_judge = 1;//�ж�����

////ʵ�����еĻ�е��״̬
//Arm_state virtual_condition = {
//        .Chassis_price = 150,
//        .Forearm_price = 50,
//        .Postbrachium_price = 220,
//        .Claw_switch = 0
//};

//void(*step_over[4])();

//��е�۵Ķ����ʼ��
void robot_arm_init(void) {
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);

    Chassis_PMW(Chassis_price);
    Forearm_PMW(Forearm_price);
    Postbrachium_PMW(Postbrachium_price);
    claw_Close;
}

/**
  * @brief  ���ɿ��ƺ���.
  * @param  char order_char[4]:˳��ִ��
  * @param  C_value��������Ҫת����λ��ֵ.
  * @param  F_value��ǰ����Ҫת����λ��ֵ.
  * @param  P_value�������Ҫת����λ��ֵ.
  * @param  Claw_switch��צ�Ŀ�����.
  * @retval None
  */
void free_control(char order_char[4], int32_t C_value, int32_t F_value, int32_t P_value, uint32_t Claw_switch) {
    int i;
    void (*step_over[4])() = {&NOP_arm, &NOP_arm, &NOP_arm, &NOP_arm};
    void (*step_default[4])() = {
            &Chassis_constant, &Forearm_constant, &Postbrachium_constant, &Claw_constant
    };
    /*----------------����ѭ������������-------------------*/
    //����
    C_time = Num_cal(C_value, Chassis_price);
    C_judge = PM(C_value, Chassis_price);
    //ǰ��
    F_time = Num_cal(F_value, Forearm_price);
    F_judge = PM(F_value, Forearm_price);
    //���
    P_time = Num_cal(P_value, Postbrachium_price);
    P_judge = PM(P_value, Postbrachium_price);
    /*-------------------------------------------------*/
    /*-----------------�����ƶ������---------------------*/
    for (i = 0; i < 4; ++i) {
        '1' == order_char[i] ? step_over[0] = step_default[i] : NOP_arm;
        '2' == order_char[i] ? step_over[1] = step_default[i] : NOP_arm;
        '3' == order_char[i] ? step_over[2] = step_default[i] : NOP_arm;
        '4' == order_char[i] ? step_over[3] = step_default[i] : NOP_arm;
    }
    order_char[3] != '0' ? claw_state = Claw_switch : 0;
    for (i = 0; i < 4; ++i) {
        step_over[i]();
    }
    /*-------------------------------------------------*/
}

/**
  * @brief  ָ����������ƶ�����.
  * @param  time��ѭ������.
  * @param  judge���ж�����.
  * @param  price�����ռ�ձȵ�ֵ.
  * @param  CCR��TIM4����/�Ƚ�ͨ��.
  * @retval None
  */
void Postbrachium_running(uint32_t time, uint32_t judge, uint16_t *price, uint32_t CCR) {
    while (time--) {
        AS(judge, *price);
        *(unsigned int *) (TIM4_BASE + 0x30 + CCR * 4) = *price;
        Free_delay;
    }
}


void Chassis_constant(void) {
    Chassis_Uniform(C_time, C_judge, &Chassis_price);
}

void Forearm_constant(void) {
    Forearm_Uniform(F_time, F_judge, &Forearm_price);
}

void Postbrachium_constant(void) {
    Postbrachium_Uniform(P_time, P_judge, &Postbrachium_price);
}

void Claw_constant(void) {
    judge_switch(claw_state);
}

void NOP_arm(void) {

}
