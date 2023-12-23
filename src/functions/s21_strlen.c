#include "../s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t s21_strlen = 0;

  if (str != S21_NULL) {
    for (; *str; str++, s21_strlen++)
      ;
  }
  return s21_strlen;
}