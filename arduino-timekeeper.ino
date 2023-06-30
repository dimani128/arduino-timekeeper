
#include <Wire.h>

#include <SerLCD.h> //Click here to get the library: http://librarymanager/All#SparkFun_SerLCD
SerLCD lcd; // Initialize the library with default I2C address 0x72

#include "SparkFun_Qwiic_Twist_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_Twist
TWIST twist;

#include "util.h"
#include "alarms.h"
#include "lcdKeyboard.h"

Alarm alarms[20];

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println(F("starting devices"));
  Serial.println(F("starting wire"));
  Wire.begin();
  // Set up the LCD screen and the rotary encoder

  Serial.println(F("starting lcd"));
  lcd.begin(Wire);
  lcd.clear();
  lcd.setBacklight(255, 255, 255);
  lcd.print("Hello World!");

  Serial.println(F("starting twist"));
  if (twist.begin() == false)
  {
    Serial.println(F("Twist not found. Please check wiring. Freezing..."));
    while (1);
  }
  twist.setColor(0, 0, 0);

  splash(2000);
}

void loop() {
  while (1) {}
}

Alarm createAlarmLcd()
{
  Alarm alarm;
  Serial.println("Enter Alarm Time on LCD.");
  int* time;
  numSelect(time, "Select Alarm Time", 2, ":");
  alarm.setTime(time[0], time[1]);

  Serial.println("Enter Alarm Title on LCD.");
  String title = strInput("Enter Alarm Title");
  title.trim();
  strcpy(alarm.title, title.c_str());
  // strcpy(alarm.title, "title");

  // Serial.println("Enter On/Off State (0 - Off, 1 - On):");
  // while (!Serial.available()) {}
  // byte state = Serial.parseInt();
  // alarm.isOn = (state == 1);
  alarm.isOn = true;

  Serial.println("Enter Days of the Week on LCD.");
  bool* selected;
  selected = selectDaysOfWeek();
  for (int i = 0; i < 7; i++) {
    alarm.daysOfWeek[i] = selected[i];
  }

  // Serial.print("title: " );
  // Serial.println(alarm.title);
  // for (int i = 0; i < 7; i++) {
  //   Serial.print(i);
  //   // Serial.print(" ");
  //   // Serial.print(alarm.daysOfWeek[i]);
  //   Serial.print(" ");
  //   Serial.print(alarm.daysOfWeek[i] ? "T" : "F");
  //   Serial.print(",  ");
  // }
  // Serial.println();  // Print a newline after printing the array
  // Serial.print("isOn: ");
  // Serial.println(alarm.isOn);
  // Serial.print("hour: ");
  // Serial.println(alarm.hour);
  // Serial.print("minute: ");
  // Serial.println(alarm.minute);

  return alarm;
}
