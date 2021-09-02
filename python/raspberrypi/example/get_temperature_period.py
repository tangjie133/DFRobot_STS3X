# -*- coding: utf-8 -*
'''
  # @file get_sensor_status.py
  # @brief 获取传感器周期测量模式下，测量的温度数据
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
     @brief 设置测量频率，要使用周期测量模式，必需调用此api
     @param 数据测量频率，默认频率1Hz，freq: FREQ_2S, FREQ_1HZ, FREQ_2HZ, FREQ_4HZ, FREQ_10HZ
  '''
  sensor.set_freq(sensor.FREQ_1HZ)


def loop():
  ''' Read the temperature data periodically measured by the sensor, unit: °C '''
  temperature = sensor.get_temperature_period()
  print("period measurement celsius = %0.2f C\n" %temperature)

  time.sleep(1)


if __name__ == "__main__":
  setup()
  while True:
    loop()
