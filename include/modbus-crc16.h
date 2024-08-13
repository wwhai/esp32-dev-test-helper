#include <stdint.h>
#include <stdio.h>

// 生成Modbus CRC16校验值
uint16_t Modbus_CRC16(const uint8_t *data, size_t length)
{
    uint16_t crc = 0xFFFF; // 初始值为0xFFFF

    for (size_t i = 0; i < length; i++)
    {
        crc ^= data[i]; // 将当前字节与CRC寄存器异或

        for (int j = 0; j < 8; j++)
        { // 对每个字节进行8次移位和异或
            if (crc & 0x0001)
            {
                crc = (crc >> 1) ^ 0xA001; // 如果最低位为1，右移后异或多项式
            }
            else
            {
                crc >>= 1; // 否则直接右移
            }
        }
    }

    return crc;
}

// 计算Modbus CRC16值并返回高字节和低字节，同时返回完整的CRC16值
uint16_t getModbusCRC16(const uint8_t *data, size_t length, uint8_t *crcHigh, uint8_t *crcLow)
{
    // 计算CRC16值
    uint16_t crc = Modbus_CRC16(data, length);

    // 拆分成高字节和低字节
    *crcLow = crc & 0xFF;         // 低字节
    *crcHigh = (crc >> 8) & 0xFF; // 高字节

    return crc;
}

int test2()
{
    // 示例数据
    uint8_t data[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x0A}; // 示例的Modbus请求数据
    size_t length = sizeof(data) / sizeof(data[0]);

    // 计算并获取CRC16值
    uint8_t crcHigh, crcLow;
    uint16_t crc = getModbusCRC16(data, length, &crcHigh, &crcLow);

    // 打印CRC16高字节和低字节
    printf("CRC16 High Byte: 0x%02X\n", crcHigh);
    printf("CRC16 Low Byte: 0x%02X\n", crcLow);

    // 打印完整的CRC16值
    printf("CRC16: 0x%04X\n", crc);

    return 0;
}
