#ifndef UTIL_H
#define UTIL_H

const char* VERSION = "0.0.0-alpha";

void splash(int time=1000)
{
  lcd.clear();
  lcd.println("Timekeeper");
  lcd.print("v");
  lcd.println(VERSION);
  delay(time);
}

char* formatTime(int hour, int minute, int second = -1, int millisecond = -1) {
  static char buffer[9];  // Buffer to hold the formatted time string (hh:mm:ss)

  if (second == -1) {
    sprintf(buffer, "%02d:%02d", hour, minute);
  }
  else if (millisecond == -1) {
    sprintf(buffer, "%02d:%02d:%02d", hour, minute, second);
  }
  else {
    sprintf(buffer, "%02d:%02d:%02d.%03d", hour, minute, second, millisecond);
  }

  return buffer;
}

void copyBoolListToIntList(const bool* boolList, int* intList, int length) {
  for (int i = 0; i < length; i++) {
    intList[i] = boolList[i] ? 1 : 0;
  }
}

void countToXY(int input, int width, int& first, int& second) {
  // Calculate the first output number by dividing the input by `width` and rounding down
  first = (input / width) % 2;
  
  // Calculate the second output number by taking the input modulus `width`
  second = input % width;
}


int menu(char* title, char* options[], int numOptions)
{
  lcd.clear();

  int lastCount = -1;

  int min = 0;
  int max = 2;

  twist.setCount(0);

  while (true) {
    // Update the rotary encoder count
    int count = twist.getCount();

    // Only update the selection if the count has changed
    if (count != lastCount) {
      // Serial.print(twist.getCount());
      // Serial.print(" ");
      // Serial.println(count);
      // Wrap the selection around if it goes out of bounds
      if (count < 0)
      {
        twist.setCount(numOptions - 1);
        count = numOptions - 1;
        continue;
      }
      else if (count > numOptions - 1)
      {
        twist.setCount(0);
        count = 0;
        continue;
      }
      if (count < min)
      {
        min = count;
        max = min + 2;
      }
      else if (count > max)
      {
        max = count;
        min = max - 2;
      }

      if (max > numOptions)
      {
        max = numOptions;
      }

      lcd.clear();
      
      // Display the menu options
      for (int i = min; i <= max; i++)
      {
        int rowNum = 1 + i - min;
        lcd.setCursor(2, rowNum);
        lcd.print(options[i]);
      }

      // Clear the old selection and highlight the new one
      for (int i = min; i <= max; i++)
      {
        int rowNum = 1 + i - min;
        lcd.setCursor(0, rowNum);
        if (i == count) {
          lcd.print(">");
        } else {
          lcd.print(" ");
        }
      }

      // Display the menu title
      lcd.setCursor(0, 0);
      lcd.print(title);

      // Save the new count
      lastCount = count;
    }

    // Check for a button press
    if (twist.isPressed()) {
      while (twist.isPressed());
      // Clear the selection and return the chosen index
      lcd.clear();
      lcd.noBlink();
      return count;
    }
  }
}

#endif