#ifndef RX_VEHICLE_ROBOT_ARM_H
#define RX_VEHICLE_ROBOT_ARM_H

#include "main.h"

extern uint16_t Chassis_price;
extern uint16_t Forearm_price;
extern uint16_t Postbrachium_price;
extern uint16_t claw_state;    //צ�ӵ�״̬��0Ϊ�أ�1Ϊ��

extern int32_t C_time, F_time, P_time;//ѭ������
extern int32_t C_judge, F_judge, P_judge;//�ж�����

//typedef struct {
//    uint32_t Chassis_price;         //����ռ�ձ�ֵ
//    uint32_t Forearm_price;            //ǰ��ռ�ձ�ֵ
//    uint32_t Postbrachium_price;    //���ռ�ձ�ֵ
//    uint32_t Claw_switch;           //צ�Ŀ�����
//    char order[4];                  //����˳��
//} Arm_state;

// ����
#define Chassis_PMW(price)              __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, price);
// ǰ��
#define Forearm_PMW(price)              __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, price);
// ���
#define Postbrachium_PMW(price)         __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, price);
// צ
#define Claw_PMW(price)                 __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, price);

//צ�Ŀ���
#define claw_Open                       claw_state = 1;Claw_PMW(250)
#define claw_Close                      claw_state = 0;Claw_PMW(200)

#define arm_delay                       HAL_Delay(20)
#define Free_delay                      HAL_Delay(15)
#define ACC_size                        2

#define Chassis_Uniform(time, judge, price)                 Postbrachium_running(time, judge, price, 1)
#define Forearm_Uniform(time, judge, price)                 Postbrachium_running(time, judge, price, 2)
#define Postbrachium_Uniform(time, judge, price)            Postbrachium_running(time, judge, price, 3)
#define judge_switch(Claw_switch)                           if(Claw_switch){claw_Open;}else {claw_Close;}


/*---------------�����ƶ�������--------------------*/
#define Num_cal(a, b)            a < b ? (b-a)/2:(a-b)/2
#define PM(a, b)                 a < b ? 1:0
#define AS(a, b)                 a ?(b -= 2):(b += 2)
/*-----------------------------------------------*/

/*------------------��е����----------------------*/
//��ץ
#define Left_to_catch            free_control("1324", 250, 70, 180, 1)
//��ץ
#define right_to_grasp           free_control("1324", 50, 70, 180, 1)
//ץ�����
#define Put_after_catch          free_control("4231", 154, 50, 194, 0);claw_Open;HAL_Delay(500);claw_Close

/*-----------------------------------------------*/


void robot_arm_init(void);//��е�۵Ķ����ʼ��

void free_control(char order_char[4], int32_t C_value, int32_t F_value, int32_t P_value, uint32_t Claw_switch);

void Postbrachium_running(uint32_t time, uint32_t judge, uint16_t *price, uint32_t CCR);


void Chassis_constant(void);
void Forearm_constant(void);
void Postbrachium_constant(void);
void Claw_constant(void);
void NOP_arm(void);

#endif //RX_VEHICLE_ROBOT_ARM_H
