/**
  ******************************************************************************
  * @file    bsp_xxx.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   ����ģ��/nrf24l01+/�������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��STMF767������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ***********************************************************************m*******
  */

#include "bsp_nrf24l01.h"

SPI_HandleTypeDef NRF_Handler;

const uint8_t TX_ADDRESS[TX_ADR_WIDTH] = {0x34, 0x43, 0x10, 0x10, 0x01}; //���͵�ַ
const uint8_t RX_ADDRESS[RX_ADR_WIDTH] = {0x34, 0x43, 0x10, 0x10, 0x01}; //���͵�ַ


/**
  * @brief  SPI_NRF�� I/O����
  * @param  ��
  * @retval ��
  */
void SPI_NRF_Init(void) {
    GPIO_InitTypeDef GPIO_Initure;

    /* ʹ����Ӧ�˿ڵ�ʱ�� */
    NRF_CE_GPIO_CLK_ENABLE();
    NRF_CSN_GPIO_CLK_ENABLE();
    NRF_CLK_GPIO_CLK_ENABLE();
    NRF_MISO_GPIO_CLK_ENABLE();
    NRF_MOSI_GPIO_CLK_ENABLE();
    NRF_IRQ_GPIO_CLK_ENABLE();
    /* ʹ��SPI2ʱ�� */
    NRF_SPI_CLOCK();

    /* ��ʼ��CLK���ŵ����� */
    GPIO_Initure.Pin = NRF_CLK_PIN;
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(NRF_CLK_GPIO_PORT, &GPIO_Initure);

    /* ��ʼ��MISO���ŵ����� */
    GPIO_Initure.Pin = NRF_MISO_PIN;
    HAL_GPIO_Init(NRF_MISO_GPIO_PORT, &GPIO_Initure);

    /* ��ʼ��MOSI���ŵ����� */
    GPIO_Initure.Pin = NRF_MOSI_PIN;
    HAL_GPIO_Init(NRF_MOSI_GPIO_PORT, &GPIO_Initure);

    /* ��ʼ��CSN���ŵ����� */
    GPIO_Initure.Pin = NRF_CSN_PIN;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(NRF_CSN_GPIO_PORT, &GPIO_Initure);

    /* ��ʼ��CE���ŵ����� */
    GPIO_Initure.Pin = NRF_CE_PIN;
    HAL_GPIO_Init(NRF_CE_GPIO_PORT, &GPIO_Initure);

    /* ��ʼ��IRQ���ŵ����� */
    GPIO_Initure.Pin = NRF_IRQ_PIN;
    GPIO_Initure.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(NRF_IRQ_GPIO_PORT, &GPIO_Initure);

    /* ��ʼ��SPI������ */
    NRF_Handler.Instance = NRF_SPI;                      //SPI2
    NRF_Handler.Init.Mode = SPI_MODE_MASTER;          //����SPI����ģʽ������Ϊ��ģʽ
    NRF_Handler.Init.Direction = SPI_DIRECTION_2LINES;//SPI����Ϊ˫��ģʽ
    NRF_Handler.Init.DataSize = SPI_DATASIZE_8BIT;    //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
    NRF_Handler.Init.CLKPolarity = SPI_POLARITY_LOW;  //����ͬ��ʱ�ӵĿ���״̬Ϊ�͵�ƽ
    NRF_Handler.Init.CLKPhase = SPI_PHASE_1EDGE;      //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
    NRF_Handler.Init.NSS = SPI_NSS_SOFT;              //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
    NRF_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ9MHz
    NRF_Handler.Init.FirstBit = SPI_FIRSTBIT_MSB;     //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    NRF_Handler.Init.CRCPolynomial = 7;               //CRCֵ����Ķ���ʽ
    HAL_SPI_Init(&NRF_Handler);
    __HAL_SPI_ENABLE(&NRF_Handler);                 //ʹ��SPI

    NRF_CE_0();
    /*�õ�CSN��ʹ��SPI����*/
    NRF_CSN_1();
}


/**
  * @brief   ������NRF��/дһ�ֽ�����
  * @param   д�������
  *	@arg     TxData 
  * @retval  ��ȡ�õ�����
  */
uint8_t SPI_NRF_RW(uint8_t TxData) {
    uint8_t Rxdata;
    HAL_SPI_TransmitReceive(&NRF_Handler, &TxData, &Rxdata, 1, 1000);
    return Rxdata;                    //�����յ�������
}


/**
  * @brief  ��Ҫ����NRF��MCU�Ƿ���������
  * @param  ��
  * @retval SUCCESS/ERROR ��������/����ʧ��
  */
uint8_t NRF_Check(void) {
    uint8_t buf[5] = {0XA5, 0XA5, 0XA5, 0XA5, 0XA5};
    uint8_t buf1[5];
    uint8_t i;
    SPI_NRF_WriteBuf(NRF_WRITE_REG + TX_ADDR, buf, 5);//д��5���ֽڵĵ�ַ.
    SPI_NRF_ReadBuf(TX_ADDR, buf1, 5); //����д��ĵ�ַ
    for (i = 0; i < 5; i++) {
        if (buf1[i] != 0XA5)
            break;
    }
    if (i != 5)return ERROR;    //���24L01����
    return SUCCESS;             //��⵽24L01
}


/**
  * @brief   ������NRF�ض��ļĴ���д������
  * @param   
  *	@arg     reg:NRF������+�Ĵ�����ַ
  *	@arg     dat:��Ҫ��Ĵ���д�������
  * @retval  NRF��status�Ĵ�����״̬
  */
uint8_t SPI_NRF_WriteReg(uint8_t reg, uint8_t value) {
    uint8_t status;
    /*�õ�CSN��ʹ��SPI����*/
    NRF_CSN_0();

    /*��������Ĵ����� */
    status = SPI_NRF_RW(reg);

    /*��Ĵ���д������*/
    SPI_NRF_RW(value);

    /*CSN���ߣ����*/
    NRF_CSN_1();

    /*����״̬�Ĵ�����ֵ*/
    return (status);
}


/**
  * @brief   ���ڴ�NRF�ض��ļĴ�����������
  * @param   
  *		@arg   reg:NRF������+�Ĵ�����ַ
  * @retval  �Ĵ����е�����
  */
uint8_t SPI_NRF_ReadReg(uint8_t reg) {
    uint8_t reg_val;
    /*�õ�CSN��ʹ��SPI����*/
    NRF_CSN_0();

    /*���ͼĴ����� */
    SPI_NRF_RW(reg);

    /*��ȡ�Ĵ�����ֵ */
    reg_val = SPI_NRF_RW(NOP);

    /*CSN���ߣ����*/
    NRF_CSN_1();

    return (reg_val);
}


/**
  * @brief   ������NRF�ļĴ�����д��һ������
  * @param   
  *		@arg   reg : NRF������+�Ĵ�����ַ
  *		@arg   pBuf�����ڴ洢���������ļĴ������ݵ����飬�ⲿ����
  * 	@arg   bytes: pBuf�����ݳ���
  * @retval  NRF��status�Ĵ�����״̬
  */
uint8_t SPI_NRF_ReadBuf(uint8_t reg, uint8_t *pBuf, uint8_t len) {
    uint8_t status, uint8_t_ctr;
    /*�õ�CSN��ʹ��SPI����*/
    NRF_CSN_0();

    /*���ͼĴ����� */
    status = SPI_NRF_RW(reg);

    /*��ȡ����������*/
    for (uint8_t_ctr = 0; uint8_t_ctr < len; uint8_t_ctr++)
        pBuf[uint8_t_ctr] = SPI_NRF_RW(NOP);

    /*CSN���ߣ����*/
    NRF_CSN_1();

    /*����״̬�Ĵ�����ֵ*/
    return status;
}


/**
  * @brief    ������NRF�ļĴ�����д��һ������
  * @param   
  *	@arg      reg : NRF������+�Ĵ�����ַ
  *	@arg      pBuf���洢�˽�Ҫд��д�Ĵ������ݵ����飬�ⲿ����
  * @arg      bytes: pBuf�����ݳ���
  * @retval   NRF��status�Ĵ�����״̬
  */
uint8_t SPI_NRF_WriteBuf(uint8_t reg, uint8_t *pBuf, uint8_t len) {
    uint8_t status, uint8_t_ctr;

    /*�õ�CSN��ʹ��SPI����*/
    NRF_CSN_0();

    /*���ͼĴ����� */
    status = SPI_NRF_RW(reg);

    /*�򻺳���д������*/
    for (uint8_t_ctr = 0; uint8_t_ctr < len; uint8_t_ctr++)
        SPI_NRF_RW(*pBuf++);

    /*CSN���ߣ����*/
    NRF_CSN_1();
    return status;
}


/**
  * @brief   ������NRF�ķ��ͻ�������д������
  * @param   
  *		@arg txBuf���洢�˽�Ҫ���͵����ݵ����飬�ⲿ����	
  * @retval  ���ͽ�����ɹ�����TXDS,ʧ�ܷ���MAXRT��ERROR
  */
uint8_t NRF_Tx_Dat(uint8_t *txbuf) {
    uint8_t state;

    /*ceΪ�ͣ��������ģʽ1*/
    NRF_CE_0();

    /*д���ݵ�TX BUF ��� 32���ֽ�*/
    SPI_NRF_WriteBuf(WR_TX_PLOAD, txbuf, TX_PLOAD_WIDTH);

    /*CEΪ�ߣ�txbuf�ǿգ��������ݰ� */
    NRF_CE_1();

    /*�ȴ���������ж� */
    while (NRF_Read_IRQ() != 0);

    /*��ȡ״̬�Ĵ�����ֵ */
    state = SPI_NRF_ReadReg(STATUS);

    /*���TX_DS��MAX_RT�жϱ�־*/
    SPI_NRF_WriteReg(NRF_WRITE_REG + STATUS, state);

    SPI_NRF_WriteReg(FLUSH_TX, NOP);    //���TX FIFO�Ĵ���

    /*�ж��ж�����*/
    if (state & MAX_TX)                     //�ﵽ����ط�����
        return MAX_TX;

    else if (state & TX_DS)                  //�������
        return TX_DS;
    else
        return ERROR;                 //����ԭ����ʧ��
}

/**
  * @brief   ���ڴ�NRF�Ľ��ջ������ж�������
  * @param   
  *		@arg rxBuf �����ڽ��ո����ݵ����飬�ⲿ����	
  * @retval 
  *		@arg ���ս��
  */
uint8_t NRF_Rx_Dat(uint8_t *rxbuf) {
    uint8_t state;
    NRF_CE_1();     //�������״̬
    /*�ȴ������ж�*/
    while (NRF_Read_IRQ() == 0) {
        NRF_CE_0();     //�������״̬
        /*��ȡstatus�Ĵ�����ֵ  */
        state = SPI_NRF_ReadReg(STATUS);

        /* ����жϱ�־*/
        SPI_NRF_WriteReg(NRF_WRITE_REG + STATUS, state);

        /*�ж��Ƿ���յ�����*/
        if (state & RX_DR)                                 //���յ�����
        {
            SPI_NRF_ReadBuf(RD_RX_PLOAD, rxbuf, RX_PLOAD_WIDTH);//��ȡ����
            SPI_NRF_WriteReg(FLUSH_RX, NOP);          //���RX FIFO�Ĵ���
            return RX_DR;
        } else
            return ERROR;                    //û�յ��κ�����
    }

    return ERROR;                    //û�յ��κ�����
}


/**
  * @brief  NRF���ò��������ģʽ
  * @param  ��
  * @retval ��
  */
void NRF_RX_Mode(void) {
    NRF_CE_0();
    SPI_NRF_WriteBuf(NRF_WRITE_REG + RX_ADDR_P0, (uint8_t *) RX_ADDRESS, RX_ADR_WIDTH);//дRX�ڵ��ַ

    SPI_NRF_WriteReg(NRF_WRITE_REG + EN_AA, 0x01);       //ʹ��ͨ��0���Զ�Ӧ��
    SPI_NRF_WriteReg(NRF_WRITE_REG + EN_RXADDR, 0x01);   //ʹ��ͨ��0�Ľ��յ�ַ
    SPI_NRF_WriteReg(NRF_WRITE_REG + RF_CH, CHANAL);            //����RFͨ��Ƶ��
    SPI_NRF_WriteReg(NRF_WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ��
    SPI_NRF_WriteReg(NRF_WRITE_REG + RF_SETUP, 0x0f);    //����TX�������,0db����,2Mbps,���������濪��
    SPI_NRF_WriteReg(NRF_WRITE_REG + CONFIG, 0x0f);     //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ
    NRF_CE_1(); //CEΪ��,�������ģʽ
}


/**
  * @brief  NRF���÷���ģʽ
  * @param  ��
  * @retval ��
  */
void NRF_TX_Mode(void) {
    NRF_CE_0();
    SPI_NRF_WriteBuf(NRF_WRITE_REG + TX_ADDR, (uint8_t *) TX_ADDRESS, TX_ADR_WIDTH);//дTX�ڵ��ַ
    SPI_NRF_WriteBuf(NRF_WRITE_REG + RX_ADDR_P0, (uint8_t *) RX_ADDRESS, RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK

    SPI_NRF_WriteReg(NRF_WRITE_REG + EN_AA, 0x01);     //ʹ��ͨ��0���Զ�Ӧ��
    SPI_NRF_WriteReg(NRF_WRITE_REG + EN_RXADDR, 0x01); //ʹ��ͨ��0�Ľ��յ�ַ
    SPI_NRF_WriteReg(NRF_WRITE_REG + SETUP_RETR, 0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
    SPI_NRF_WriteReg(NRF_WRITE_REG + RF_CH, CHANAL);       //����RFͨ��Ϊ40
    SPI_NRF_WriteReg(NRF_WRITE_REG + RF_SETUP, 0x0f);  //����TX�������,0db����,2Mbps,���������濪��
    SPI_NRF_WriteReg(NRF_WRITE_REG + CONFIG, 0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
    NRF_CE_1();
    delay_us(100);                        //CEҪ����һ��ʱ��Ž��뷢��ģʽ
}


