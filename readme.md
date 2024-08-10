<!--
 Copyright (C) 2024 wwhai

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as
 published by the Free Software Foundation, either version 3 of the
 License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
-->

# 开发小助手
![1723272314036](image/readme/1723272314036.png)
## 简介
这是一个基于ESP32开发的小助手，主要用于串口开发过程中设备和协议的模拟场景。比如此时需要对接一个Modbus传感器的时候，手里没有设备，可以用小助手模拟一些报文来进行测试。让我们便携测试，精力专注上位机开发。
## 功能
当前版本很简单，支持3个模式。
### ECHO 模式
上位机发什么过来，小助手就回什么过去。
### Modbus从机模式
小助手作为modbus从机模式，接收外部请求，返回模拟数据。
### GPS模式
小助手会一直向外发送标准NEMA格式的GPS位置信息。
### 自定义字节发送
配置一个自定义字节，按照一定的时间间隔持续向上位机发送。

## 模式切换
小助手支持2个模式：工作模式和配置模式。均使用AT指令来切换。

## AT指令集
### 指令格式
请求:
```sh
AT+${指令}\r\n
```
返回
```sh
AT+${指令}\r\n
DATA\r\n
\r\n
```
### 指令表
| 指令                | 参数                   | 返回值                             | 说明                                 |
| ------------------- | ---------------------- | ---------------------------------- | ------------------------------------ |
| `AT+INFO\r\n`       | Void                   | `AT+INFO\r\n[version],[state]\r\n` | 查看固件信息                         |
| `AT+RESET\r\n`      | Void                   | `AT+RESET\r\nOK\r\n`               | 重启指令                             |
| `AT+ECHO[echo]\r\n` | Void                   | `AT+ECHO\r\n[echo]\r\n`            | 回显                                 |
| `AT+PING\r\n`       | Void                   | `AT+PING\r\nOK\r\n`                | 测试设备工作状态，会发出三声“滴滴滴” |
| `AT+M2[id]\r\n`     | [SlaverId]             | `AT+M2?id\r\nOK\r\n`               | Modbus从机模式配置ID                 |
| `AT+M3[hex]\r\n`    | [自定义字节内容(数组)] | `AT+M3?hex\r\nOK\r\n`              | 配置自定义指令                       |