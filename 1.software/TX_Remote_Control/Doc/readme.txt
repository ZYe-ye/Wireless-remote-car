

include_directories(System/sys System/delay System/retarget)
include_directories(Hardware/NRF24L01 Hardware/serial)

add_definitions(-DUSE_HAL_DRIVER -DSTM32F103xB)

file(GLOB_RECURSE SOURCES "startup/*.*" "Drivers/*.*" "Core/*.*" "System/*.*" "Hardware/*.*")


NRF24L01(SPI1):
CE      <------>    PA15
CSN     <------>    PA1
CLK(SCK)<------>    PA5
MISO    <------>    PA6
MOSI    <------>    PA7
IRQ     <------>    PA2

ADC(ADC1):
ADC_1   <------>    PA3(ADC1_IN3)
ADC_2   <------>    PA4(ADC1_IN4)
ADC_3   <------>    PB0(ADC1_IN8)
ADC_4   <------>    PB1(ADC1_IN9)

KEY(EXTI):
KEY1    <------>    PA0
KEY2    <------>    PB5
KEY3    <------>    PB6
KEY4    <------>    PB7
KEY5    <------>    PB8
KEY6    <------>    PB9
KEY7    <------>    PB10
KEY8    <------>    PB11
KEY9    <------>    PB12
KEY10   <------>    PB13
KEY11   <------>    PB14(摇杆部分)
KEY12   <------>    PB15(摇杆部分)

