#include "../s21_string.h"
void *s21_trim(const char *src, const char *trim_chars) {
  char *result = S21_NULL;
  if (src && trim_chars) {
    int begin = 0;
    int end = s21_strlen(src);
    while (src[begin] && s21_strchr(trim_chars, src[begin])) {
      begin++;
    }
    while (end != begin && s21_strchr(trim_chars, src[end - 1])) {
      end--;
    }
    if ((result = (char *)calloc((end - begin + 1), sizeof(char))) !=
        S21_NULL) {
      for (int i = begin; i < end; i++) {
        result[i - begin] = src[i];
      }
      result[end - begin] = '\0';
    }
  }
  return result;
}