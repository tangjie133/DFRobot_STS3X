/*!
 * @file getStatus.ino
 * @brief 获取传感器当前所有状态，并一一解析打印
 *
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [LuoYufeng](yufeng.luo@dfrobot.com)
 * @version  V0.1
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
     *@brief 获取并保存传感器当前所有状态
     *@n 每隔一段时间之后需要先调用这个接口，才能用其他api获得传感器当前的状态
     */
    sts.getStatus();

    /*!
     *@brief 获取校验和状态
     *@return true: checksum of last write transfer was correct
     *@n      false: checksum of last write transfer failed
     */
    if(sts.checkSumStatus() == true)
        Serial.println("checksum of last write transfer was correct");
    else
        Serial.println("checksum of last write transfer failed");

    /*!
     *@brief 获取指令状态
     *@return true: last command executed successfully
     *@n      false: last command not processed.
     */
    if(sts.commandStatus() == true)
        Serial.println("last command executed successfully");
    else
        Serial.println("last command not processed");

    /*!
     *@brief 检测系统是否重置
     *@return true: no reset detected since last 'clear status register' command
     *@n      false: reset detected (hard reset, soft reset command or supply fail)
     */
    if(sts.systemResetDetected() == true)
        Serial.println("no reset detected since last 'clear status register' command");
    else
        Serial.println("reset detected");

    /*!
     *@brief 温度跟踪提醒
     *@return true: no alert
     *@n      false: alert
     */
    if(sts.temTrackingAlert() == true)
        Serial.println("temperature have not been alerted");
    else
        Serial.println("temperature have been alerted");

    /*!
     *@brief 获取加热器状态
     *@return true: Heater OFF
     *@n      false: Heater ON
     */
    if(sts.heaterStatus() == true)
        Serial.println("Heater has been closed");
    else
        Serial.println("Heater has been opened");

    /*!
     *@brief 获取警报待处理状态
     *@return true: no pending alerts
     *@n      false: at least one pending alert
     */
    if(sts.alertPendingStatus() == true)
        Serial.println("There is no pending alert");
    else
        Serial.println("There is at least pending alert");
}

void loop() {
    
}