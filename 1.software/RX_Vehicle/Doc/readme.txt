
include_directories(System/delay System/retarget System/sys)
include_directories(Hardware/NRF24L01 Hardware/robot_arm Hardware/motor Hardware/ball_device)

add_definitions(-DUSE_HAL_DRIVER -DSTM32F103xB)

file(GLOB_RECURSE SOURCES "startup/*.*" "Drivers/*.*" "Core/*.*" "System/*.*" "Hardware/*.*")



NRF24L01(SPI1):
CE      <------>    PA15
CSN     <------>    PA1
CLK(SCK)<------>    PA5
MISO    <------>    PA6
MOSI    <------>    PA7
IRQ     <------>    PA2


舵机:
Chassis         <------>    PB6(TIM4_CH1--底盘)
Forearm         <------>    PB7(TIM4_CH2--前臂)
Postbrachium    <------>    PB8(TIM4_CH3--后臂)
Claw            <------>    PB9(TIM4_CH4--爪)

Servo1          <------>    PA0(TIM2_CH1)
Servo2          <------>    PB10(TIM2_CH3)
Servo3          <------>    PB11(TIM2_CH4)

电机:
ENA     <------>    PB4(TIM3_CH1)
ENB     <------>    PB5(TIM3_CH2)
ENC     <------>    PB0(TIM3_CH3)
END     <------>    PB1(TIM3_CH4)

EN1     <------>    PC14
EN2     <------>    PC15
EN3     <------>    PA4
EN4     <------>    PB12
EN5     <------>    PB3
EN6     <------>    PA3
EN7     <------>    PA11
EN8     <------>    PB15
