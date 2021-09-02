# -*- coding: utf-8 -*
'''
  # @file get_sensor_status.py
  # @brief 配置传感器相关测量参数，然后单次读取测量数据
  # @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  # @licence     The MIT License (MIT)
  # @author      [qsj](qsj.huang@dfrobot.com)
  # @version  V0.1
  # @date  2021-08-31
  # @get from https://www.dfrobot.com
  # @url https://github.com/DFRobot/DFRobot_STS3X
'''
from __future__ import print_function
import sys
sys.path.append('../')
from DFRobot_STS3X import *

# 根据ADDR引脚拉高或拉低来确定IIC地址
# ADDR引脚拉低： STS3X_IIC_ADDRESS_A   0x4A
# ADDR引脚拉高： STS3X_IIC_ADDRESS_B   0x4B
sensor = DFRobot_STS3X(i2c_addr = STS3X_IIC_ADDRESS_A,bus = 1)


def setup():
  sensor.begin()
  print("sensor begin successfully!!!")

  '''
     @brief 设置重复模式
     @n 重复性设置影响测量持续时间，从而影响传感器的总能耗。
     @param repeat, 重复测量配置模式，共三种模式： REPEAT_HIGH, REPEAT_MEDIUM, REPEAT_LOW
  '''
  sensor.set_repeat(sensor.REPEAT_LOW)

  '''
     @brief 打开或关闭加热器
  '''
  sensor.set_heater_on()
  sensor.set_heater_off()

  '''
     @brief 中断传感器正在进行的工作，进入空闲状态以等待我们接下来的命令，单次测量需传感器处于空闲状态
  '''
  sensor.sensor_break()

  '''
     @brief 将参数设置回默认值
  '''
  # sensor.sensor_reset()

def loop():
  ''' Read the temperature data of a single sensor measurement, unit: °C '''
  temperature = sensor.get_temperature_single()
  print("single measurement celsius = %0.2f C\n" %temperature)

  time.sleep(1)

if __name__ == "__main__":
  setup()
  while True:
    loop()
