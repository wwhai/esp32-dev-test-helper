#include <Arduino.h>
#include "buzzer.h"
#include "led.h"
#include <WiFi.h>
#include "user-uart-protocol.h"
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  resetBeep();
}
//
String cmd;
int Mode = 2;
bool inWork = true;
//
void loop()
{
  ledBlink(2, 50);
  cmd = "";
  if (Serial.available())
  {
    cmd = Serial.readStringUntil('\n');
  }
  if (cmd.startsWith("AT+WORK"))
  {
    inWork = true;
    Serial.write("# Change to Working Mode.");
    return;
  }
  if (cmd.startsWith("AT+CFG"))
  {
    inWork = false;
    Serial.write("# Change to Config Mode.");
    return;
  }
  if (inWork)
  {
    // Echo Mode
    if (Mode == 1)
    {
    }
    // 自定义 模式
    if (Mode == 3)
    {
    }

    // 串口模式
    if (Mode == 2)
    {
      for (size_t i = 0; i < 30; i++)
      {
        for (size_t j = 0; j < 18; j++)
        {
          Serial.write(UserUartPacket[i][j]);
        }
      }
      return;
    }
  }

  if (!inWork)
  {
    if (cmd.startsWith("AT+ECHO"))
    {
      Serial.write(cmd.c_str());
      return;
    }
    if (cmd.startsWith("AT+PING"))
    {
      pongBeep();
      return;
    }
    if (cmd.startsWith("AT+RESET"))
    {
      ESP.restart();
      return;
    }
    if (cmd.startsWith("AT+INFO"))
    {
      char info[30];
      sprintf(info, "# Cpu Frequency: %d MHz\n", ESP.getCpuFreqMHz());
      Serial.write(info);
      sprintf(info, "# Chip Cores: %d\n", ESP.getChipCores());
      Serial.write(info);
      sprintf(info, "# Chip Revision: %d\n", ESP.getChipRevision());
      Serial.write(info);
      sprintf(info, "# Free Heap: %d\n", ESP.getFreeHeap());
      Serial.write(info);
      return;
    }
    if (cmd.startsWith("AT+M1"))
    {
      Mode = 1;
      Serial.printf("# Change to ECHO Mode");
      return;
    }
    if (cmd.startsWith("AT+M2"))
    {
      Mode = 2;
      cmd.trim();
      String id = cmd.substring(5);
      if (id.toInt() > 0 && id.toInt() < 256)
      {
        Serial.printf("# Change to Modbus Slaver Mode, SlaverID:%s", id);
      }
      else
      {
        Serial.printf("# Invalid Modbus SlaverID:%s", id);
      }
      return;
    }
    if (cmd.startsWith("AT+M3"))
    {
      Mode = 3;
      cmd.trim();
      String hexString = cmd.substring(5);
      Serial.printf("# Change to USER Packet Mode: %s", hexString);
      if (hexString.length() > 0)
      {
        Serial.printf("# Change to User Mode, Packet:%s", hexString);
      }
      else
      {
        Serial.printf("# Invalid User Packet:%s", hexString);
      }
      return;
    }
  }
}
