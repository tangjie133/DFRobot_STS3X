# -*- coding: utf-8 -*
'''
  # @file get_sensor_status.py
  # @brief 获取传感器当前所有状态，并一一解析打印
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
     @brief 获取并保存传感器当前所有状态
     @n 每隔一段时间之后需要先调用这个接口，才能用其他api获得传感器当前的状态
  '''
  sensor.get_sensor_status()

  '''
     @brief 获取校验和状态
     @return true: checksum of last write transfer was correct
     @n      false: checksum of last write transfer failed
  '''
  if sensor.check_sum_status():
      print("checksum of last write transfer was correct")
  else:
      print("checksum of last write transfer failed")

  '''
     @brief 获取指令状态
     @return true: last command executed successfully
     @n      false: last command not processed.
  '''
  if sensor.command_status():
      print("last command executed successfully")
  else:
      print("last command not processed")

  '''
     @brief 检测系统是否重置
     @return true: no reset detected since last 'clear status register' command
     @n      false: reset detected (hard reset, soft reset command or supply fail)
  '''
  if sensor.system_reset_detected():
      print("no reset detected since last 'clear status register' command")
  else:
      print("reset detected")

  '''
     @brief 温度跟踪提醒
     @return true: no alert
     @n      false: alert
  '''
  if sensor.temp_tracking_alert():
      print("temperature have not been alerted")
  else:
      print("temperature have been alerted")

  '''
     @brief 获取加热器状态
     @return true: Heater OFF
     @n      false: Heater ON
  '''
  if sensor.heater_status():
      print("Heater has been closed")
  else:
      print("Heater has been opened")

  '''
     @brief 获取警报待处理状态
     @return true: no pending alerts
     @n      false: at least one pending alert
  '''
  if sensor.alert_pending_status():
      print("There is no pending alert")
  else:
      print("There is at least pending alert")

def loop():
  time.sleep(1)

if __name__ == "__main__":
  setup()
#   while True:
#     loop()
