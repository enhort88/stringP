#include "../s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *s21_strncpy = dest;

  if ((dest != S21_NULL) && (src != S21_NULL)) {
    s21_size_t s21_n = 0;
    int flag = 0;
    while (s21_n < n) {
      if (src[s21_n] == '\0') flag = 1;
      if (flag == 1) {
        dest[s21_n] = '\0';
      } else {
        dest[s21_n] = src[s21_n];
      }
      s21_n++;
    }
  }
  return s21_strncpy;
}