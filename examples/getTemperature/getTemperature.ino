/*!
 * @file getTemperature.ino
 * @brief 开启传感器周期测量模式（设置周期测量频率，相当于发送开启周期测量模式的指令），
 * @n 获取传感器周期测量模式下，测量的温度数据
 * 
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [LuoYufeng](yufeng.luo@dfrobot.com)
 * @version  V1.0
 * @date  2021-9-01
 * @url https://github.com/DFRobot/DFRobot_STS3X
 */
#include "DFRobot_STS3X.h"

/*!
 * 根据ADDR引脚拉高或拉低来确定IIC地址
 * ADDR引脚拉低： STS3X_IIC_ADDRESS_A   0x4A
 * ADDR引脚拉高： STS3X_IIC_ADDRESS_B   0x4B
 */
DFRobot_STS3X sts(&Wire, STS3X_IIC_ADDRESS_A);


void setup(void)
{
    Serial.begin(9600);
    /*Wait for the chip to be initialized completely, and then exit*/
    while(sts.begin() != true){
        Serial.println("Failed to init chip, please check if the chip connection is fine. ");
        delay(1000);
    }

    /*!
     *@brief 设置测量频率
     *@param freq: 在枚举变量eFreq_t中选择e2S，e1Hz，e2Hz，e4Hz，e10Hz模式
     */
    sts.setFreq(sts.e10Hz);

}

void loop() {
    Serial.print(sts.getTemperaturePeriodC());
    Serial.println(" ℃");
    delay(1000);
}