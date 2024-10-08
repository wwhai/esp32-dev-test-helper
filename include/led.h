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
#include <Arduino.h>

const int ledPin = 27;
// 闪烁LED
void ledBlink(int times)
{
    for (size_t i = 0; i < times; i++)
    {
        digitalWrite(ledPin, HIGH);
        delay(100);
        digitalWrite(ledPin, LOW);
        delay(100);
    }
}
void ledBlink(int times, int delayTimeMills)
{
    for (size_t i = 0; i < times; i++)
    {
        digitalWrite(ledPin, HIGH);
        delay(delayTimeMills);
        digitalWrite(ledPin, LOW);
        delay(delayTimeMills);
    }
}