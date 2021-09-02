/*!
 * @file DFRobot_STS3X.cpp
 * @brief Define the basic structure of class DFRobot_STS3X
 * 
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [yufeng](yufeng.luo@dfrobot.com)
 * @version  V1.0
 * @date  2021-09-01
 * @url https://github.com/DFRobot/DFRobot_STS3X
 */

#include <DFRobot_STS3X.h>
DFRobot_STS3X::DFRobot_STS3X(TwoWire *pWire, uint8_t iicAddr)
{
    _pWire = pWire;
    _deviceAddr = iicAddr;
}

bool DFRobot_STS3X::begin(void)
{
    _pWire->begin();
    delay(100);
    _pWire->beginTransmission(_deviceAddr);
    if(_pWire->endTransmission() == 0){
        _repeat = eMedium;
        _stretch = true;
        resetSensor();
        delay(10);
        clearStatus();
        delay(500);
        return true;
    }
    else{
        return false;
    }
}

void DFRobot_STS3X::setRepeat(eCode_t code){
    _repeat = code;
}

void DFRobot_STS3X::setStretch(bool clockStretch){
    _stretch = clockStretch;
}

void DFRobot_STS3X::setFreq(eFreq_t freq){
    uint8_t cmd[2];
    switch (freq) {
        case e2S:
            cmd[0] = STS3X_CMD_MEA_PER_2S_NULL;
                switch (_repeat){
                    case eHigh:
                        cmd[1] = STS3X_CMD_MEA_PER_2S_HIGH;break;
                    case eMedium:
                        cmd[1] = STS3X_CMD_MEA_PER_2S_MED;break;
                    case eLow:
                        cmd[1] = STS3X_CMD_MEA_PER_2S_LOW;break;
                    default:
                        cmd[1] = STS3X_CMD_MEA_PER_2S_MED;break;
                }
            break;
        case e1Hz:
            cmd[0] = STS3X_CMD_MEA_PER_1HZ_NULL;
                switch (_repeat){
                    case eHigh:
                        cmd[1] = STS3X_CMD_MEA_PER_1HZ_HIGH;break;
                    case eMedium:
                        cmd[1] = STS3X_CMD_MEA_PER_1HZ_MED;break;
                    case eLow:
                        cmd[1] = STS3X_CMD_MEA_PER_1HZ_LOW;break;
                    default:
                        cmd[1] = STS3X_CMD_MEA_PER_1HZ_MED;break;
                }
            break;
        case e2Hz:
            cmd[0] = STS3X_CMD_MEA_PER_2HZ_NULL;
                switch (_repeat){
                    case eHigh:
                        cmd[1] = STS3X_CMD_MEA_PER_2HZ_HIGH;break;
                    case eMedium:
                        cmd[1] = STS3X_CMD_MEA_PER_2HZ_MED;break;
                    case eLow:
                        cmd[1] = STS3X_CMD_MEA_PER_2HZ_LOW;break;
                    default:
                        cmd[1] = STS3X_CMD_MEA_PER_2HZ_MED;break;
                }
            break;
        case e4Hz:
            cmd[0] = STS3X_CMD_MEA_PER_4HZ_NULL;
                switch (_repeat){
                    case eHigh:
                        cmd[1] = STS3X_CMD_MEA_PER_4HZ_HIGH;break;
                    case eMedium:
                        cmd[1] = STS3X_CMD_MEA_PER_4HZ_MED;break;
                    case eLow:
                        cmd[1] = STS3X_CMD_MEA_PER_4HZ_LOW;break;
                    default:
                        cmd[1] = STS3X_CMD_MEA_PER_4HZ_MED;break;
                }
            break;
        case e10Hz:
            cmd[0] = STS3X_CMD_MEA_PER_10HZ_NULL;
                switch (_repeat){
                    case eHigh:
                        cmd[1] = STS3X_CMD_MEA_PER_10HZ_HIGH;break;
                    case eMedium:
                        cmd[1] = STS3X_CMD_MEA_PER_10HZ_MED;break;
                    case eLow:
                        cmd[1] = STS3X_CMD_MEA_PER_10HZ_LOW;break;
                    default:
                        cmd[1] = STS3X_CMD_MEA_PER_10HZ_MED;break;
                }
            break;
        default:
            cmd[0] = STS3X_CMD_MEA_PER_1HZ_NULL;
                switch (_repeat){
                    case eHigh:
                        cmd[1] = STS3X_CMD_MEA_PER_1HZ_HIGH;break;
                    case eMedium:
                        cmd[1] = STS3X_CMD_MEA_PER_1HZ_MED;break;
                    case eLow:
                        cmd[1] = STS3X_CMD_MEA_PER_1HZ_LOW;break;
                    default:
                        cmd[1] = STS3X_CMD_MEA_PER_1HZ_MED;break;
                }
            break;
    }
    writeCommand(cmd, 2);
}

float DFRobot_STS3X::getTemperatureSingleC(){
    uint8_t cmd[2];
    switch (_stretch) {
        case true:
            cmd[0] = STS3X_CMD_CLK_STR_EN_NULL;
                switch (_repeat){
                    case eHigh:
                        cmd[1] = STS3X_CMD_CLK_STR_EN_HIGH;break;
                    case eMedium:
                        cmd[1] = STS3X_CMD_CLK_STR_EN_MED;break;
                    case eLow:
                        cmd[1] = STS3X_CMD_CLK_STR_EN_LOW;break;
                    default:
                        cmd[1] = STS3X_CMD_CLK_STR_EN_MED;break;
                }
            break;
        case false:
            cmd[0] = STS3X_CMD_CLK_STR_DIS_NULL;
                switch (_repeat){
                    case eHigh:
                        cmd[1] = STS3X_CMD_CLK_STR_DIS_HIGH;break;
                    case eMedium:
                        cmd[1] = STS3X_CMD_CLK_STR_DIS_MED;break;
                    case eLow:
                        cmd[1] = STS3X_CMD_CLK_STR_DIS_LOW;break;
                    default:
                        cmd[1] = STS3X_CMD_CLK_STR_DIS_MED;break;
                }
            break;
        default:
            cmd[0] = STS3X_CMD_CLK_STR_EN_NULL;
                switch (_repeat){
                    case eHigh:
                        cmd[1] = STS3X_CMD_CLK_STR_EN_HIGH;break;
                    case eMedium:
                        cmd[1] = STS3X_CMD_CLK_STR_EN_MED;break;
                    case eLow:
                        cmd[1] = STS3X_CMD_CLK_STR_EN_LOW;break;
                    default:
                        cmd[1] = STS3X_CMD_CLK_STR_EN_MED;break;
                }
            break;
    }
    writeCommand(cmd, 2);
    float result = 0.0;
    uint8_t buf[3];
    readData(buf, 3);
    uint16_t rawData = buf[0]<<8 | buf[1];
    uint8_t checkSum = buf[2];
    DBG(rawData);
    if (calculateCrc(buf) == checkSum) {
        result = 175.0f * (float)rawData / 65535.0f - 45.0f;
        DBG("result");
        DBG(result);
    }
    return result;
}

float DFRobot_STS3X::getTemperaturePeriodC(){
    uint8_t cmd[2] = {0xE0,0x00};
    writeCommand(cmd, 2);
    float result = 0.0;
    uint8_t buf[3];
    readData(buf, 3);
    uint16_t rawData = buf[0]<<8 | buf[1];
    uint8_t checkSum = buf[2];
    if (calculateCrc(buf) == checkSum) {
        result = 175.0f * (float)rawData / 65535.0f - 45.0f;
    }
    return result;
}

uint8_t DFRobot_STS3X::calculateCrc(uint8_t data[])
{
    uint8_t bit;
    uint8_t crc = 0xFF;
    uint8_t dataCounter = 0;

    for (; dataCounter < 2; dataCounter++)
    {
        crc ^= (data[dataCounter]);
        for (bit = 8; bit > 0; --bit)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x131;
            else
                crc = (crc << 1);
        }
    }

    return crc;
}

void DFRobot_STS3X::setHeaterOn(){
    uint8_t cmd[2];
    cmd[0] = STS3X_CMD_HEATER_NULL;
    cmd[1] = STS3X_CMD_HEATER_ENABLE;
    writeCommand(cmd, 2);
}

void DFRobot_STS3X::setHeaterOff(){
    uint8_t cmd[2];
    cmd[0] = STS3X_CMD_HEATER_NULL;
    cmd[1] = STS3X_CMD_HEATER_DISABLE;
    writeCommand(cmd, 2);
}

void DFRobot_STS3X::breakSensor(){
    uint8_t cmd[2];
    cmd[0] = STS3X_CMD_BREAK_MSB;
    cmd[1] = STS3X_CMD_BREAK_LSB;
    writeCommand(cmd, 2);
}

void DFRobot_STS3X::resetSensor(){
    breakSensor();
    uint8_t cmd[2];
    cmd[0] = STS3X_CMD_SOFT_RESET_MSB;
    cmd[1] = STS3X_CMD_SOFT_RESET_LSB;
    writeCommand(cmd, 2);
}

void DFRobot_STS3X::clearStatus(){
    uint8_t cmd[2];
    cmd[0] = STS3X_CMD_CLEAR_STATUS_MSB;
    cmd[1] = STS3X_CMD_CLEAR_STATUS_LSB;
    writeCommand(cmd, 2);
    _status = 0x0000;
}

void DFRobot_STS3X::getStatus(){
    // breakSensor();
    uint8_t cmd[2];
    cmd[0] = STS3X_CMD_READ_STATUS_MSB;
    cmd[1] = STS3X_CMD_READ_STATUS_LSB;
    writeCommand(cmd, 2);
    uint8_t buf[2];
    readData(buf, 2);
    DBG(_status);
    _status = buf[0]<<8 | buf[1];
    DBG(_status);
    delay(100);
}

bool DFRobot_STS3X::checkSumStatus(){
    if ((_status & 0x0001) == 0)
        return true;
    else
        return false;
}

bool DFRobot_STS3X::commandStatus(){
    if ((_status & 0x0002) == 0)
        return true;
    else
        return false;
}

bool DFRobot_STS3X::systemResetDetected(){
    if ((_status & 0x0010) == 0)
        return true;
    else
        return false;
}

bool DFRobot_STS3X::temTrackingAlert(){
    if ((_status & 0x0400) == 0)
        return true;
    else
        return false;
}

bool DFRobot_STS3X::heaterStatus(){
    if ((_status & 0x2000) == 0)
        return true;
    else
        return false;
}

bool DFRobot_STS3X::alertPendingStatus(){
    if ((_status & 0x8000) == 0)
        return true;
    else
        return false;
}

bool DFRobot_STS3X::checkCRC8(uint8_t *data, uint8_t Num) {
    uint8_t bit, byte, crc = 0xFF;
    // 数据位的数据经过转换应该与校验位的数据相同
    for (byte = 0; byte < Num; byte++){
        crc ^= (data[byte]);
        for (bit = 8; bit > 0; --bit){
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x31;
            else
                crc = (crc << 1);
        }
    }
    //让计算的到的crc与读到的crc作比较，来判断读到的数据是否正确
    if (crc == data[Num]) { 
        return true;
    }else {
        return false;
    }
}

void DFRobot_STS3X::writeCommand(const void *pBuf, size_t size) {
    if (pBuf == NULL) {
        DBG("pBuf ERROR!! : null pointer");
    }
    uint8_t * _pBuf = (uint8_t *)pBuf;
    _pWire->beginTransmission(_deviceAddr);
    // 将命令通过iic发给芯片
    for (uint16_t i = 0; i < size; i++) {
        _pWire->write(_pBuf[i]);
    }
    _pWire->endTransmission();
    delay(100);
}

uint8_t DFRobot_STS3X::readData(const void *pBuf, size_t size) {
    if (pBuf == NULL) {
        DBG("pBuf ERROR!! : null pointer");
    }
    uint8_t * _pBuf = (uint8_t *)pBuf;
    //读取芯片返回的数据
    _pWire->requestFrom(_deviceAddr, size);
    delay(100);
    uint8_t i = 0;
    
    for (uint8_t i = 0 ; i < size ; i++) {
        _pBuf[i] = _pWire->read();
    }
    return 1;
}