#ifndef ALARMS_H
#define ALARMS_H

struct Alarm {
  char title[20];
  bool isOn;
  bool daysOfWeek[7];
  byte hour;
  byte minute;

  // Function to compare the alarm time with a given time
  bool isTimeMatch(int givenHour, int givenMinute, int givenDayOfWeek) {
    // Check if the alarm is on for the given day of the week
    if (!daysOfWeek[givenDayOfWeek]) {
      return false;
    }

    // Compare the hour and minute
    if (hour == givenHour && minute == givenMinute) {
      return true;
    }

    return false;
  }

  void setTime(int newHour, int newMinute) {
    hour = newHour;
    minute = newMinute;
  }
};

#endif