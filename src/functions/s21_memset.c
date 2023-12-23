#include "../s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  void *s21_memset = str;
  unsigned char *ptr1 = (unsigned char *)str;

  if ((ptr1 != S21_NULL) && (n > 0)) {
    s21_size_t s21_n = 1;
    for (; (*ptr1) && (s21_n <= n); *ptr1 = (unsigned char)c, ptr1++, s21_n++)
      ;
  }
  return s21_memset;
}