#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *s21_memchr = S21_NULL;
  unsigned char *ptr = (unsigned char *)str;

  if (str != S21_NULL) {
    s21_size_t s21_n = 0;
    while (s21_n != n) {
      if (ptr[s21_n] == c) {
        s21_memchr = &ptr[s21_n];
        break;
      }
      s21_n++;
    }
  }
  return s21_memchr;
}