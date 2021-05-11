/*!
 * @file getStatus.ino
 * @brief Show curren temperature of chip
 * @n Experiment phenomenon: 由用户自行设置初始时间，并从芯片获取实时时间和温度
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
    sts.getStatus()
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