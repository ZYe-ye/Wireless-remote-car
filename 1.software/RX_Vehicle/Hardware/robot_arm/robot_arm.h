#ifndef RX_VEHICLE_ROBOT_ARM_H
#define RX_VEHICLE_ROBOT_ARM_H

#include "main.h"

extern uint16_t Chassis_price;
extern uint16_t Forearm_price;
extern uint16_t Postbrachium_price;
extern uint16_t claw_state;    //爪子的状态；0为关，1为开

extern int32_t C_time, F_time, P_time;//循环次数
extern int32_t C_judge, F_judge, P_judge;//判断正负

//typedef struct {
//    uint32_t Chassis_price;         //底盘占空比值
//    uint32_t Forearm_price;            //前臂占空比值
//    uint32_t Postbrachium_price;    //后臂占空比值
//    uint32_t Claw_switch;           //爪的开关量
//    char order[4];                  //运行顺序
//} Arm_state;

// 底盘
#define Chassis_PMW(price)              __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, price);
// 前臂
#define Forearm_PMW(price)              __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, price);
// 后臂
#define Postbrachium_PMW(price)         __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, price);
// 爪
#define Claw_PMW(price)                 __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, price);

//爪的开关
#define claw_Open                       claw_state = 1;Claw_PMW(250)
#define claw_Close                      claw_state = 0;Claw_PMW(200)

#define arm_delay                       HAL_Delay(20)
#define Free_delay                      HAL_Delay(15)
#define ACC_size                        2

#define Chassis_Uniform(time, judge, price)                 Postbrachium_running(time, judge, price, 1)
#define Forearm_Uniform(time, judge, price)                 Postbrachium_running(time, judge, price, 2)
#define Postbrachium_Uniform(time, judge, price)            Postbrachium_running(time, judge, price, 3)
#define judge_switch(Claw_switch)                           if(Claw_switch){claw_Open;}else {claw_Close;}


/*---------------自由移动，计算--------------------*/
#define Num_cal(a, b)            a < b ? (b-a)/2:(a-b)/2
#define PM(a, b)                 a < b ? 1:0
#define AS(a, b)                 a ?(b -= 2):(b += 2)
/*-----------------------------------------------*/

/*------------------机械动作----------------------*/
//左抓
#define Left_to_catch            free_control("1324", 250, 70, 180, 1)
//右抓
#define right_to_grasp           free_control("1324", 50, 70, 180, 1)
//抓后放球
#define Put_after_catch          free_control("4231", 154, 50, 194, 0);claw_Open;HAL_Delay(500);claw_Close

/*-----------------------------------------------*/


void robot_arm_init(void);//机械臂的舵机初始化

void free_control(char order_char[4], int32_t C_value, int32_t F_value, int32_t P_value, uint32_t Claw_switch);

void Postbrachium_running(uint32_t time, uint32_t judge, uint16_t *price, uint32_t CCR);


void Chassis_constant(void);
void Forearm_constant(void);
void Postbrachium_constant(void);
void Claw_constant(void);
void NOP_arm(void);

#endif //RX_VEHICLE_ROBOT_ARM_H
