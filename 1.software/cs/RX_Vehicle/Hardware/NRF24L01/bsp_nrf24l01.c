/**
  ******************************************************************************
  * @file    bsp_xxx.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   无线模块/nrf24l01+/单板测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火STMF767开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ***********************************************************************m*******
  */

#include "bsp_nrf24l01.h"

SPI_HandleTypeDef NRF_Handler;

const uint8_t TX_ADDRESS[TX_ADR_WIDTH] = {0x34, 0x43, 0x10, 0x10, 0x01}; //发送地址
const uint8_t RX_ADDRESS[RX_ADR_WIDTH] = {0x34, 0x43, 0x10, 0x10, 0x01}; //发送地址


/**
  * @brief  SPI_NRF的 I/O配置
  * @param  无
  * @retval 无
  */
void SPI_NRF_Init(void) {
    GPIO_InitTypeDef GPIO_Initure;

    /* 使能相应端口的时钟 */
    NRF_CE_GPIO_CLK_ENABLE();
    NRF_CSN_GPIO_CLK_ENABLE();
    NRF_CLK_GPIO_CLK_ENABLE();
    NRF_MISO_GPIO_CLK_ENABLE();
    NRF_MOSI_GPIO_CLK_ENABLE();
    NRF_IRQ_GPIO_CLK_ENABLE();
    /* 使能SPI2时钟 */
    NRF_SPI_CLOCK();

    /* 初始化CLK引脚的配置 */
    GPIO_Initure.Pin = NRF_CLK_PIN;
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(NRF_CLK_GPIO_PORT, &GPIO_Initure);

    /* 初始化MISO引脚的配置 */
    GPIO_Initure.Pin = NRF_MISO_PIN;
    HAL_GPIO_Init(NRF_MISO_GPIO_PORT, &GPIO_Initure);

    /* 初始化MOSI引脚的配置 */
    GPIO_Initure.Pin = NRF_MOSI_PIN;
    HAL_GPIO_Init(NRF_MOSI_GPIO_PORT, &GPIO_Initure);

    /* 初始化CSN引脚的配置 */
    GPIO_Initure.Pin = NRF_CSN_PIN;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(NRF_CSN_GPIO_PORT, &GPIO_Initure);

    /* 初始化CE引脚的配置 */
    GPIO_Initure.Pin = NRF_CE_PIN;
    HAL_GPIO_Init(NRF_CE_GPIO_PORT, &GPIO_Initure);

    /* 初始化IRQ引脚的配置 */
    GPIO_Initure.Pin = NRF_IRQ_PIN;
    GPIO_Initure.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(NRF_IRQ_GPIO_PORT, &GPIO_Initure);

    /* 初始化SPI的配置 */
    NRF_Handler.Instance = NRF_SPI;                      //SPI2
    NRF_Handler.Init.Mode = SPI_MODE_MASTER;          //设置SPI工作模式，设置为主模式
    NRF_Handler.Init.Direction = SPI_DIRECTION_2LINES;//SPI设置为双线模式
    NRF_Handler.Init.DataSize = SPI_DATASIZE_8BIT;    //设置SPI的数据大小:SPI发送接收8位帧结构
    NRF_Handler.Init.CLKPolarity = SPI_POLARITY_LOW;  //串行同步时钟的空闲状态为低电平
    NRF_Handler.Init.CLKPhase = SPI_PHASE_1EDGE;      //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
    NRF_Handler.Init.NSS = SPI_NSS_SOFT;              //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
    NRF_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;//定义波特率预分频的值:波特率预分频值为9MHz
    NRF_Handler.Init.FirstBit = SPI_FIRSTBIT_MSB;     //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    NRF_Handler.Init.CRCPolynomial = 7;               //CRC值计算的多项式
    HAL_SPI_Init(&NRF_Handler);
    __HAL_SPI_ENABLE(&NRF_Handler);                 //使能SPI

    NRF_CE_0();
    /*置低CSN，使能SPI传输*/
    NRF_CSN_1();
}


/**
  * @brief   用于向NRF读/写一字节数据
  * @param   写入的数据
  *	@arg     TxData 
  * @retval  读取得的数据
  */
uint8_t SPI_NRF_RW(uint8_t TxData) {
    uint8_t Rxdata;
    HAL_SPI_TransmitReceive(&NRF_Handler, &TxData, &Rxdata, 1, 1000);
    return Rxdata;                    //返回收到的数据
}


/**
  * @brief  主要用于NRF与MCU是否正常连接
  * @param  无
  * @retval SUCCESS/ERROR 连接正常/连接失败
  */
uint8_t NRF_Check(void) {
    uint8_t buf[5] = {0XA5, 0XA5, 0XA5, 0XA5, 0XA5};
    uint8_t buf1[5];
    uint8_t i;
    SPI_NRF_WriteBuf(NRF_WRITE_REG + TX_ADDR, buf, 5);//写入5个字节的地址.
    SPI_NRF_ReadBuf(TX_ADDR, buf1, 5); //读出写入的地址
    for (i = 0; i < 5; i++) {
        if (buf1[i] != 0XA5)
            break;
    }
    if (i != 5)return ERROR;    //检测24L01错误
    return SUCCESS;             //检测到24L01
}


/**
  * @brief   用于向NRF特定的寄存器写入数据
  * @param   
  *	@arg     reg:NRF的命令+寄存器地址
  *	@arg     dat:将要向寄存器写入的数据
  * @retval  NRF的status寄存器的状态
  */
uint8_t SPI_NRF_WriteReg(uint8_t reg, uint8_t value) {
    uint8_t status;
    /*置低CSN，使能SPI传输*/
    NRF_CSN_0();

    /*发送命令及寄存器号 */
    status = SPI_NRF_RW(reg);

    /*向寄存器写入数据*/
    SPI_NRF_RW(value);

    /*CSN拉高，完成*/
    NRF_CSN_1();

    /*返回状态寄存器的值*/
    return (status);
}


/**
  * @brief   用于从NRF特定的寄存器读出数据
  * @param   
  *		@arg   reg:NRF的命令+寄存器地址
  * @retval  寄存器中的数据
  */
uint8_t SPI_NRF_ReadReg(uint8_t reg) {
    uint8_t reg_val;
    /*置低CSN，使能SPI传输*/
    NRF_CSN_0();

    /*发送寄存器号 */
    SPI_NRF_RW(reg);

    /*读取寄存器的值 */
    reg_val = SPI_NRF_RW(NOP);

    /*CSN拉高，完成*/
    NRF_CSN_1();

    return (reg_val);
}


/**
  * @brief   用于向NRF的寄存器中写入一串数据
  * @param   
  *		@arg   reg : NRF的命令+寄存器地址
  *		@arg   pBuf：用于存储将被读出的寄存器数据的数组，外部定义
  * 	@arg   bytes: pBuf的数据长度
  * @retval  NRF的status寄存器的状态
  */
uint8_t SPI_NRF_ReadBuf(uint8_t reg, uint8_t *pBuf, uint8_t len) {
    uint8_t status, uint8_t_ctr;
    /*置低CSN，使能SPI传输*/
    NRF_CSN_0();

    /*发送寄存器号 */
    status = SPI_NRF_RW(reg);

    /*读取缓冲区数据*/
    for (uint8_t_ctr = 0; uint8_t_ctr < len; uint8_t_ctr++)
        pBuf[uint8_t_ctr] = SPI_NRF_RW(NOP);

    /*CSN拉高，完成*/
    NRF_CSN_1();

    /*返回状态寄存器的值*/
    return status;
}


/**
  * @brief    用于向NRF的寄存器中写入一串数据
  * @param   
  *	@arg      reg : NRF的命令+寄存器地址
  *	@arg      pBuf：存储了将要写入写寄存器数据的数组，外部定义
  * @arg      bytes: pBuf的数据长度
  * @retval   NRF的status寄存器的状态
  */
uint8_t SPI_NRF_WriteBuf(uint8_t reg, uint8_t *pBuf, uint8_t len) {
    uint8_t status, uint8_t_ctr;

    /*置低CSN，使能SPI传输*/
    NRF_CSN_0();

    /*发送寄存器号 */
    status = SPI_NRF_RW(reg);

    /*向缓冲区写入数据*/
    for (uint8_t_ctr = 0; uint8_t_ctr < len; uint8_t_ctr++)
        SPI_NRF_RW(*pBuf++);

    /*CSN拉高，完成*/
    NRF_CSN_1();
    return status;
}


/**
  * @brief   用于向NRF的发送缓冲区中写入数据
  * @param   
  *		@arg txBuf：存储了将要发送的数据的数组，外部定义	
  * @retval  发送结果，成功返回TXDS,失败返回MAXRT或ERROR
  */
uint8_t NRF_Tx_Dat(uint8_t *txbuf) {
    uint8_t state;

    /*ce为低，进入待机模式1*/
    NRF_CE_0();

    /*写数据到TX BUF 最大 32个字节*/
    SPI_NRF_WriteBuf(WR_TX_PLOAD, txbuf, TX_PLOAD_WIDTH);

    /*CE为高，txbuf非空，发送数据包 */
    NRF_CE_1();

    /*等待发送完成中断 */
    while (NRF_Read_IRQ() != 0);

    /*读取状态寄存器的值 */
    state = SPI_NRF_ReadReg(STATUS);

    /*清除TX_DS或MAX_RT中断标志*/
    SPI_NRF_WriteReg(NRF_WRITE_REG + STATUS, state);

    SPI_NRF_WriteReg(FLUSH_TX, NOP);    //清除TX FIFO寄存器

    /*判断中断类型*/
    if (state & MAX_TX)                     //达到最大重发次数
        return MAX_TX;

    else if (state & TX_DS)                  //发送完成
        return TX_DS;
    else
        return ERROR;                 //其他原因发送失败
}

/**
  * @brief   用于从NRF的接收缓冲区中读出数据
  * @param   
  *		@arg rxBuf ：用于接收该数据的数组，外部定义	
  * @retval 
  *		@arg 接收结果
  */
uint8_t NRF_Rx_Dat(uint8_t *rxbuf) {
    uint8_t state;
    NRF_CE_1();     //进入接收状态
    /*等待接收中断*/
    while (NRF_Read_IRQ() == 0) {
        NRF_CE_0();     //进入待机状态
        /*读取status寄存器的值  */
        state = SPI_NRF_ReadReg(STATUS);

        /* 清除中断标志*/
        SPI_NRF_WriteReg(NRF_WRITE_REG + STATUS, state);

        /*判断是否接收到数据*/
        if (state & RX_DR)                                 //接收到数据
        {
            SPI_NRF_ReadBuf(RD_RX_PLOAD, rxbuf, RX_PLOAD_WIDTH);//读取数据
            SPI_NRF_WriteReg(FLUSH_RX, NOP);          //清除RX FIFO寄存器
            return RX_DR;
        } else
            return ERROR;                    //没收到任何数据
    }

    return ERROR;                    //没收到任何数据
}


/**
  * @brief  NRF配置并进入接收模式
  * @param  无
  * @retval 无
  */
void NRF_RX_Mode(void) {
    NRF_CE_0();
    SPI_NRF_WriteBuf(NRF_WRITE_REG + RX_ADDR_P0, (uint8_t *) RX_ADDRESS, RX_ADR_WIDTH);//写RX节点地址

    SPI_NRF_WriteReg(NRF_WRITE_REG + EN_AA, 0x01);       //使能通道0的自动应答
    SPI_NRF_WriteReg(NRF_WRITE_REG + EN_RXADDR, 0x01);   //使能通道0的接收地址
    SPI_NRF_WriteReg(NRF_WRITE_REG + RF_CH, CHANAL);            //设置RF通信频率
    SPI_NRF_WriteReg(NRF_WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);//选择通道0的有效数据宽度
    SPI_NRF_WriteReg(NRF_WRITE_REG + RF_SETUP, 0x0f);    //设置TX发射参数,0db增益,2Mbps,低噪声增益开启
    SPI_NRF_WriteReg(NRF_WRITE_REG + CONFIG, 0x0f);     //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式
    NRF_CE_1(); //CE为高,进入接收模式
}


/**
  * @brief  NRF配置发送模式
  * @param  无
  * @retval 无
  */
void NRF_TX_Mode(void) {
    NRF_CE_0();
    SPI_NRF_WriteBuf(NRF_WRITE_REG + TX_ADDR, (uint8_t *) TX_ADDRESS, TX_ADR_WIDTH);//写TX节点地址
    SPI_NRF_WriteBuf(NRF_WRITE_REG + RX_ADDR_P0, (uint8_t *) RX_ADDRESS, RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK

    SPI_NRF_WriteReg(NRF_WRITE_REG + EN_AA, 0x01);     //使能通道0的自动应答
    SPI_NRF_WriteReg(NRF_WRITE_REG + EN_RXADDR, 0x01); //使能通道0的接收地址
    SPI_NRF_WriteReg(NRF_WRITE_REG + SETUP_RETR, 0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
    SPI_NRF_WriteReg(NRF_WRITE_REG + RF_CH, CHANAL);       //设置RF通道为40
    SPI_NRF_WriteReg(NRF_WRITE_REG + RF_SETUP, 0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启
    SPI_NRF_WriteReg(NRF_WRITE_REG + CONFIG, 0x0e);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
    NRF_CE_1();
    delay_us(100);                        //CE要拉高一段时间才进入发送模式
}


