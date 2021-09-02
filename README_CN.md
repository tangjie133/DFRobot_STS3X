# DFRobot_STS3X
* [English Version](./README.md)

STS3x-DIS是Sensirion公司最新推出的高精度数字温度传感器。其功能
包括增强的信号处理，两个独特的和用户可选择的I2C地址和
高达1 MHz的通信速度。

![正反面svg效果图](https://github.com/ouki-wang/DFRobot_Sensor/raw/master/resources/images/SEN0245svg1.png)


## Product Link （链接到英文商城）
    SKU：产品名称
   
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

* 获取实时温度<br>
* 设置测量模式<br>
* 获取传感器状态<br>

## Installation

要使用这个库，首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开示例文件夹并在文件夹中运行演示。

## Methods

```C++

  /*!
   *@brief 初始化芯片
   *@return True表示IIC沟通成功，false表示失败。
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
   *@return true: 上次写入传输校验和正确
   *@n      false: 上次写传输校验和失败
   */
  bool checkSumStatus();
  
  /*!
   *@brief 获取指令状态
   *@return true: 最后一个命令成功执行
   *@n      false: 最后一个命令未被处理
   */
  bool commandStatus();
  
  /*!
   *@brief 检测系统是否重置
   *@return true: 自上次'清除状态寄存器'命令后未检测到重置
   *@n      false: 检测到复位(硬复位、软复位命令或供应失败)
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
   *@return true: 加热器关闭
   *@n      false: 加热器开启
   */
  bool heaterStatus();
  
  /*!
   *@brief 获取警报待处理状态
   *@return true: 没有等待警报
   *@n      false: 至少有一个未决警报
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


## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32        |      √       |              |             | 
micro:bit        |      √       |              |             | 


## History

- Data 2021-09-01
- Version V1.0


## Credits

Written by(yufeng.luo@dfrobot.com), 2019. (Welcome to our [website](https://www.dfrobot.com/))





