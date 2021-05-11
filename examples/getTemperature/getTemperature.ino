/*!
 * @file getTemperature.ino
 * @brief Show curren temperature of chip
 * @n Experiment phenomenon: 由用户自行设置初始时间，并从芯片获取实时时间和温度
 *
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [LuoYufeng](yufeng.luo@dfrobot.com)
 * @version  V0.1
 * @date  2021-2-23
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
}

void loop() {
    Serial.print(sts.getTemperatureC());
    Serial.println(" ℃");
    delay(1000);
}