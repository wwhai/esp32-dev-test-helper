// Copyright (C) 2024 wwhai
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

unsigned char modbus0103[] = {0x01, 0x03, 0x00, 0x01, 0x12, 0x34, 0x7d, 0x19};
#include <stdint.h>
// uint8_t myData[5] = {0x01, 0x03, 0x00, 0x01, 0x00};
// uint16_t crcValue = calculateModbusCRC(myData, 5);
uint16_t calculateModbusCRC(uint8_t *data, uint16_t length)
{
    uint16_t crc = 0xFFFF;
    for (uint16_t pos = 0; pos < length; pos++)
    {
        crc ^= (uint16_t)data[pos]; // XOR byte into least sig. byte of crc

        for (uint8_t i = 8; i != 0; i--)
        { // Loop over each bit
            if ((crc & 0x0001) != 0)
            {              // If the LSB is set
                crc >>= 1; // Shift right and XOR 0xA001
                crc ^= 0xA001;
            }
            else
            {              // Else LSB is not set
                crc >>= 1; // Just shift right
            }
        }
    }
    return crc;
}
