#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  void *s21_strncat = dest;
  unsigned char *ptr1 = (unsigned char *)dest;
  unsigned char *ptr2 = (unsigned char *)src;

  if ((ptr1 != S21_NULL) && (ptr2 != S21_NULL)) {
    s21_size_t s21_n = 1;
    for (; *ptr1; ptr1++)
      ;
    for (; (*ptr2) && (s21_n <= n); *ptr1 = *ptr2, ptr1++, ptr2++, s21_n++)
      ;
    *ptr1 = '\0';
  }
  return s21_strncat;
}