/*!
 * @file DFRobot_STS3X.h
 * @brief Define the basic structure of class DFRobot_STS3X 
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [yufeng](yufeng.luo@dfrobot.com)
 * @version  V1.0
 * @date  2021-2-23
 * @url https://github.com/DFRobot/DFRobot_STS3X
 */

#ifndef _DFRobot_STS3X_H
#define _DFRobot_STS3X_H

#include "Arduino.h"
#include <Wire.h>


/*I2C ADDRESS*/
#define STS3X_IIC_ADDRESS_A                0x4A
#define STS3X_IIC_ADDRESS_B                0x4B


//The repeatability setting influences the measurement duration and thus the overall energy consumption of the sensor
#define STS3X_CMD_CLK_STR_EN_NULL          0x2C
#define STS3X_CMD_CLK_STR_EN_HIGH          0x06
#define STS3X_CMD_CLK_STR_EN_MED           0x0D
#define STS3X_CMD_CLK_STR_EN_LOW           0x10

#define STS3X_CMD_CLK_STR_DIS_NULL         0x24
#define STS3X_CMD_CLK_STR_DIS_HIGH         0x00
#define STS3X_CMD_CLK_STR_DIS_MED          0x0B
#define STS3X_CMD_CLK_STR_DIS_LOW          0x16

#define STS3X_CMD_MEA_PER_2S_NULL          0x20
#define STS3X_CMD_MEA_PER_2S_HIGH          0x16
#define STS3X_CMD_MEA_PER_2S_MED           0x24
#define STS3X_CMD_MEA_PER_2S_LOW           0x2F

#define STS3X_CMD_MEA_PER_1HZ_NULL         0x21
#define STS3X_CMD_MEA_PER_1HZ_HIGH         0x30
#define STS3X_CMD_MEA_PER_1HZ_MED          0x26
#define STS3X_CMD_MEA_PER_1HZ_LOW          0x2D

#define STS3X_CMD_MEA_PER_2HZ_NULL         0x22
#define STS3X_CMD_MEA_PER_2HZ_HIGH         0x36
#define STS3X_CMD_MEA_PER_2HZ_MED          0x20
#define STS3X_CMD_MEA_PER_2HZ_LOW          0x2B

#define STS3X_CMD_MEA_PER_4HZ_NULL         0x23
#define STS3X_CMD_MEA_PER_4HZ_HIGH         0x34
#define STS3X_CMD_MEA_PER_4HZ_MED          0x22
#define STS3X_CMD_MEA_PER_4HZ_LOW          0x29

#define STS3X_CMD_MEA_PER_10HZ_NULL        0x27
#define STS3X_CMD_MEA_PER_10HZ_HIGH        0x37
#define STS3X_CMD_MEA_PER_10HZ_MED         0x21
#define STS3X_CMD_MEA_PER_10HZ_LOW         0x2A

#define STS3X_CMD_READ_FETCH_DATA          0xE0

#define STS3X_CMD_SOFT_RESET_MSB           0x30
#define STS3X_CMD_SOFT_RESET_LSB           0xA2
#define STS3X_CMD_HEATER_NULL              0x30
#define STS3X_CMD_HEATER_ENABLE            0x6D
#define STS3X_CMD_HEATER_DISABLE           0x66

#define STS3X_CMD_GENERAL_RESET            0x0006
#define STS3X_CMD_READ_STATUS_MSB          0xF3
#define STS3X_CMD_READ_STATUS_LSB          0x2D
#define STS3X_CMD_CLEAR_STATUS_MSB         0x30
#define STS3X_CMD_CLEAR_STATUS_LSB         0x41

//Open this macro to see the detailed running process of the program 
//#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif




class DFRobot_STS3X
{
public:

    typedef enum{
        eHigh,
        eMedium,
        eLow
    }eCode_t;
    
    
    typedef enum{
        e2S,
        e1Hz,
        e2Hz,
        e4Hz,
        e10Hz
    }eFreq_t;
    
    /**
     * @brief Constructor 
     * @param Input Wire address
     */
    DFRobot_STS3X(TwoWire *pWire = &Wire){_pWire = pWire;};
    ~DFRobot_STS3X();
    /*!
     *@brief Init chip 
     *@return True means IIC communication succeeds, false means it fails.
     */
    bool begin(void);
    /*!
     *@brief 设置IIC地址
     *@param addr: 通过将ADDR引脚拉高或拉低来设置IIC地址
     *@n           STS3X_IIC_ADDRESS_A   0x4A
     *@n           STS3X_IIC_ADDRESS_B   0x4B
     */
    void setAddress(uint8_t addr);
    
    /*!
     *@brief 设置重复模式
     *@param code: 在枚举变量eCode_t中选择eHigh，eMedium，eLow模式
     */
    void setRepeat(eCode_t code);
    
    /*!
     *@brief 设置时钟延展
     *@param clockStretch: 是否打开时钟延展，true表示打开，false表示关闭
     */
    void setStretch(bool clockStretch);
    
    /*!
     *@brief 设置测量频率
     *@param freq: 在枚举变量eFreq_t中选择e2S，e1Hz，e2Hz，e4Hz，e10Hz模式
     */
    void setFreq(eFreq_t freq);
    
    /*!
     *@brief 打开加热器
     */
    void setHeaterOn();
    
    /*!
     *@brief 关闭加热器
     */
    void setHeaterOff();
    
    /*!
     *@brief 将参数设置回默认值
     */
    void reset();
    
    /*!
     *@brief 获取校验和状态
     *@return true: checksum of last write transfer was correct
     *@n      false: checksum of last write transfer failed
     */
    bool checkSumStatus();
    
    /*!
     *@brief 获取指令状态
     *@return true: last command executed successfully
     *@n      false: last command not processed.
     */
    bool commandStatus();
    
    /*!
     *@brief 检测系统是否重置
     *@return true: no reset detected since last 'clear status register' command
     *@n      false: reset detected (hard reset, soft reset command or supply fail)
     */
    bool systemResetDetected();
    
    /*!
     *@brief 温度跟踪提醒
     *@return true: no alert
     *@n      false: alert
     */
    bool temTrackingAlert();
    
    /*!
     *@brief 获取加热器状态
     *@return true: Heater OFF
     *@n      false: Heater ON
     */
    bool heaterStatus();
    
    /*!
     *@brief 获取警报待处理状态
     *@return true: no pending alerts
     *@n      false: at least one pending alert
     */
    bool alertPendingStatus();
    /*!
     *@brief 获取当前温度
     *@return 单位：℃
     */
    float  getTemperature();
    float  getTemperatureC();
    

protected:
    virtual void writeCommand(const void *pBuf, size_t size);
    virtual uint8_t readData(const void* pBuf, size_t size);
    
private:
  /**
   * @brief 检测返回的CRC，是否与数据位的两个数据校验出的CRC8相等.
   * @param data  数据位的数据.
   * @param Num   需要检验数据的个数.
   * @return      返回0表示验证正确，返回其他值表示验证为错误.
   */
    bool   checkCRC8(uint8_t *cmd, uint8_t Num);
    void   getStatus();
    
    TwoWire *_pWire;
    uint8_t calculateCrc(uint8_t data[]);
    uint8_t _deviceAddr = STS3X_IIC_ADDRESS_B;
    uint8_t _repeat;
    uint8_t _stretch;
    uint16_t status;
    //uint8_t _checkSum;
};

#endif
