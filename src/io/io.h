#pragma once
#include <string>

#define MODE_STDIO 0
#define MODE_DEBUG 1

int input();
void output(const std::string&);
void set_mode(const int&); // set the IO mode
int get_mode();