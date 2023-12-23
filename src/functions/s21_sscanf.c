#include "../s21_string.h"

struct flag {
  int h;
  int l;
  int L;
  int star;
  int message;
  int err;
  int count;
  int is_negative;
  int wight;
  int res;
};
unsigned long long hex_str_pars(const char *str, int len, struct flag *fl);
int len_str_part(const char *s);
s21_size_t long_line_len(const char *s);
int octalToDecimal(int n);
long double parse_hexadecimal(const char *s, struct flag *fl);
long double parse_decimal(const char *s, struct flag *fl);
int fl_swtchr(struct flag *fl, const char *f);
int case_digits(struct flag *fl, const char *s, const char *f, va_list *args);
int case_chr_str(struct flag *fl, const char *s, const char *f, va_list *args);
int f_star_check(struct flag *fl, const char *f);
int f_wight_check(struct flag *fl, const char *f);
int space_del(const char *s, const char *f);
void fl_clear(struct flag *fl);
void *state_fill(void *str, int c, s21_size_t n);
int case_d(struct flag *fl, const char *s, va_list *args);
int case_hd(struct flag *fl, const char *s, va_list *args);
int case_ld(struct flag *fl, const char *s, va_list *args);
int case_i(struct flag *fl, const char *s, va_list *args);
int case_hi(struct flag *fl, const char *s, va_list *args);
int case_li(struct flag *fl, const char *s, va_list *args);
int case_e(struct flag *fl, const char *s, va_list *args);
int case_Le(struct flag *fl, const char *s, va_list *args);
int case_u(struct flag *fl, const char *s, va_list *args);
int case_hu(struct flag *fl, const char *s, va_list *args);
int case_lu(struct flag *fl, const char *s, va_list *args);
int case_f(struct flag *fl, const char *s, va_list *args);
int case_Lf(struct flag *fl, const char *s, va_list *args);
int case_x(struct flag *fl, const char *s, va_list *args);
int case_hx(struct flag *fl, const char *s, va_list *args);
int case_lx(struct flag *fl, const char *s, va_list *args);
int case_o(struct flag *fl, const char *s, va_list *args);
int case_ho(struct flag *fl, const char *s, va_list *args);
int case_lo(struct flag *fl, const char *s, va_list *args);
int case_p(struct flag *fl, const char *s, va_list *args);
int case_c(struct flag *fl, const char *s, va_list *args);
int case_lc(struct flag *fl, const char *s, va_list *args);
int case_s(struct flag *fl, const char *s, va_list *args);
int case_ls(struct flag *fl, const char *s, va_list *args);

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  const char *s = str;
  const char *f = format;
  struct flag fl = {0, 0, 0, 0, 0, 0, 0, 0, -1, 0};
  while (*f && !fl.err) {
    s += space_del(s, f);
    if (*f == '%') {
      fl.res = (*s == '\0' || *s == '\n') ? fl.res : fl.res + 1;
      f++;
      f += f_star_check(&fl, f);
      f += f_wight_check(&fl, f);
      f += fl_swtchr(&fl, f);
      s += case_digits(&fl, s, f, &args);
      s += case_chr_str(&fl, s, f, &args);
      fl.err = (fl.message > 1) ? 1 : fl.err;
    }
    f++;
    fl_clear(&fl);
  }
  va_end(args);
  return (fl.err > 0) ? EOF : fl.res;
}

void fl_clear(struct flag *fl) {
  fl->count = fl->is_negative = fl->h = fl->l = fl->L = fl->message = fl->star =
      0;
  fl->wight = -1;
}
int fl_swtchr(struct flag *fl, const char *f) {
  switch (*f) {
    case 'h':
      fl->h = 1;
      break;
    case 'l':
      fl->l = 1;
      break;
    case 'L':
      fl->L = 1;
      break;
    default:
      break;
  }
  return (fl->h || fl->l || fl->L) ? 1 : 0;
}
int case_digits(struct flag *fl, const char *s, const char *f, va_list *args) {
  int res = 0;
  switch (*f) {
    case 'u': {
      res = (fl->h)   ? case_hu(fl, s, args)
            : (fl->l) ? case_lu(fl, s, args)
                      : case_u(fl, s, args);
      break;
    }
    case 'G':
    case 'g':
    case 'E':
    case 'e': {
      res = (fl->L) ? case_Le(fl, s, args) : case_e(fl, s, args);
      break;
    }
    case 'o': {
      res = (fl->h)   ? case_ho(fl, s, args)
            : (fl->l) ? case_lo(fl, s, args)
                      : case_o(fl, s, args);
      break;
    }
    case 'X':
    case 'x': {
      res = (fl->h)   ? case_hx(fl, s, args)
            : (fl->l) ? case_lx(fl, s, args)
                      : case_x(fl, s, args);
      break;
    }
    case 'f': {
      res = (fl->L) ? case_Lf(fl, s, args) : case_f(fl, s, args);
      break;
    }
    case 'd': {
      res = (fl->h)   ? case_hd(fl, s, args)
            : (fl->l) ? case_ld(fl, s, args)
                      : case_d(fl, s, args);
      break;
    }
    case 'i': {
      res = (fl->h)   ? case_hi(fl, s, args)
            : (fl->l) ? case_li(fl, s, args)
                      : case_i(fl, s, args);
      break;
    }
    default:
      fl->message += 1;
      break;
  }
  return res;
}
int case_chr_str(struct flag *fl, const char *s, const char *f, va_list *args) {
  int res = 0;
  switch (*f) {
    case 'p': {
      res = case_p(fl, s, args);
      break;
    }
    case 'c': {
      res = (fl->l) ? case_lc(fl, s, args) : case_c(fl, s, args);
      break;
    }
    case 's': {
      res = (fl->l) ? case_ls(fl, s, args) : case_s(fl, s, args);
      break;
    }
    default:
      fl->message += 1;
      break;
  }
  return res;
}
int f_star_check(struct flag *fl, const char *f) {
  int count = 0;
  while (*f && (*f == ' ' || *f == '\t')) {
    f++;
    count++;
  }
  if (*f == '*') {
    fl->star = 1;
    fl->res--;
    count++;
  }
  return (fl->star) ? count : 0;
}
int f_wight_check(struct flag *fl, const char *f) {
  int lenght = 0;
  if ((*f >= '0' && *f <= '9')) {
    int temp = parse_decimal(f, fl);
    fl->wight = (!temp) ? -1 : temp;
    lenght = (!temp) ? 1 : fl->count;
    fl->count = 0;
  }

  return lenght;
}
int space_del(const char *s, const char *f) {
  int count = 0;
  while (*s && (*s == ' ' || *s == '\t') && *(f + 1) != 'c') {
    s++;
    count++;
  };
  return count;
}
long double parse_hexadecimal(const char *s, struct flag *fl) {
  long double result = 0.0;
  long double decimal_part = 0;
  long double decimal_divisor = 1.0;
  int is_decimal_part = 0;
  int is_negative = 0;
  if (*s == '-') {
    is_negative = 1;
    s++;
    fl->count++;
  }
  while (((*s >= '0' && *s <= '9') || (*s >= 'a' && *s <= 'f') ||
          (*s >= 'A' && *s <= 'F') || (*s == '.'|| *s==',')) &&
         fl->wight != 0) {
    if (*s == '.'|| *s==',') {
      is_decimal_part = 1;
      s++;
      fl->count++;
      fl->wight--;
      continue;
    }
    if (is_decimal_part) {
      decimal_divisor *= 16.0;
      decimal_part = (long double)decimal_part * 16 +
                     (*s >= 'a' ? (*s - 'a' + 10)
                                : (*s >= 'A' ? (*s - 'A' + 10) : (*s - '0')));
      fl->count++;
    } else {
      result = (long double)result * 16 +
               (*s >= 'a' ? (*s - 'a' + 10)
                          : (*s >= 'A' ? (*s - 'A' + 10) : (*s - '0')));
      fl->count++;
    }
    fl->wight--;
    s++;
  }
  if (is_decimal_part) {
    result += decimal_part / decimal_divisor;
  }
  return is_negative ? -result : result;
}
long double parse_decimal(const char *s, struct flag *fl) {
  long double result = 0.0;
  long double integer_part = 0.0;
  long double decimal_part = 0.0;
  long double decimal_divisor = 1.0;
  int is_decimal_part = 0;
  int is_negative = 0;
  if (*s == '-') {
    is_negative = 1;
    s++;
    fl->count++;
    fl->wight--;
  }
  while (((*s >= '0' && *s <= '9') || (*s == '.' || *s==',')) && fl->wight != 0) {
    if (*s == '.'|| *s==',') {
      is_decimal_part = 1;
      s++;
      fl->count++;
      continue;
    }
    if (is_decimal_part) {
      decimal_divisor *= 10.0;
      decimal_part = (long double)decimal_part * 10 + (*s - '0');
      fl->count++;
    } else {
      integer_part = (long double)integer_part * 10 + (*s - '0');
      fl->count++;
    }
    fl->wight--;
    s++;
  }
  result = integer_part + decimal_part / decimal_divisor;
  return is_negative ? -result : result;
}
int len_str_part(const char *s) {
  int lenght = 0;
  while (*s && *s != ' ' && *s != '\t') {
    lenght++;
    s++;
  }
  return lenght;
}
int octalToDecimal(int octalNum) {
  int decimalNum = 0;
  int base = 0;

  while (octalNum != 0) {
    int last_digit = octalNum % 10;
    octalNum = octalNum / 10;
    decimalNum += last_digit * pow(8, base);
    ++base;
  }
  return decimalNum;
}
int case_d(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    int *ptr = va_arg(*args, int *);
    *ptr = 0;
    *ptr = (int)parse_decimal(s, fl);
  }
  return lenght;
}
int case_hd(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    short int *ptr = va_arg(*args, short int *);
    *ptr = 0;
    *ptr = (short int)parse_decimal(s, fl);
  }
  return lenght;
}
int case_ld(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    long int *ptr = va_arg(*args, long int *);
    *ptr = 0;
    *ptr = (long int)parse_decimal(s, fl);
  }
  return lenght;
}
int case_i(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    if (*s == '-') {
      fl->is_negative = 1;
      s++;
    }
    int *ptr = va_arg(*args, int *);
    *ptr = 0;
    if (*s == '0') {
      s++;
      if (*s == 'x' || *s == 'X') {
        s++;
        *ptr = (int)parse_hexadecimal(s, fl);
      } else
        *ptr = (int)octalToDecimal(parse_decimal(s, fl));
    } else {
      *ptr = (int)parse_decimal(s, fl);
    }
    if (fl->is_negative) *ptr = -(*ptr);
  }
  return lenght;
}
int case_hi(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    if (*s == '-') {
      fl->is_negative = 1;
      s++;
    }
    short int *ptr = va_arg(*args, short int *);
    *ptr = 0;
    if (*s == '0') {
      s++;
      if (*s == 'x' || *s == 'X') {
        s++;
        *ptr = (short int)parse_hexadecimal(s, fl);
      } else
        *ptr = (short int)octalToDecimal(parse_decimal(s, fl));
    } else {
      *ptr = (short int)parse_decimal(s, fl);
    }
    if (fl->is_negative) *ptr = -(*ptr);
  }
  return lenght;
}
int case_li(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    if (*s == '-') {
      fl->is_negative = 1;
      s++;
    }
    long int *ptr = va_arg(*args, long int *);
    *ptr = 0;
    if (*s == '0') {
      s++;
      if (*s == 'x' || *s == 'X') {
        s++;
        *ptr = (long int)parse_hexadecimal(s, fl);
      } else
        *ptr = (long int)octalToDecimal(parse_decimal(s, fl));
    } else {
      *ptr = (long int)parse_decimal(s, fl);
    }
    if (fl->is_negative) *ptr = -(*ptr);
  }
  return lenght;
}
int case_e(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    if (*s == '-') {
      fl->is_negative = 1;
      s++;
    }
    float *ptr = va_arg(*args, float *);
    *ptr = 0;
    if ((*s == '0')) {
      s++;
      if (*s == 'x' || *s == 'X') {
        s++;
        *ptr = parse_hexadecimal(s, fl);
        s += fl->count;
      } else {
        *ptr = parse_decimal(s, fl);
        s += fl->count;
      }
    } else {
      *ptr = parse_decimal(s, fl);
      s += fl->count;
    }
    if (*s == 'e' || *s == 'E') {
      s++;
      int expSign = 1;
      if (*s == '+' || *s == '-') {
        expSign = (*s == '+') ? 1 : -1;
        s++;
      }
      int expValue = parse_decimal(s, fl);
      *ptr *= pow(10, expSign * expValue);
    }
    if (fl->is_negative) *ptr = -(*ptr);
  }
  return lenght;
}
int case_Le(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    if (*s == '-') {
      fl->is_negative = 1;
      s++;
    }
    long double *ptr = va_arg(*args, long double *);
    *ptr = 0;
    if (*s == '0') {
      s++;
      if (*s == 'x' || *s == 'X') {
        s++;
        *ptr = (long double)parse_hexadecimal(s, fl);
        s += fl->count;
      } else {
        *ptr = (long double)parse_decimal(s, fl);
        s += fl->count;
      }
    } else {
      *ptr = (long double)parse_decimal(s, fl);
      s += fl->count;
    }
    if (*s == 'e' || *s == 'E') {
      s++;
      int expSign = 1;
      if (*s == '+' || *s == '-') {
        expSign = (*s == '+') ? 1 : -1;
        s++;
      }
      int expValue = (long double)parse_decimal(s, fl);
      *ptr *= pow(10, expSign * expValue);
    }
    if (fl->is_negative) *ptr = -(*ptr);
  }
  return lenght;
}
int case_u(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    unsigned int *ptr = va_arg(*args, unsigned int *);
    *ptr = 0;
    *ptr = (unsigned int)parse_decimal(s, fl);
  }
  return lenght;
}
int case_hu(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    short unsigned int *ptr = va_arg(*args, short unsigned int *);
    *ptr = 0;
    *ptr = (short unsigned int)parse_decimal(s, fl);
  }
  return lenght;
}
int case_lu(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    long unsigned int *ptr = va_arg(*args, long unsigned int *);
    *ptr = 0;
    *ptr = (long unsigned int)parse_decimal(s, fl);
  }
  return lenght;
}
int case_f(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    float *ptr = va_arg(*args, float *);
    *ptr = 0;
    *ptr = (float)parse_decimal(s, fl);
  }
  return lenght;
}
int case_Lf(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    long double *ptr = va_arg(*args, long double *);
    *ptr = 0;
    *ptr = (long double)parse_decimal(s, fl);
  }
  return lenght;
}
int case_x(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    unsigned int *ptr = va_arg(*args, unsigned int *);
    *ptr = 0;
    if (*s == '0') {
      s++;
      if (*s == 'x' || *s == 'X') {
        s++;
        *ptr = (int)parse_hexadecimal(s, fl);
      }
    } else
      *ptr = (int)parse_decimal(s, fl);
  }
  return lenght;
}
int case_hx(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    short unsigned int *ptr = va_arg(*args, short unsigned int *);
    *ptr = 0;
    if (*s == '0') {
      s++;
      if (*s == 'x' || *s == 'X') {
        s++;
        *ptr = (short unsigned int)parse_hexadecimal(s, fl);
      }
    } else
      *ptr = (short unsigned int)parse_decimal(s, fl);
  }
  return lenght;
}
int case_lx(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    long unsigned int *ptr = va_arg(*args, long unsigned int *);
    *ptr = 0;
    if (*s == '0') {
      s++;
      if (*s == 'x' || *s == 'X') {
        s++;
        *ptr = (long unsigned int)parse_hexadecimal(s, fl);
      }
    } else
      *ptr = (long unsigned int)parse_decimal(s, fl);
  }
  return lenght;
}
int case_o(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    unsigned int *ptr = va_arg(*args, unsigned int *);
    *ptr = 0;
    if (*s == '0') {
      s++;
      *ptr = (unsigned int)octalToDecimal(parse_decimal(s, fl));
    } else
      *ptr = (unsigned int)octalToDecimal(parse_decimal(s, fl));
  }
  return lenght;
}
int case_ho(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    short unsigned int *ptr = va_arg(*args, short unsigned int *);
    *ptr = 0;
    if (*s == '0') {
      s++;
      *ptr = (short unsigned int)octalToDecimal(parse_decimal(s, fl));
    } else
      *ptr = (short unsigned int)octalToDecimal(parse_decimal(s, fl));
  }
  return lenght;
}
int case_lo(struct flag *fl, const char *s, va_list *args) {
  int lenght = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    long unsigned int *ptr = va_arg(*args, long unsigned int *);
    *ptr = 0;
    if (*s == '0') {
      s++;
      *ptr = (long unsigned int)octalToDecimal(parse_decimal(s, fl));
    } else
      *ptr = (long unsigned int)octalToDecimal(parse_decimal(s, fl));
  }
  return lenght;
}
int case_p(struct flag *fl, const char *s, va_list *args) {
  int check = len_str_part(s);
  int result = (fl->wight != -1) ? fl->wight : len_str_part(s);
  int lenght = result;
  if (!fl->star) {
    void **ptr = va_arg(*args, void **);
    *ptr = 0;
    char *t;
    t = (char *)calloc((lenght + 1), sizeof(char));
    if (t != S21_NULL) {
      char *temp = t;
      while (lenght--) {
        *temp++ = *s++;
      }
      *ptr = (void *)hex_str_pars(t, result, fl);
    } else {
      fl->err = 1;
      va_end(*args);
    }
    free(t);
  }
  if (check >= fl->wight && fl->wight != -1) fl->res -= 1;
  return result;
}
int case_c(struct flag *fl, const char *s, va_list *args) {
  if (!fl->star) {
    char *ptr = va_arg(*args, char *);
    *ptr = 0;
    if (*s) *ptr = *s;
  }
  return 1;
}
int case_lc(struct flag *fl, const char *s, va_list *args) {
  s21_size_t length = mblen(s, MB_CUR_MAX);
  if (!fl->star) {
    wchar_t *ptr = va_arg(*args, wchar_t *);
    *ptr = 0;
    if (*s) {
      int bytes = mbtowc(ptr, s, MB_CUR_MAX);
      length = bytes;
      if (bytes < 0) *ptr = L'\0';
    }
  }
  return length;
}
int case_s(struct flag *fl, const char *s, va_list *args) {
  int result = (fl->wight != -1) ? fl->wight : len_str_part(s);
  if (!fl->star) {
    int length = result;
    char *ptr = va_arg(*args, char *);
    result = length;
    char *temp = ptr;
    while (length--) *temp++ = *s++;
    *temp = '\0';
  }
  return result;
}
int case_ls(struct flag *fl, const char *s, va_list *args) {
  s21_size_t result = long_line_len(s);
  s21_size_t length = 0;

  if (!fl->star) {
    wchar_t *ptr = va_arg(*args, wchar_t *);
    *ptr = 0;
    mbstate_t state;
    state_fill(&state, 0, sizeof(state));
    if (*s) {
      while (*s != '\0' && *s != ' ' && fl->wight) {
        int bytes = mbtowc(ptr, s, MB_CUR_MAX);
        if (bytes < 0) {
          *ptr = L'\0';
          fl->err = 1;
        }
        length += bytes;
        s += bytes;
        ptr++;
        fl->wight--;
      }
      *ptr = L'\0';
    }
  }
  return (fl->wight != -1) ? (int)length : (int)result;
}

s21_size_t long_line_len(const char *s) {
  s21_size_t length = 0;
  while (*s && (*s != ' ' && *s != '\t')) {
    s21_size_t temp;
    temp = abs(mblen(s, MB_CUR_MAX));
    s += temp;
    length += temp;
  }
  return length;
}
void *state_fill(void *str, int c, s21_size_t n) {
  void *state_fill = str;
  unsigned char *ptr1 = (unsigned char *)str;
  if ((ptr1 != S21_NULL) && (n > 0)) {
    s21_size_t s21_n = 1;
    for (; (s21_n <= n); *ptr1 = (unsigned char)c, ptr1++, s21_n++)
      ;
  }
  return state_fill;
}
unsigned long long hex_str_pars(const char *str, int len, struct flag *fl) {
  unsigned long long result = 0;
  if (len >= 2 && (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))) {
    str += 2;
    len -= 2;
  }

  for (int i = 0; i < len; i++) {
    char c = str[i];
    unsigned long long val = 0;
    if (c >= '0' && c <= '9') {
      val = c - '0';
    } else if (c >= 'a' && c <= 'f') {
      val = 10 + (c - 'a');
    } else if (c >= 'A' && c <= 'F') {
      val = 10 + (c - 'A');
    } else {
      fl->err = 1;
    }
    result = result * 16 + val;
  }
  return result;
}