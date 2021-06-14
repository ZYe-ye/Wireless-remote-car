#ifndef __24L01_H
#define __24L01_H
#include "main.h"


/* NRF���Ӧ��SPI��� */
extern SPI_HandleTypeDef NRF_Handler;


#define TX_ADR_WIDTH    5   	//5�ֽڵĵ�ַ���
#define RX_ADR_WIDTH    5   	//5�ֽڵĵ�ַ���
#define TX_PLOAD_WIDTH  32  	//32�ֽڵ��û����ݿ��
#define RX_PLOAD_WIDTH  32  	//32�ֽڵ��û����ݿ��

#define CHANAL 18	//Ƶ��ѡ��

// SPI(NRF14L01) commands ,	NRF��SPI����궨�壬���NRF����ʹ���ĵ�
#define NRF_READ_REG    0x00  // Define read command to register
#define NRF_WRITE_REG   0x20  // Define write command to register
#define RD_RX_PLOAD 0x61  // Define RX payload register address
#define WR_TX_PLOAD 0xA0  // Define TX payload register address
#define FLUSH_TX    0xE1  // Define flush TX register command
#define FLUSH_RX    0xE2  // Define flush RX register command
#define REUSE_TX_PL 0xE3  // Define reuse TX payload register command
#define NOP         0xFF  // Define No Operation, might be used to read status register

// SPI(NRF14L01) registers(addresses) ��NRF14L01 ��ؼĴ�����ַ�ĺ궨��
#define CONFIG      0x00  // 'Config' register address
#define EN_AA       0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR   0x02  // 'Enabled RX addresses' register address
#define SETUP_AW    0x03  // 'Setup address width' register address
#define SETUP_RETR  0x04  // 'Setup Auto. Retrans' register address
#define RF_CH       0x05  // 'RF channel' register address
#define RF_SETUP    0x06  // 'RF setup' register address
#define STATUS      0x07  // 'Status' register address
#define OBSERVE_TX  0x08  // 'Observe TX' register address
#define CD          0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0  0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1  0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2  0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3  0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4  0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5  0x0F  // 'RX address pipe5' register address
#define TX_ADDR     0x10  // 'TX address' register address
#define RX_PW_P0    0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1    0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2    0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3    0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4    0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5    0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS 0x17  // 'FIFO Status Register' register address


#define MAX_TX  		0x10  //�ﵽ����ʹ����ж�
#define TX_DS   		0x20  //TX��������ж�
#define RX_DR   		0x40  //���յ������ж�

//NRF���Ŷ���
/*******************************************************/
/*CE����*/
#define NRF_CE_PIN                     GPIO_PIN_15
#define NRF_CE_GPIO_PORT               GPIOA
#define NRF_CE_GPIO_CLK_ENABLE()        __GPIOA_CLK_ENABLE()

/*CSN����*/
#define NRF_CSN_PIN                     GPIO_PIN_1
#define NRF_CSN_GPIO_PORT               GPIOA
#define NRF_CSN_GPIO_CLK_ENABLE()       __GPIOA_CLK_ENABLE()

/*SCK����*/
#define NRF_CLK_PIN                      GPIO_PIN_5
#define NRF_CLK_GPIO_PORT                GPIOA
#define NRF_CLK_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()

/*MISO����*/
#define NRF_MISO_PIN                     GPIO_PIN_6
#define NRF_MISO_GPIO_PORT               GPIOA
#define NRF_MISO_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()


/*MOSI����*/
#define NRF_MOSI_PIN                    GPIO_PIN_7
#define NRF_MOSI_GPIO_PORT              GPIOA
#define NRF_MOSI_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()

/*IRQ����*/
#define NRF_IRQ_PIN                     GPIO_PIN_2
#define NRF_IRQ_GPIO_PORT               GPIOA
#define NRF_IRQ_GPIO_CLK_ENABLE()       __GPIOC_CLK_ENABLE()

/*ѡ��SPI*/
#define NRF_SPI                         SPI1
/*SPIʱ��*/
#define NRF_SPI_CLOCK()                 __HAL_RCC_SPI1_CLK_ENABLE();
/************************************************************/


#define NRF_CE_0()         HAL_GPIO_WritePin(NRF_CE_GPIO_PORT,NRF_CE_PIN,GPIO_PIN_RESET)
#define NRF_CE_1()         HAL_GPIO_WritePin(NRF_CE_GPIO_PORT,NRF_CE_PIN,GPIO_PIN_SET)

#define NRF_CSN_0()        HAL_GPIO_WritePin(NRF_CSN_GPIO_PORT,NRF_CSN_PIN,GPIO_PIN_RESET)
#define NRF_CSN_1()        HAL_GPIO_WritePin(NRF_CSN_GPIO_PORT,NRF_CSN_PIN,GPIO_PIN_SET)

#define NRF_CLK_0()        HAL_GPIO_WritePin(NRF_CLK_GPIO_PORT,NRF_CLK_PIN,GPIO_PIN_RESET)
#define NRF_CLK_1()        HAL_GPIO_WritePin(NRF_CLK_GPIO_PORT,NRF_CLK_PIN,GPIO_PIN_SET)

#define NRF_MOSI_0()       HAL_GPIO_WritePin(NRF_MOSI_GPIO_PORT,NRF_MOSI_PIN,GPIO_PIN_RESET)
#define NRF_MOSI_1()       HAL_GPIO_WritePin(NRF_MOSI_GPIO_PORT,NRF_MOSI_PIN,GPIO_PIN_SET)

#define NRF_Read_IRQ()	    HAL_GPIO_ReadPin(NRF_IRQ_GPIO_PORT, NRF_IRQ_PIN)  //�ж�����
/************************************************************/

//NRF���ͽ������ݿ�ȶ���
uint8_t SPI_NRF_RW(uint8_t TxData);
void SPI_NRF_Init(void);//��ʼ��
void NRF_RX_Mode(void);//����Ϊ����ģʽ
void NRF_TX_Mode(void);//����Ϊ����ģʽ
uint8_t SPI_NRF_WriteBuf(uint8_t reg, uint8_t *pBuf, uint8_t uint8_ts);//д������
uint8_t SPI_NRF_ReadBuf(uint8_t reg, uint8_t *pBuf, uint8_t uint8_ts);//��������
uint8_t SPI_NRF_ReadReg(uint8_t reg);			//���Ĵ���
uint8_t SPI_NRF_WriteReg(uint8_t reg, uint8_t value);//д�Ĵ���
uint8_t NRF_Check(void);//���24L01�Ƿ����
uint8_t NRF_Tx_Dat(uint8_t *txbuf);//����һ����������
uint8_t NRF_Rx_Dat(uint8_t *rxbuf);//����һ����������


#endif
