#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "util.h"

const int hight = 2;
const int width = 15;
const int MAX_LENGTH = 15;

// Define the keyboard layout
char keyboard[hight][width] = {
  {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', '_'},
  {'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '<', '>'},
};

void numSelect(int*& reslt, char* title, int numOfNums, char* sep)
{
  int results[numOfNums];
  int positions[numOfNums];

  for (int i = 0; i < numOfNums; i++) {
    results[i] = 0;
  }
  for (int i = 0; i < numOfNums; i++) {
    positions[i] = 0;
  }

  int pos;

  int count;
  int lastCount = -1;

  bool mode = true; // true: select, false: edit

  twist.setCount(0);
  lcd.clear();

  while (true)
  {
    // Update the rotary encoder count
    count = twist.getCount();

    // Only update the selection if the count has changed
    if (count != lastCount)
    {
      if (mode) // if in select mode
      {
        // Wrap the selection around if it goes out of bounds
        if (count < 0)
        {
          twist.setCount(numOfNums - 1);
          continue;
        }
        else if (count > numOfNums - 1)
        {
          twist.setCount(0);
          continue;
        }
      }

      if (mode) // select
      {
        if (count < 0)
        {
          twist.setCount(numOfNums);
          continue;
        }
        if (count > numOfNums)
        {
          twist.setCount(0);
          continue;
        }
        pos = count;
      }
      else // edit
      {
        results[pos] = count;
      }
      lastCount = count;

      // draw ui
      lcd.setCursor(0, 0);
      lcd.print(title);

      String row = "";

      // Iterate over the elements in the list
      for (int i = 0; i < sizeof(results)/sizeof(results[0]); i++) {
        // Append the current element to the row string and the position to the postitions array
        positions[i] = row.length();
        int res = results[i];
        row += res;
        
        // Append the separator, unless we're at the last element
        if (i < sizeof(results)/sizeof(results[0])-1) {
          row += String(sep);
        }
      }

      lcd.setCursor(0, 2);
      lcd.print(row);

      if (mode)
      {
        lcd.setCursor(positions[pos], 2);
      }
      else
      {
        lcd.setCursor(positions[pos], 3);
      }
      lcd.blink();
    }
    if (twist.isPressed())
    {
      if (mode)
      {
        mode = false;
        twist.setCount(results[pos]);
        unsigned long timeStrt = millis();
        while (twist.isPressed());
        if (millis() - timeStrt > 500)
        {
          break;
        }
        delay(50);
      }
      else
      {
        mode = true;
        twist.setCount(pos);
        unsigned long timeStrt = millis();
        while (twist.isPressed());
        if (millis() - timeStrt > 500)
        {
          break;
        }
        delay(50);
      }
    }
  }
  lcd.clear();
  lcd.noBlink();

  for (int i = 0; i < sizeof(results) / sizeof(results[0]); i++) {
    reslt[i] = results[i];
  }
}


bool* selectDaysOfWeek(char* title = "Select Days") {
  const char* daysOfWeek[] = {"S", "M", "T", "W", "T", "F", "S"};
  const int numDays = sizeof(daysOfWeek) / sizeof(daysOfWeek[0]);

  lcd.clear();
  lcd.println(title);
  bool* selected = new bool[numDays];
  String row = "";
  for (int x = 0; x < numDays; x ++) {
    row += " ";
    row += daysOfWeek[x];
    selected[x] = false;
  }
  lcd.print(row);

  int prevCount;
  twist.setCount(0);

  while (1) {
    int count = twist.getCount();
    if (count < 0) {
      count = numDays - 1;
      twist.setCount(count);
    }
    count = count % numDays;

    if (count != prevCount) {
      lcd.setCursor(0, 0);
      lcd.println(title);
      lcd.print(row);
    }

    lcd.setCursor(count * 2 + 1, 1);
    lcd.blink();

    if (twist.isPressed()) {
      unsigned long timeStart = millis();
      while (twist.isPressed()) {
        if (millis() - timeStart > 1000) {
          return selected;
        }
      }

      lcd.setCursor(count * 2 + 1, 2);
      if (selected[count]) {
        selected[count] = false;
        lcd.print(' ');
        // lcd.write(byte(0));
      } else {
        selected[count] = true;
        lcd.print('^');
      }
      // Serial.print(count);
      // Serial.print(" ");
      // Serial.println(selected[count] ? "TRUE" : "FALSE");
    }

    prevCount = count;
  }
}

char* strInput(char* title)
{
  int cursor_x;
  int cursor_y;

  // define the input buffer
  int input_index = 0;
  char input[MAX_LENGTH] = "";
  lcd.clear();
  lcd.print(title);
  // Display the keyboard
  for (int y = 2; y < 4; y++) {
    String row = "";
    for (int i = 0; i < sizeof(keyboard[y-2])/sizeof(keyboard[y-2][0]); i++) {
      row.concat(keyboard[y-2][i]);  // Add each element to the string
    }
    lcd.setCursor(0, y);
    lcd.print(row);
  }
  
  // Display the cursor on the keyboard
  lcd.setCursor(cursor_x * 2, cursor_y + 2);
  lcd.blink();

  while (true)
  {
    int pos = twist.getCount();
    if (pos < 0)
    {
      twist.setCount(width * hight - 1);
      pos = twist.getCount();
    }

    countToXY(pos, width, cursor_y, cursor_x);
    lcd.setCursor(cursor_x, 2 + cursor_y);

    // Check if the rotary encoder button is pressed
    if (twist.isPressed()) {
      char character = keyboard[cursor_y][cursor_x];
      // Check if the cursor is on the delete button

      if (character == '<') {
        // Delete the last character from the input
        if (input_index > 0) {
          input_index--;
          input[input_index] = '\0';
          lcd.setCursor(0, 1);
          lcd.print(input);
          lcd.setCursor(input_index, 1);
          lcd.print(' ');
        }
      }
      // Check if the cursor is on the submit button
      else if (character == '>') {
        lcd.clear();
        lcd.noBlink();
        // Allocate dynamic memory for the input string
        char* result = new char[input_index + 1];
        // Copy the input to the dynamically allocated memory
        strncpy(result, input, input_index);
        result[input_index] = '\0';  // Add null terminator
        return result;
      }
      // Otherwise, add the selected letter to the input
      else {
        if (input_index < MAX_LENGTH) {
          input[input_index] = character;
          input_index++;
          lcd.setCursor(0, 1);
          lcd.print(input);
          lcd.setCursor(input_index, 1);
        }
      }
      while(twist.isPressed()) {}
    }
  }
}

#endif