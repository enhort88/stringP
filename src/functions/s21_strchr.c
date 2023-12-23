#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *s21_strchr = S21_NULL;

  if (str != S21_NULL) {
    for (; (*str) && (*str != (unsigned char)c); str++)
      ;
    if (*str == (unsigned char)c) {
      s21_strchr = (char *)str;
    }
  }
  return s21_strchr;
}