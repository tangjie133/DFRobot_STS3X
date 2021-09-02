# -*- coding: utf-8 -*
'''
  @file DFRobot_STS3X.py
  @brief Define the infrastructure of DFRobot_STS3X class.
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @licence     The MIT License (MIT)
  @author [qsj.huang](qsjhyy@dfrobot.com)
  @version  V1.0
  @date  2021-8-31
  @get from https://www.dfrobot.com
  @url https://github.com/DFRobot/DFRobot_STS3X
'''
import sys
import time
import smbus
import logging
from ctypes import *


logger = logging.getLogger()
logger.setLevel(logging.INFO)  #Display all print information
#logger.setLevel(logging.FATAL)  #If you don’t want to display too many prints, only print errors, please use this option
ph = logging.StreamHandler()
formatter = logging.Formatter("%(asctime)s - [%(filename)s %(funcName)s]:%(lineno)d - %(levelname)s: %(message)s")
ph.setFormatter(formatter) 
logger.addHandler(ph)


# I2C ADDRESS
STS3X_IIC_ADDRESS_A = 0x4A   # ADDR引脚接GND
STS3X_IIC_ADDRESS_B = 0x4B   # ADDR引脚接VDD

# 传感器通信命令
STS3X_CMD_REPEATABILITY_MSB        = 0x24   # "重复性测量"配置命令高位
STS3X_CMD_REPEATABILITY_LSB_HIGH   = 0x00   # "重复性测量"配置命令低位，高重复性
STS3X_CMD_REPEATABILITY_LSB_MEDIUM = 0x0B   # "重复性测量"配置命令低位，中等重复性
STS3X_CMD_REPEATABILITY_LSB_LOW    = 0x16   # "重复性测量"配置命令低位，低重复性

STS3X_CMD_MEA_PER_2S_MSB        = 0x20   # "0.5Hz测量频率"配置命令高位
STS3X_CMD_MEA_PER_2S_LSB_HIGH   = 0x16   # "0.5Hz测量频率"配置命令低位，高重复性
STS3X_CMD_MEA_PER_2S_LSB_MEDIUM = 0x24   # "0.5Hz测量频率"配置命令低位，中等重复性
STS3X_CMD_MEA_PER_2S_LSB_LOW    = 0x2F   # "0.5Hz测量频率"配置命令低位，低重复性

STS3X_CMD_MEA_PER_1HZ_MSB        = 0x21   # "1Hz测量频率"配置命令高位
STS3X_CMD_MEA_PER_1HZ_LSB_HIGH   = 0x30   # "1Hz测量频率"配置命令低位，高重复性
STS3X_CMD_MEA_PER_1HZ_LSB_MEDIUM = 0x26   # "1Hz测量频率"配置命令低位，中等重复
STS3X_CMD_MEA_PER_1HZ_LSB_LOW    = 0x2D   # "1Hz测量频率"配置命令低位，低重复性

STS3X_CMD_MEA_PER_2HZ_MSB        = 0x22   # "2Hz测量频率"配置命令高位
STS3X_CMD_MEA_PER_2HZ_LSB_HIGH   = 0x36   # "2Hz测量频率"配置命令低位，高重复性
STS3X_CMD_MEA_PER_2HZ_LSB_MEDIUM = 0x20   # "2Hz测量频率"配置命令低位，中等重复
STS3X_CMD_MEA_PER_2HZ_LSB_LOW    = 0x2B   # "2Hz测量频率"配置命令低位，低重复性

STS3X_CMD_MEA_PER_4HZ_MSB        = 0x23   # "4Hz测量频率"配置命令高位
STS3X_CMD_MEA_PER_4HZ_LSB_HIGH   = 0x34   # "4Hz测量频率"配置命令低位，高重复性
STS3X_CMD_MEA_PER_4HZ_LSB_MEDIUM = 0x22   # "4Hz测量频率"配置命令低位，中等重复
STS3X_CMD_MEA_PER_4HZ_LSB_LOW    = 0x29   # "4Hz测量频率"配置命令低位，低重复性

STS3X_CMD_MEA_PER_10HZ_MSB        = 0x27   # "10Hz测量频率"配置命令高位
STS3X_CMD_MEA_PER_10HZ_LSB_HIGH   = 0x37   # "10Hz测量频率"配置命令低位，高重复性
STS3X_CMD_MEA_PER_10HZ_LSB_MEDIUM = 0x21   # "10Hz测量频率"配置命令低位，中等重复
STS3X_CMD_MEA_PER_10HZ_LSB_LOW    = 0x2A   # "10Hz测量频率"配置命令低位，低重复性

STS3X_CMD_MEA_PER_FETCH_DATA_MSB = 0xE0   # Fetch Data command MSB for Periodic Mode
STS3X_CMD_MEA_PER_FETCH_DATA_LSB = 0x00   # Fetch Data command LSB for Periodic Mode

STS3X_CMD_MEA_PER_BREAK_MSB = 0x30   # Break command MSB / Stop Periodic Data Acquisition Mode
STS3X_CMD_MEA_PER_BREAK_LSB = 0x93   # Break command LSB / Stop Periodic Data Acquisition Mode

STS3X_CMD_SOFT_RESET_MSB = 0x30   # Soft reset command MSB
STS3X_CMD_SOFT_RESET_LSB = 0xA2   # Soft reset command LSB

STS3X_CMD_HEATER_MSB         = 0x30   # Heater command MSB
STS3X_CMD_HEATER_LSB_ENABLE  = 0x6D   # Heater Enable command LSB
STS3X_CMD_HEATER_LSB_DISABLE = 0x66   # Heater Disabled command LSB

STS3X_CMD_GENERAL_RESET = 0x0006   # Reset command using the general call address

STS3X_CMD_READ_STATUS_MSB = 0xF3   # Read Out of status command MSB
STS3X_CMD_READ_STATUS_LSB = 0x2D   # Read Out of status command LSB

STS3X_CMD_CLEAR_STATUS_MSB = 0x30   # Clear status command MSB
STS3X_CMD_CLEAR_STATUS_LSB = 0x41   # Clear status command LSB


class DFRobot_STS3X(object):

    REPEAT_HIGH   = 0
    REPEAT_MEDIUM = 1
    REPEAT_LOW    = 2

    FREQ_2S   = 0
    FREQ_1HZ  = 1
    FREQ_2HZ  = 2
    FREQ_4HZ  = 3
    FREQ_10HZ = 4

    '''
       @brief Module init
    '''
    def __init__(self, i2c_addr=STS3X_IIC_ADDRESS_A, bus=1):
        '''初始化配置参数'''
        self._iic_addr = i2c_addr
        self._i2c = smbus.SMBus(bus)
        self._repeat = self.REPEAT_LOW
        self._freq = self.FREQ_1HZ

    '''
       @brief Initialize sensor
    '''
    def begin(self):
        self.sensor_reset()
        time.sleep(0.1)
        self._clear_sensor_status()
        time.sleep(0.1)
        # self._status = self.get_sensor_status()
        # time.sleep(0.1)
        # self.set_freq(self._freq)
        # time.sleep(0.1)

    '''
       @brief 设置重复模式
       @n 重复性设置影响测量持续时间，从而影响传感器的总能耗。
       @param repeat, 重复测量配置模式，共三种模式：REPEAT_HIGH, REPEAT_MEDIUM, REPEAT_LOW
    '''
    def set_repeat(self, repeat=REPEAT_LOW):
        self._repeat = repeat

    '''
       @brief 设置测量频率
       @param 数据测量频率，默认频率1Hz，freq: FREQ_2S, FREQ_1HZ, FREQ_2HZ, FREQ_4HZ, FREQ_10HZ
    '''
    def set_freq(self, freq=FREQ_1HZ):
        self._freq = freq
        if self._freq == self.FREQ_2S:
            CMD_MSB = STS3X_CMD_MEA_PER_2S_MSB
            if self._repeat == self.REPEAT_HIGH:
                CMD_LSB = STS3X_CMD_MEA_PER_2S_LSB_HIGH
            elif self._repeat == self.REPEAT_MEDIUM:
                CMD_LSB = STS3X_CMD_MEA_PER_2S_LSB_MEDIUM
            elif self._repeat == self.REPEAT_LOW:
                CMD_LSB = STS3X_CMD_MEA_PER_2S_LSB_LOW
            else:
                CMD_LSB = STS3X_CMD_MEA_PER_2S_LSB_MEDIUM
        elif self._freq == self.FREQ_1HZ:
            CMD_MSB = STS3X_CMD_MEA_PER_1HZ_MSB
            if self._repeat == self.REPEAT_HIGH:
                CMD_LSB = STS3X_CMD_MEA_PER_1HZ_LSB_HIGH
            elif self._repeat == self.REPEAT_MEDIUM:
                CMD_LSB = STS3X_CMD_MEA_PER_1HZ_LSB_MEDIUM
            elif self._repeat == self.REPEAT_LOW:
                CMD_LSB = STS3X_CMD_MEA_PER_1HZ_LSB_LOW
            else:
                CMD_LSB = STS3X_CMD_MEA_PER_1HZ_LSB_MEDIUM
        elif self._freq == self.FREQ_2HZ:
            CMD_MSB = STS3X_CMD_MEA_PER_2HZ_MSB
            if self._repeat == self.REPEAT_HIGH:
                CMD_LSB = STS3X_CMD_MEA_PER_2HZ_LSB_HIGH
            elif self._repeat == self.REPEAT_MEDIUM:
                CMD_LSB = STS3X_CMD_MEA_PER_2HZ_LSB_MEDIUM
            elif self._repeat == self.REPEAT_LOW:
                CMD_LSB = STS3X_CMD_MEA_PER_2HZ_LSB_LOW
            else:
                CMD_LSB = STS3X_CMD_MEA_PER_2HZ_LSB_MEDIUM
        elif self._freq == self.FREQ_4HZ:
            CMD_MSB = STS3X_CMD_MEA_PER_4HZ_MSB
            if self._repeat == self.REPEAT_HIGH:
                CMD_LSB = STS3X_CMD_MEA_PER_4HZ_LSB_HIGH
            elif self._repeat == self.REPEAT_MEDIUM:
                CMD_LSB = STS3X_CMD_MEA_PER_4HZ_LSB_MEDIUM
            elif self._repeat == self.REPEAT_LOW:
                CMD_LSB = STS3X_CMD_MEA_PER_4HZ_LSB_LOW
            else:
                CMD_LSB = STS3X_CMD_MEA_PER_4HZ_LSB_MEDIUM
        elif self._freq == self.FREQ_10HZ:
            CMD_MSB = STS3X_CMD_MEA_PER_10HZ_MSB
            if self._repeat == self.REPEAT_HIGH:
                CMD_LSB = STS3X_CMD_MEA_PER_10HZ_LSB_HIGH
            elif self._repeat == self.REPEAT_MEDIUM:
                CMD_LSB = STS3X_CMD_MEA_PER_10HZ_LSB_MEDIUM
            elif self._repeat == self.REPEAT_LOW:
                CMD_LSB = STS3X_CMD_MEA_PER_10HZ_LSB_LOW
            else:
                CMD_LSB = STS3X_CMD_MEA_PER_10HZ_LSB_MEDIUM
        else:
            CMD_MSB = STS3X_CMD_MEA_PER_1HZ_MSB
            if self._repeat == self.REPEAT_HIGH:
                CMD_LSB = STS3X_CMD_MEA_PER_1HZ_LSB_HIGH
            elif self._repeat == self.REPEAT_MEDIUM:
                CMD_LSB = STS3X_CMD_MEA_PER_1HZ_LSB_MEDIUM
            elif self._repeat == self.REPEAT_LOW:
                CMD_LSB = STS3X_CMD_MEA_PER_1HZ_LSB_LOW
            else:
                CMD_LSB = STS3X_CMD_MEA_PER_1HZ_LSB_MEDIUM
        self._write_command(CMD_MSB, [CMD_LSB])

    '''
       @brief 打开加热器
    '''
    def set_heater_on(self):
        self._write_command(STS3X_CMD_HEATER_MSB, [STS3X_CMD_HEATER_LSB_ENABLE])

    '''
       @brief 关闭加热器
    '''
    def set_heater_off(self):
        self._write_command(STS3X_CMD_HEATER_MSB, [STS3X_CMD_HEATER_LSB_DISABLE])

    '''
       @brief 中断传感器正在进行的工作，以等待我们接下来的命令
    '''
    def sensor_break(self):
        self._write_command(STS3X_CMD_MEA_PER_BREAK_MSB, [STS3X_CMD_MEA_PER_BREAK_LSB])

    '''
       @brief 将参数设置回默认值
    '''
    def sensor_reset(self):
        self.sensor_break()
        self._write_command(STS3X_CMD_SOFT_RESET_MSB, [STS3X_CMD_SOFT_RESET_LSB])

    '''
       @brief 获取并保存传感器当前所有状态
       @n 每隔一段时间之后需要先调用这个接口，才能用其他api获得传感器当前的状态
    '''
    def get_sensor_status(self):
        self._write_command(STS3X_CMD_READ_STATUS_MSB, [STS3X_CMD_READ_STATUS_LSB])
        rslt = self._read_data(3)
        if self._crc8_131(rslt) == rslt[2]:
            self._status = rslt[0]<<8 | rslt[1]

    '''
       @brief 清除传感器状态位
    '''
    def _clear_sensor_status(self):
        self._write_command(STS3X_CMD_CLEAR_STATUS_MSB, [STS3X_CMD_CLEAR_STATUS_LSB])
        self._status = 0x0000

    '''
       @brief 获取校验和状态
       @return true: checksum of last write transfer was correct
       @n      false: checksum of last write transfer failed
    '''
    def check_sum_status(self):
        ret = False
        if (self._status & 0x0001) == 0:
            ret = True
        return ret

    '''
       @brief 获取指令状态
       @return true: last command executed successfully
       @n      false: last command not processed.
    '''
    def command_status(self):
        ret = False
        if (self._status & 0x0002) == 0:
            ret = True
        return ret

    '''
       @brief 检测系统是否重置
       @return true: no reset detected since last 'clear status register' command
       @n      false: reset detected (hard reset, soft reset command or supply fail)
    '''
    def system_reset_detected(self):
        ret = False
        if (self._status & 0x0010) == 0:
            ret = True
        return ret

    '''
       @brief 温度跟踪提醒
       @return true: no alert
       @n      false: alert
    '''
    def temp_tracking_alert(self):
        ret = False
        if (self._status & 0x0400) == 0:
            ret = True
        return ret

    '''
       @brief 获取加热器状态
       @return true: Heater OFF
       @n      false: Heater ON
    '''
    def heater_status(self):
        ret = False
        if (self._status & 0x2000) == 0:
            ret = True
        return ret

    '''
       @brief 获取警报待处理状态
       @return true: no pending alerts
       @n      false: at least one pending alert
    '''
    def alert_pending_status(self):
        ret = False
        if (self._status & 0x8000) == 0:
            ret = True
        return ret

    '''
       @brief 获取当前温度，单次测量模式下
       @return 单位：℃
    '''
    def get_temperature_single(self):
        CMD_MSB = STS3X_CMD_REPEATABILITY_MSB
        if self._repeat == self.REPEAT_HIGH:
            CMD_LSB = STS3X_CMD_REPEATABILITY_LSB_HIGH
        elif self._repeat == self.REPEAT_MEDIUM:
            CMD_LSB = STS3X_CMD_REPEATABILITY_LSB_MEDIUM
        elif self._repeat == self.REPEAT_LOW:
            CMD_LSB = STS3X_CMD_REPEATABILITY_LSB_LOW
        else:
            CMD_LSB = STS3X_CMD_REPEATABILITY_LSB_MEDIUM

        self._write_command(CMD_MSB, [CMD_LSB])
        rslt = self._read_data(3)
        rawData = rslt[0]<<8 | rslt[1]
        result = 0.0
        if self._crc8_131(rslt) == rslt[2]:
            result = 175.0 * float(rawData) / 65535.0 - 45.0
        return result

    '''
       @brief 获取当前温度, 周期测量模式下
       @return 单位：℃
    '''
    def get_temperature_period(self):
        self._write_command(STS3X_CMD_MEA_PER_FETCH_DATA_MSB, [STS3X_CMD_MEA_PER_FETCH_DATA_LSB])
        rslt = self._read_data(3)
        rawData = rslt[0]<<8 | rslt[1]
        result = 0.0
        if self._crc8_131(rslt) == rslt[2]:
            result = 175.0 * float(rawData) / 65535.0 - 45.0
        return result

    '''
      @brief 计算crc8（多项式对应为0x131）的校验码（PEC）
      @param ptr 对应计算校验码的数据指针
             len 对应计算校验码的数据长度
    '''
    def _crc8_131(self, data):
        crc = 0xFF
        for i in [0, 1]:
            #logger.info(hex(data[i]))
            crc = (crc & 0xFF) ^ data[i]
            for j in range(8):
                if (crc & 0x80):
                    crc = (crc << 1) ^ 0x31
                else:
                    crc = (crc << 1)
        #logger.info(hex(crc & 0xFF))
        return crc & 0xFF

    '''
       @brief writes CMD to a sensor
       @param cmd_msb 命令高8位， 变量
              cmd_lsb 命令低八位， 数组
    '''
    def _write_command(self, cmd_msb, cmd_lsb):
        self._i2c.write_i2c_block_data(self._iic_addr, cmd_msb, cmd_lsb)
        time.sleep(0.01)

    '''
      @brief read the data from the sensor
      @param length read data length
    '''
    def _read_data(self, length):
        rslt = self._i2c.read_i2c_block_data (self._iic_addr, 0x00, length)
        time.sleep(0.01)
        return rslt
