#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *s21_strstr = S21_NULL;

  if ((haystack != S21_NULL) && (needle != S21_NULL)) {
    s21_size_t n = s21_strlen(needle);
    if (*needle == 0) s21_strstr = (char *)haystack;
    while (*haystack != '\0' && *needle != '\0') {
      if (s21_memcmp(haystack, needle, n) != 0) {
        haystack++;
      } else {
        s21_strstr = (char *)haystack;
        break;
      }
    }
  }
  return s21_strstr;
}
