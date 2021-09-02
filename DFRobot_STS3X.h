/*!
 * @file DFRobot_STS3X.h
 * @brief Realize the specific function of class DFRobot_STS3X
 * 
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [yufeng](yufeng.luo@dfrobot.com)
 * @version  V1.0
 * @date  2021-09-01
 * @url https://github.com/DFRobot/DFRobot_STS3X
 */

#ifndef _DFRobot_STS3X_H
#define _DFRobot_STS3X_H

#include "Arduino.h"
#include <Wire.h>


/*I2C ADDRESS*/
#define STS3X_IIC_ADDRESS_A                0x4A   // addr引脚接GND时的IIC通信地址
#define STS3X_IIC_ADDRESS_B                0x4B   // addr引脚接VCC时的IIC通信地址

//The repeatability setting influences the measurement duration and thus the overall energy consumption of the sensor
// 单次测量模式过采样（重复性）设置
#define STS3X_CMD_CLK_STR_EN_NULL          0x2C
#define STS3X_CMD_CLK_STR_EN_HIGH          0x06
#define STS3X_CMD_CLK_STR_EN_MED           0x0D
#define STS3X_CMD_CLK_STR_EN_LOW           0x10

#define STS3X_CMD_CLK_STR_DIS_NULL         0x24
#define STS3X_CMD_CLK_STR_DIS_HIGH         0x00
#define STS3X_CMD_CLK_STR_DIS_MED          0x0B
#define STS3X_CMD_CLK_STR_DIS_LOW          0x16

// 周期测量模式频率设置
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

// 周期读取命令的MSB位
#define STS3X_CMD_READ_FETCH_DATA          0xE0

// 传感器停止工作命令，使传感器进入空闲状态
#define STS3X_CMD_BREAK_MSB                0x30
#define STS3X_CMD_BREAK_LSB                0x93

// 软复位命令
#define STS3X_CMD_SOFT_RESET_MSB           0x30
#define STS3X_CMD_SOFT_RESET_LSB           0xA2

// 加热器使能/失能命令
#define STS3X_CMD_HEATER_NULL              0x30
#define STS3X_CMD_HEATER_ENABLE            0x6D
#define STS3X_CMD_HEATER_DISABLE           0x66

// 通用复位命令
#define STS3X_CMD_GENERAL_RESET            0x0006

// 读传感器状态命令
#define STS3X_CMD_READ_STATUS_MSB          0xF3
#define STS3X_CMD_READ_STATUS_LSB          0x2D

// 清除传感器状态命令
#define STS3X_CMD_CLEAR_STATUS_MSB         0x30
#define STS3X_CMD_CLEAR_STATUS_LSB         0x41

//Open this macro to see the detailed running process of the program 
#define ENABLE_DBG

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
    DFRobot_STS3X(TwoWire *pWire = &Wire, uint8_t iicAddr = STS3X_IIC_ADDRESS_A);

    /*!
     *@brief Init chip 
     *@return True means IIC communication succeeds, false means it fails.
     */
    bool begin(void);

    /*!
     *@brief 设置传感器重复测量速率（模式）
     *@n 重复性设置影响测量持续时间，从而影响传感器的总能耗。
     *@param code: 在枚举变量eCode_t中选择eHigh，eMedium，eLow模式
     */
    void setRepeat(eCode_t code);

    /*!
     *@brief 设置时钟延展，开启时钟延展后，当传感器未测量完成时不会发送NAK，直到测量完成时才发送数据完成之前未完成的测量命令
     *@param clockStretch: 是否打开时钟延展，true表示打开，false表示关闭
     */
    void setStretch(bool clockStretch);

    /*!
     *@brief 设置测量频率，开启传感器周期测量模式（设置周期测量频率，相当于发送开启周期测量模式的指令）
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
     *@brief 中断传感器正在进行的工作，强制使其进入空闲模式
     */
    void breakSensor();

    /*!
     *@brief 将参数设置回默认值
     */
    void resetSensor();

    /*!
     *@brief 获取并保存传感器当前所有状态
     *@n 每隔一段时间之后需要先调用这个接口，才能用其他api获得传感器当前的状态
     */
    void getStatus();

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
     *@brief 单次测量模式下，获取当前温度，注：需保证传感器处于空闲状态，可以调用相关api：breakSensor()
     *@return 单位：℃
     */
    float  getTemperatureSingleC();

    /*!
     *@brief 周期测量模式下，获取当前温度，注：需提前设置采样频率，可以调用相关api：setFreq(eFreq_t freq)
     *@return 单位：℃
     */
    float  getTemperaturePeriodC();


protected:
    /*!
     *@brief 清除传感器状态寄存器当前所有状态
     */
    void clearStatus();

    /*!
     *@brief 与传感器进行IIC通信
     */
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

  /**
   * @brief 计算数据对应的CRC.
   * @param data  数据位的数据.
   * @return      CRC计算结果.
   */
    uint8_t calculateCrc(uint8_t data[]);

    TwoWire *_pWire;
    uint8_t _deviceAddr;
    uint8_t _repeat;
    uint8_t _stretch;
    uint16_t _status;
    //uint8_t _checkSum;
};

#endif
