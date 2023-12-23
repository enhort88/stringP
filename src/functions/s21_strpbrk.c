#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *s21_strpbrk = S21_NULL;

  if ((str1 != S21_NULL) && (str2 != S21_NULL)) {
    const char *str2_temp = str2;
    int break_flag = 0;
    for (; (*str1) && (break_flag == 0); str1++) {
      for (str2 = str2_temp; (*str2) && (*str1 != *str2); str2++)
        ;
      if (*str1 == *str2) {
        break_flag = 1;
        s21_strpbrk = (char *)str1;
      }
    }
  }
  return s21_strpbrk;
}
