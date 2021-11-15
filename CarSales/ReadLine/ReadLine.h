#pragma once

int readInt(const char* _prompt);
float readFloat(const char* _prompt);
double readDouble(const char* _prompt);
long readLongInt(const char* _prompt);
int readIntInRange(const char* _prompt, int _low, int _high);
void readString(const char* _prompt, char* _destination, int _maxLen);
char readChar(const char* _prompt);