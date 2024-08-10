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
const int buzzerPin = 14;
const int delayInterval = 60;

void dot()
{
    tone(buzzerPin, 440, delayInterval);
}

void dash()
{
    tone(buzzerPin, 440, delayInterval * 3);
}
void resetBeep()
{
    tone(buzzerPin, 440, delayInterval * 5);
}
void pongBeep()
{
    dot();
    delay(500);
    dot();
    delay(500);
    dot();
}
void warnBeep()
{
    dot();
    delay(500);
    dot();
    delay(500);
    dot();
}