#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *s21_strrchr = S21_NULL;

  if (str != S21_NULL) {
    char *str_temp = (char *)str;
    for (; *str_temp; str_temp++)
      ;
    for (; (str_temp != str) && (*str_temp != (unsigned char)c); str_temp--)
      ;
    if (*str_temp == (unsigned char)c) {
      s21_strrchr = str_temp;
    }
  }
  return s21_strrchr;
}