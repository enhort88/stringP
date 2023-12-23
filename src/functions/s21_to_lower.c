#include "../s21_string.h"

void *s21_to_lower(const char *str) {
  char *result = S21_NULL;
  if (str) {
    s21_size_t len = 0;
    while (str[len]) len++;
    result = (char *)calloc(len + 1, sizeof(char));
    if (result) {
      for (s21_size_t i = 0; i < len; i++)
        result[i] = (str[i] >= 'A' && str[i] <= 'Z') ? str[i] + 32 : str[i];

      result[len] = '\0';
    }
  }
  return result;
}
