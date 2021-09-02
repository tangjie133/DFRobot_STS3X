# DFRobot_STS3X
* [English Version](./README.md)

高精度数字温度传感器集成电路
完全校准和线性化数字输出
电源电压范围宽，从2.15 V到5.5 V
I2C接口，通讯速度可达1
MHz和两个用户可选地址
精度可达0.1°C
启动和测量时间非常快
Tiny 8-pin DFN包
NIST可追溯性

![正反面svg效果图](https://github.com/cdjq/DFRobot_Sensor/raw/master/resources/images/SEN0245svg1.png)

## Product Link (https://www.dfrobot.com/)
    SKU：产品名称


## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)


## Summary

* 获取实时温度
* 设置测量模式
* 获取传感器状态


## Installation

使用库，首先下载库文件，将其粘贴到指定的目录中，然后打开Examples文件夹并在该文件夹中运行演示。

## Methods

```python

    '''
       @brief 初始化传感器
    '''
    def begin(self)

    '''
       @brief 设置重复模式
       @n 重复性设置影响测量持续时间，从而影响传感器的总能耗。
       @param repeat, 重复测量配置模式，共三种模式：REPEAT_HIGH, REPEAT_MEDIUM, REPEAT_LOW
    '''
    def set_repeat(self, repeat=REPEAT_LOW)

    '''
       @brief 设置测量频率
       @param 数据测量频率，默认频率1Hz，freq: FREQ_2S, FREQ_1HZ, FREQ_2HZ, FREQ_4HZ, FREQ_10HZ
    '''
    def set_freq(self,  freq=FREQ_1HZ)

    '''
       @brief 打开加热器
    '''
    def set_heater_on(self)

    '''
       @brief 关闭加热器
    '''
    def set_heater_off(self)

    '''
       @brief 中断传感器正在进行的工作，以等待我们接下来的命令
    '''
    def sensor_break(self)

    '''
       @brief 将参数设置回默认值
    '''
    def sensor_reset(self)

    '''
       @brief 获取并保存传感器当前所有状态
       @n 每隔一段时间之后需要先调用这个接口，才能用其他api获得传感器当前的状态
    '''
    def get_sensor_status(self)

    '''
       @brief 获取校验和状态
       @return true: 上次写入传输校验和正确
       @n      false: 上次写传输校验和失败
    '''
    def check_sum_status(self)

    '''
       @brief 获取指令状态
       @return true: 最后一个命令成功执行
       @n      false: 最后一个命令未被处理
    '''
    def command_status(self)

    '''
       @brief 检测系统是否重置
       @return true: 自上次'清除状态寄存器'命令后未检测到重置
       @n      false: 检测到复位(硬复位、软复位命令或供应失败)
    '''
    def system_reset_detected(self)

    '''
       @brief 温度跟踪提醒
       @return true: 无提醒
       @n      false: 当前存在提醒
    '''
    def temp_tracking_alert(self)

    '''
       @brief 获取加热器状态
       @return true: 加热器关闭
       @n      false: 加热器打开
    '''
    def heater_status(self)

    '''
       @brief 获取警报待处理状态
       @return true: 没有等待警报
       @n      false: 至少有一个未决警报
    '''
    def alert_pending_status(self)

    '''
       @brief 获取当前温度，单次测量模式下
       @return 单位：℃
    '''
    def get_temperature_single(self)

    '''
       @brief 获取当前温度, 周期测量模式下
       @return 单位：℃
    '''
    def get_temperature_period(self)



```

## Compatibility

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## History

- data 2021-09-01
- version V1.0


## Credits

Written by qsjhyy(qsj.huang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))
