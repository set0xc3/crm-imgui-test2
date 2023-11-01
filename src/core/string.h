#pragma once

#include "base.h"

struct string {
  char *str;
  u64   size;
};

inline string
str_lit(const char *c)
{
  string result;
  result.str  = (char *)c;
  result.size = strlen(c);
  return result;
}

inline bool32
str_eq(const string left, const string right)
{
  bool32 result = !strcmp(left.str, right.str);
  return result;
}
