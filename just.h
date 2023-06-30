#ifndef UTIL_H
#define JUST_H

char* ljust(int num, int width, char filler = ' ') {
  char buf[width];  // Define a buffer to hold the resulting C-string

  // Convert an int to char*
  sprintf(buf, "%d", num);
  ljust(buf, width, filler);
  return buf;
}
char* ljust(float num, int width, char filler = ' ') {
  char buf[width];  // Define a buffer to hold the resulting C-string

  // Convert an int to char*
  sprintf(buf, "%d", num);
  ljust(buf, width, filler);
  return buf;
}

char* rjust(int num, int width, char filler = ' ') {
  char buf[width];  // Define a buffer to hold the resulting C-string

  // Convert an int to char*
  sprintf(buf, "%d", num);
  ljust(buf, width, filler);
  return buf;
}
char* rjust(float num, int width, char filler = ' ') {
  char buf[width];  // Define a buffer to hold the resulting C-string

  // Convert an int to char*
  sprintf(buf, "%d", num);
  ljust(buf, width, filler);
  return buf;
}


void ljust(char* str, int width, char filler = ' ') {
  int len = strlen(str);
  if (len < width) {
    memset(str + len, filler, width - len);
    str[width] = '\0';
  }
}

void rjust(char* str, int width, char filler = ' ') {
  int len = strlen(str);
  if (len < width) {
    memmove(str + width - len, str, len + 1);
    memset(str, filler, width - len);
  }
}

#endif