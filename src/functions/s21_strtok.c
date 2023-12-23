#include "../s21_string.h"

void move_to_next_token(char **s21_strtok, char **s21_strtok_start,
                        char **s21_strtok_end);
char *s21_strtok(char *str, const char *delim) {
  char *s21_strtok = S21_NULL;
  static char *s21_strtok_start = S21_NULL;
  static char *s21_strtok_end = S21_NULL;
  static int delim_finded = 0;
  static int not_first_function_call = 0;

  if (delim != S21_NULL) {
    if ((str != S21_NULL) && (s21_strlen(str) != 0)) {
      not_first_function_call = 1;
      s21_strtok_start = str;
      s21_strtok_end = str + s21_strlen(str);
      while ((str = s21_strpbrk(str, delim)) != S21_NULL) {
        *str = '\0';
        str = str + 1;
        delim_finded = 1;
      }
      str = s21_strtok_start;
      move_to_next_token(&s21_strtok, &s21_strtok_start, &s21_strtok_end);
    }

    if ((str == S21_NULL) && (not_first_function_call == 1) &&
        (delim_finded == 1)) {
      move_to_next_token(&s21_strtok, &s21_strtok_start, &s21_strtok_end);
      if (s21_strtok_start > s21_strtok_end) {
        s21_strtok = S21_NULL;
        s21_strtok_start = S21_NULL;
        s21_strtok_end = S21_NULL;
        not_first_function_call = 0;
        delim_finded = 0;
      }
    }
  }

  return s21_strtok;
}

void move_to_next_token(char **s21_strtok, char **s21_strtok_start,
                        char **s21_strtok_end) {
  while ((*s21_strtok_start <= *s21_strtok_end) &&
         (**s21_strtok_start == '\0')) {
    (*s21_strtok_start)++;
  }
  *s21_strtok = *s21_strtok_start;
  while ((*s21_strtok_start <= *s21_strtok_end) &&
         (**s21_strtok_start != '\0')) {
    (*s21_strtok_start)++;
  }
  return;
}
