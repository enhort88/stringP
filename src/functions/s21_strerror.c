#include "../s21_string.h"

char *s21_strerror(int errnum) {
  void *s21_strerror = S21_NULL;
  static char unknown_error_str[128] = {0};

#if __APPLE__
  char *error_array_str[] = {error_num_apple};
  int error_num_max = 106;
#elif __linux__
  char *error_array_str[] = {error_num_linux};
  int error_num_max = 133;
#endif

  if (errnum >= 0 && errnum <= error_num_max)
    s21_strerror = error_array_str[errnum];
  else {
    s21_sprintf(unknown_error_str, "%s%d", error_array_str[error_num_max + 1],
                errnum);
    s21_strerror = unknown_error_str;
  }
  return s21_strerror;
}
