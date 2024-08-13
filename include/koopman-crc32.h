/**
 * Copyright (C) 2024 wwhai
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Koopman CRC32查找表
uint32_t koopman_crc32_table[256];

// 初始化Koopman CRC32查找表
void init_koopman_crc32_table()
{
    uint32_t poly = 0x741B8CD7; // Koopman polynomial

    for (uint32_t i = 0; i < 256; i++)
    {
        uint32_t crc = i;
        for (uint32_t j = 0; j < 8; j++)
        {
            if (crc & 1)
            {
                crc = (crc >> 1) ^ poly;
            }
            else
            {
                crc >>= 1;
            }
        }
        koopman_crc32_table[i] = crc;
    }
}

// 计算Koopman CRC32的函数
uint32_t koopman_crc32(const uint8_t *data, size_t length)
{
    uint32_t crc = 0xFFFFFFFF; // 初始化CRC寄存器

    for (size_t i = 0; i < length; i++)
    {
        uint8_t byte = data[i];
        crc = (crc >> 8) ^ koopman_crc32_table[(crc ^ byte) & 0xFF];
    }

    return crc ^ 0xFFFFFFFF; // 取反输出
}

// Packet函数：打包数据，生成带有协议头的完整数据包
uint8_t *Packet(const uint8_t *data, size_t length, size_t *packet_size)
{
    // 协议头长度
    const size_t header_size = 6;

    // 计算CRC32
    uint32_t crc32 = koopman_crc32(data, length);

    // 计算数据包总长度
    *packet_size = header_size + length;

    // 分配数据包内存
    uint8_t *packet = (uint8_t *)malloc(*packet_size);
    if (!packet)
    {
        perror("Failed to allocate memory for packet");
        return NULL;
    }

    // 设置长度字段 (前2字节)
    packet[0] = (length >> 8) & 0xFF; // 高字节
    packet[1] = length & 0xFF;        // 低字节

    // 设置CRC32字段 (接下来的4字节)
    packet[2] = (crc32 >> 24) & 0xFF; // 高字节
    packet[3] = (crc32 >> 16) & 0xFF;
    packet[4] = (crc32 >> 8) & 0xFF;
    packet[5] = crc32 & 0xFF; // 低字节

    // 复制数据内容
    memcpy(packet + header_size, data, length);

    return packet;
}

int test1()
{
    // 初始化Koopman CRC32查找表
    init_koopman_crc32_table();

    // 示例数据
    const char *data = "Hello, world!";
    size_t length = strlen(data);

    // 打包数据
    size_t packet_size;
    uint8_t *packet = Packet((const uint8_t *)data, length, &packet_size);

    // 打印打包后的数据
    if (packet)
    {
        printf("Packet data:\n");
        for (size_t i = 0; i < packet_size; i++)
        {
            printf("%02X ", packet[i]);
        }
        printf("\n");

        // 释放分配的内存
        free(packet);
    }

    return 0;
}
