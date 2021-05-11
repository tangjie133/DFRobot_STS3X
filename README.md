# DFRobot_STS3X
The STS3x-DIS is Sensirion’s new high accuracy digital temperature sensor.Its functionality <br>
includes enhanced signal processing, two distinctive and user selectable I2C addresses and <br>
communication speeds of up to 1 MHz. <br>

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

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++

  /*!
   *@brief Init chip 
   *@return True means IIC communication succeeds, false means it fails.
   */
  bool begin(void);
  /*!
   *@brief 设置IIC地址
   *@param addr: 通过将ADDR引脚拉高或拉低来设置IIC地址
    @n           STS3X_IIC_ADDRESS_A   0x4A
    @n           STS3X_IIC_ADDRESS_B   0x4B
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
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32        |      √       |              |             | 
micro:bit        |      √       |              |             | 


## History

- Data 2021-5-11
- Version V0.1


## Credits

Written by(yufeng.luo@dfrobot.com), 2019. (Welcome to our [website](https://www.dfrobot.com/))





