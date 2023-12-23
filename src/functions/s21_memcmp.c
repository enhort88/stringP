#include "../s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int s21_memcmp = 0;
  unsigned char *ptr1 = (unsigned char *)str1;
  unsigned char *ptr2 = (unsigned char *)str2;

  if ((ptr1 != S21_NULL) && (ptr2 != S21_NULL)) {
    s21_size_t s21_n = 0;
    while (s21_n < n) {
      if ((ptr1[s21_n] - ptr2[s21_n]) != 0) {
        s21_memcmp = ptr1[s21_n] - ptr2[s21_n];
        break;
      }
      s21_n++;
    }
  }
  return s21_memcmp;
}
