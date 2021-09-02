/*!
 * @file setMode.ino
 * @brief 用户采样重复率（过采样，提高数据精度，过滤错误数据）、时钟延展、加热器等参数，然后以单次测量模式获取温度数据
 *
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [LuoYufeng](yufeng.luo@dfrobot.com)
 * @version  V0.1
 * @date  2021-5-10
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
     *@brief 设置重复模式
     *@param code: 在枚举变量eCode_t中选择eHigh，eMedium，eLow模式
     */
    sts.setRepeat(sts.eHigh);

    /*!
     *@brief 设置时钟延展，开启时钟延展后，当传感器未测量完成时不会发送NAK，直到测量完成时才发送数据完成之前未完成的测量命令
     *@param clockStretch: 是否打开时钟延展，true表示打开，false表示关闭
     */
    sts.setStretch(true);

    /*!
     *@brief 打开或关闭加热器，提升传感器温度，可方便内部测试
     */
    sts.setHeaterOn();
    //sts.setHeaterOff();

    /*!
     *@brief 中断传感器正在进行的工作，强制使其进入空闲模式
     */
    sts.breakSensor();

    /*!
     *@brief 将参数设置回默认值
     */
    //sts.resetSensor();
}

void loop() {
    Serial.print(sts.getTemperatureSingleC());
    Serial.println(" ℃");
    delay(1000);
}