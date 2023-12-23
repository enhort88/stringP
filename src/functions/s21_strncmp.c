#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int s21_strncmp = 0;

  if ((str1 != S21_NULL) && (str2 != S21_NULL)) {
    s21_size_t s21_n = 0;
    while (s21_n < n) {
      if ((((int)*str1 - (int)*str2)) == 0) {
        str1++;
        str2++;
        s21_n++;
      } else {
        s21_strncmp = (int)*str1 - (int)*str2;
        break;
      }
    }
  }

  return s21_strncmp;
}