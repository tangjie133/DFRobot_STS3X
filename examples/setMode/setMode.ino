/*!
 * @file setMode.ino
 * @brief 用户设置频率，地址，加热器等参数，读取温度
 *
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [LuoYufeng](yufeng.luo@dfrobot.com)
 * @version  V0.1
 * @date  2021-5-10
 * @url https://github.com/DFRobot/DFRobot_STS3X
 */
#include "DFRobot_STS3X.h"

DFRobot_STS3X sts;


void setup(void)
{
    Serial.begin(9600);
    /*Wait for the chip to be initialized completely, and then exit*/
    while(sts.begin() != true){
        Serial.println("Failed to init chip, please check if the chip connection is fine. ");
        delay(1000);
    }
    /*!
     *@brief 设置IIC地址
     *@param addr: 通过将ADDR引脚拉高或拉低来设置IIC地址
      @n           STS3X_IIC_ADDRESS_A   0x4A
      @n           STS3X_IIC_ADDRESS_B   0x4B
     */
    sts.setAddress(STS3X_IIC_ADDRESS_A);
    
    /*!
     *@brief 设置重复模式
     *@param code: 在枚举变量eCode_t中选择eHigh，eMedium，eLow模式
     */
    sts.setRepeat(sts.eHigh);
    
    /*!
     *@brief 设置时钟延展
     *@param clockStretch: 是否打开时钟延展，true表示打开，false表示关闭
     */
    sts.setStretch(true);
    
    /*!
     *@brief 设置测量频率
     *@param freq: 在枚举变量eFreq_t中选择e2S，e1Hz，e2Hz，e4Hz，e10Hz模式
     */
    sts.setFreq(sts.e10Hz);
    
    /*!
     *@brief 打开或关闭加热器
     */
    sts.setHeaterOn();
    //sts.setHeaterOff();
    /*!
     *@brief 将参数设置回默认值
     */
    //sts.reset();
}

void loop() {
    Serial.print(sts.getTemperature());
    Serial.println(" ℃");
    delay(1000);
}