#include "../s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  void *s21_memcpy = dest;
  unsigned char *ptr1 = (unsigned char *)dest;
  unsigned char *ptr2 = (unsigned char *)src;

  if ((ptr1 != S21_NULL) && (ptr2 != S21_NULL)) {
    s21_size_t s21_n = 0;
    while (s21_n != n) {
      ptr1[s21_n] = ptr2[s21_n];
      s21_n++;
    }
  }

  return s21_memcpy;
}