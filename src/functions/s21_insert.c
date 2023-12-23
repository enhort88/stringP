#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, size_t start_index) {
  char *result = S21_NULL;
  if (src && str && s21_strlen(src) >= start_index) {
    s21_size_t len = s21_strlen(str) + s21_strlen(src);
    result = (char *)calloc(len + 1, sizeof(char));
    if (result) {
      char *temp = result;
      int mid_index = s21_strlen(str);
      int fin_index = len - start_index - mid_index;
      while (temp && start_index--) *temp++ = *src++;
      while (temp && mid_index--) *temp++ = *str++;
      while (temp && fin_index--) *temp++ = *src++;
      if (temp) *temp = '\0';
    }
  }
  return result;
}
