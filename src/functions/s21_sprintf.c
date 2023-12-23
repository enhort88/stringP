#include "../s21_string.h"

typedef struct {
  int fminus;
  int fplus;
  int fspace;
  int fhash;
  int fnull;
  int width;
  int point;
  int accur;
  int sizeh;
  int sizel;
  int sizeld;
  int argwid;
  int argacc;
  char specificier;
} flags;

int minus(char **buf_it, flags spec, int negnum, int *icount);
int fminus(char **buf_it, flags spec, double *value, int *icount);
int lfminus(char **buf_it, flags spec, long double *value, int *icount);
void align(char **buf_it, flags spec, int ch_num, int signif, int *icount);
void flagparser(const char **format_iter, flags *spec);
void case_c(char **buf_it, flags spec, wchar_t value, int *icount);
void case_d(char **buf_it, flags spec, long int value, int *icount);
void case_f(char **buf_it, flags spec, double value, int *icount);
void case_lf(char **buf_it, flags spec, long double value, int *icount);
void case_g(char **buf_it, flags spec, double value, int *icount, int upcs);
void case_lg(char **buf_it, flags spec, long double value, int *icount,
             int upcs);
void case_s(char **buf_it, flags spec, char *value, int *icount);
void case_ls(char **buf_it, flags spec, wchar_t *value, int *icount);
void case_u(char **buf_it, flags spec, long unsigned int value, int *icount);
void case_x(char **buf_it, flags spec, long unsigned int value, int *icount,
            int upcs);
void case_o(char **buf_it, flags spec, long unsigned int value, int *icount);
void case_e(char **buf_it, flags spec, double value, int *icount, int upcs);
void case_le(char **buf_it, flags spec, long double value, int *icount,
             int upcs);
void case_p(char **buf_it, flags spec, va_list args, int *icount);
void switcher(char **buf_it, const char *format_iter, va_list args, flags spec,
              int *icount);
void rounder(int *digres, int *ch_num);
void mantobr_gf(int *digres, const char *mantistr, int *flnulcount, int *ch_num,
                flags spec, int enddig, int ch_m_num, int exponent);
void mantobr_ge(int *digres, const char *mantistr, int *ch_num, flags spec,
                int enddig, int ch_m_num, int *needround);
void mantobr_f(int *digres, const char *mantistr, int *flnulcount, int *ch_num,
               flags spec, int enddig, int ch_m_num, int exponent);
void mantobr_e(int *digres, const char *mantistr, int *flnulcount, int *ch_num,
               flags spec, int enddig, int ch_m_num, int *needround);
void expobr_e(char *expfnum, int expval, int *exch_num);
void unslintobr(char **buf_it, char *strofnum, flags spec, int *icount,
                int *ch_num, int prefix);
void expadd(char **buf_it, const char *expfnum, int exch_num, int upcs);
void dif_ls(char **buf_it, flags spec, va_list args, int *icount);
void dif_lf(char **buf_it, flags spec, va_list args, int *icount);
void dif_lg(char **buf_it, flags spec, va_list args, int *icount, int upcs);
void dif_le(char **buf_it, flags spec, va_list args, int *icount, int upcs);
void revdigtobuf(char **buf_it, const int *digres, int ch_num);
void revdigtobufg(char **buf_it, const int *digres, int ch_num, int lastpos);
void gfcaseaccur(const char *mantistr, flags spec, int *flnulcount, int *enddig,
                 int *needround, int exponent, int ch_m_num);
void addprefunslint(char **buf_it, flags spec, int prefix, int *icount);
int get_mant_f(char *mantistr, int *exponent, double value);
int get_mant_g(char *mantistr, int *exponent, double value);
int get_mant_lf(char *mantistr, int *exponent, long double value);
int get_mant_lg(char *mantistr, int *exponent, long double value);

int s21_sprintf(char *str, const char *format, ...) {
  int icount = 0;
  va_list args;
  va_start(args, format);
  const char *format_iter = format;
  char *buf_it = str;
  while (*format_iter) {
    flags spec = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '\0'};
    *buf_it = *format_iter;
    buf_it++;
    icount++;
    if (*format_iter == '%') {
      buf_it--;
      icount--;
      flagparser(&format_iter, &spec);
      if (spec.argwid) spec.width = va_arg(args, int);
      if (spec.argacc) spec.accur = va_arg(args, int);
      switcher(&buf_it, format_iter, args, spec, &icount);
    }
    format_iter++;
  }
  *buf_it = '\0';
  va_end(args);
  return icount;
}

void align(char **buf_it, flags spec, int ch_num, int signif, int *icount) {
  for (int i = 0; i < (spec.width - ch_num - signif); i++) {
    if (spec.fnull && !spec.fminus &&
        ((spec.specificier == 'd' && !spec.point) || spec.specificier == 'u' ||
         spec.specificier == 'o' || spec.specificier == 'e' ||
         spec.specificier == 'E' || spec.specificier == 'f' ||
         spec.specificier == 'x' || spec.specificier == 'X')) {
      **buf_it = '0';
    } else {
      **buf_it = ' ';
    }
    (*buf_it)++;
    (*icount)++;
  }
}

int minus(char **buf_it, flags spec, int negnum, int *icount) {
  int signif = 0;
  if (negnum) {
    **buf_it = '-';
    (*buf_it)++;
    (*icount)++;
    signif = 1;
  } else if (spec.fspace) {
    **buf_it = ' ';
    (*buf_it)++;
    (*icount)++;
    signif = 1;
  } else if (spec.fplus) {
    **buf_it = '+';
    (*buf_it)++;
    (*icount)++;
    signif = 1;
  }
  return signif;
}

int fminus(char **buf_it, flags spec, double *value, int *icount) {
  int signif = 0, negnum = 0;
  if ((*value) < 0) {
    negnum = 1;
    (*value) /= (-1);
  }
  if (negnum) {
    **buf_it = '-';
    (*buf_it)++;
    (*icount)++;
    signif = 1;
  } else if (spec.fspace) {
    **buf_it = ' ';
    (*buf_it)++;
    (*icount)++;
    signif = 1;
  } else if (spec.fplus) {
    **buf_it = '+';
    (*buf_it)++;
    (*icount)++;
    signif = 1;
  }
  return signif;
}

int lfminus(char **buf_it, flags spec, long double *value, int *icount) {
  int signif = 0, negnum = 0;
  if ((*value) < 0) {
    negnum = 1;
    (*value) /= (-1);
  }
  if (negnum) {
    **buf_it = '-';
    (*buf_it)++;
    (*icount)++;
    signif = 1;
  } else if (spec.fspace) {
    **buf_it = ' ';
    (*buf_it)++;
    (*icount)++;
    signif = 1;
  } else if (spec.fplus) {
    **buf_it = '+';
    (*buf_it)++;
    (*icount)++;
    signif = 1;
  }
  return signif;
}

void flagparser(const char **format_iter, flags *spec) {
  int find = 0;
  while ((find == 0) && (*format_iter)) {
    (*format_iter)++;
    if (**(format_iter) == '0' && spec->width == 0 && spec->accur == 0)
      spec->fnull = 1;
    if (**(format_iter) == '-') spec->fminus = 1;
    if (**(format_iter) == '+') spec->fplus = 1;
    if (**(format_iter) == ' ') spec->fspace = 1;
    if (**(format_iter) == '#') spec->fhash = 1;
    if ((**(format_iter) >= '0') && (**(format_iter) <= '9') &&
        spec->point == 0)
      spec->width = spec->width * 10 + ((**(format_iter)) - '0');
    if (**(format_iter) == '.') spec->point = 1;
    if (**(format_iter) == '*' && spec->point == 0) spec->argwid = 1;
    if (**(format_iter) == '*' && spec->point == 1) spec->argacc = 1;
    if ((**(format_iter) >= '0') && (**(format_iter) <= '9') &&
        spec->point == 1)
      spec->accur = spec->accur * 10 + ((**(format_iter)) - '0');
    if (**(format_iter) == 'h') spec->sizeh = 1;
    if (**(format_iter) == 'l') spec->sizel = 1;
    if (**(format_iter) == 'L') spec->sizeld = 1;

    if ((**(format_iter) == 'c') || (**(format_iter) == 'd') ||
        (**(format_iter) == 'f') || (**(format_iter) == 's') ||
        (**(format_iter) == 'u') || (**(format_iter) == '%') ||
        (**(format_iter) == 'g') || (**(format_iter) == 'G') ||
        (**(format_iter) == 'x') || (**(format_iter) == 'X') ||
        (**(format_iter) == 'e') || (**(format_iter) == 'E') ||
        (**(format_iter) == 'o') || (**(format_iter) == 'p')) {
      spec->specificier = **(format_iter);
      find = 1;
    }
  }
}

void case_c(char **buf_it, flags spec, wchar_t value, int *icount) {
  int ch_num = 1;
  if (spec.sizel) {
    char check[MB_CUR_MAX];
    ch_num = wctomb(check, value);
    if (!spec.fminus) align(buf_it, spec, ch_num, 0, icount);
    **buf_it = *check;
  } else {
    if (!spec.fminus) align(buf_it, spec, ch_num, 0, icount);
    **buf_it = (char)value;
  }
  *buf_it += ch_num;
  *icount += ch_num;
  if (spec.fminus) align(buf_it, spec, ch_num, 0, icount);
}

void case_d(char **buf_it, flags spec, long int value, int *icount) {
  if (spec.sizel) {
    value = (long int)value;
  } else if (spec.sizeh) {
    value = (short int)value;
  } else {
    value = (int)value;
  }
  int ch_num = 1, signif = 0;
  int negnum = value < 0 ? 1 : 0;
  if (negnum || (spec.fspace) || (spec.fplus)) signif = 1;
  if (negnum) value /= (-1);
  long int cvalue = value;
  char strofnum[25] = {0};
  while ((cvalue / 10) != 0) {
    strofnum[ch_num] = (value % 10) + '0';
    value /= 10;
    cvalue /= 10;
    ch_num++;
  }
  strofnum[ch_num] = (value % 10) + '0';
  int nls = (spec.accur - ch_num) > 0 ? (spec.accur - ch_num) : 0;
  if (!spec.accur && !spec.width) minus(buf_it, spec, negnum, icount);
  if (!spec.accur && spec.width) minus(buf_it, spec, negnum, icount);
  if (!spec.fminus) align(buf_it, spec, ch_num + nls, signif, icount);
  if (spec.accur) minus(buf_it, spec, negnum, icount);
  for (int an = 0; an < nls; an++) {
    **buf_it = '0';
    (*buf_it)++;
    (*icount)++;
  }
  if (spec.point && !spec.accur && ch_num == 1 && strofnum[ch_num] == '0') {
    if (!spec.width)
      ch_num = 0;
    else
      strofnum[ch_num] = ' ';
  }
  for (int i = ch_num; i > 0; i--) {
    **buf_it = strofnum[i];
    (*buf_it)++;
    (*icount)++;
  }
  if (spec.fminus) align(buf_it, spec, ch_num + nls, signif, icount);
}

void case_f(char **buf_it, flags spec, double value, int *icount) {
  if (spec.point && !spec.accur) spec.accur = 0;
  if (!spec.point && !spec.accur) spec.accur = 6;
  int digres[350] = {0};
  int flnulcount = 0, enddig = 0, needround = 0, ch_m_num = 0;
  int ch_num = 0, signif = 0;
  signif = fminus(buf_it, spec, &value, icount);
  int exponent = 0;
  char mantistr[20] = {'\0'};
  get_mant_f(mantistr, &exponent, value);
  for (int i = 0; mantistr[i] != '\0'; i++) {
    ch_m_num++;
  }
  int flnumblen = ch_m_num - exponent;
  if (flnumblen <= spec.accur) {
    flnulcount = spec.accur - flnumblen;
    enddig = ch_m_num - 1;
  } else {
    enddig = exponent + spec.accur - 1;
    if (mantistr[enddig + 1] >= '5' && mantistr[enddig + 1] <= '9' &&
        (enddig + 1) != (ch_m_num - 1)) {
      needround = 1;
    }
  }
  mantobr_f(digres, mantistr, &flnulcount, &ch_num, spec, enddig, ch_m_num,
            exponent);
  if (needround) {
    rounder(digres, &ch_num);
  }
  if (!spec.fminus) align(buf_it, spec, ch_num, signif, icount);
  revdigtobuf(buf_it, digres, ch_num);
  (*icount) += ch_num;
  if (spec.fminus) align(buf_it, spec, ch_num, signif, icount);
}

void case_lf(char **buf_it, flags spec, long double value, int *icount) {
  if (spec.point && !spec.accur) spec.accur = 0;
  if (!spec.point && !spec.accur) spec.accur = 6;
  int digres[5000] = {0};
  int flnulcount = 0, enddig = 0, needround = 0, ch_m_num = 0;
  int ch_num = 0, signif = 0;
  signif = lfminus(buf_it, spec, &value, icount);
  int exponent = 0;
  char mantistr[20] = {'\0'};
  get_mant_lf(mantistr, &exponent, value);
  for (int i = 0; mantistr[i] != '\0'; i++) {
    ch_m_num++;
  }
  int flnumblen = ch_m_num - exponent;
  if (flnumblen <= spec.accur) {
    flnulcount = spec.accur - flnumblen;
    enddig = ch_m_num - 1;
  } else {
    enddig = exponent + spec.accur - 1;
    if (mantistr[enddig + 1] >= '5' && mantistr[enddig + 1] <= '9' &&
        (enddig + 1) != (ch_m_num - 1)) {
      needround = 1;
    }
  }
  mantobr_f(digres, mantistr, &flnulcount, &ch_num, spec, enddig, ch_m_num,
            exponent);
  if (needround) {
    rounder(digres, &ch_num);
  }
  if (!spec.fminus) align(buf_it, spec, ch_num, signif, icount);
  revdigtobuf(buf_it, digres, ch_num);
  (*icount) += ch_num;
  if (spec.fminus) align(buf_it, spec, ch_num, signif, icount);
}

void case_g(char **buf_it, flags spec, double value, int *icount, int upcs) {
  if (spec.point && !spec.accur) spec.accur = 1;
  if (!spec.point && !spec.accur) spec.accur = 6;
  int digres[350] = {0};
  char expfnum[25] = {0};
  int flnulcount = 0, enddig = 0, needround = 0, ch_m_num = 0;
  int ch_num = 0, exch_num = 0, signif = 0, lastpos = -1;
  signif = fminus(buf_it, spec, &value, icount);
  int exponent = 0;
  char mantistr[20] = {'\0'};
  get_mant_g(mantistr, &exponent, value);
  for (int i = 0; mantistr[i] != '\0'; i++) {
    ch_m_num++;
  }
  int expv = (((exponent - 1) < -4) || (spec.accur <= (exponent - 1))) ? 1 : 0;
  if (expv) {
    if (ch_m_num == 0) exponent = 1;
    int expval = exponent - 1;
    expobr_e(expfnum, expval, &exch_num);
    mantobr_ge(digres, mantistr, &ch_num, spec, enddig, ch_m_num, &needround);
  } else {
    gfcaseaccur(mantistr, spec, &flnulcount, &enddig, &needround, exponent,
                ch_m_num);
    mantobr_gf(digres, mantistr, &flnulcount, &ch_num, spec, enddig, ch_m_num,
               exponent);
  }
  if (needround) {
    rounder(digres, &ch_num);
  }
  if (!expv && !spec.fhash) {
    for (int g = 0; g < ch_num && lastpos == -1; g++) {
      if (digres[g] != 0) lastpos = g;
    }
  }
  if (lastpos < 0) lastpos = 0;
  if (!spec.fminus)
    align(buf_it, spec, ch_num + exch_num - lastpos, signif, icount);
  revdigtobufg(buf_it, digres, ch_num, lastpos);
  if (expv) expadd(buf_it, expfnum, exch_num, upcs);
  (*icount) += ch_num - lastpos + exch_num;
  if (spec.fminus)
    align(buf_it, spec, ch_num + exch_num - lastpos, signif, icount);
}

void case_lg(char **buf_it, flags spec, long double value, int *icount,
             int upcs) {
  if (spec.point && !spec.accur) spec.accur = 1;
  if (!spec.point && !spec.accur) spec.accur = 6;
  int digres[5000] = {0};
  char expfnum[25] = {0};
  int flnulcount = 0, enddig = 0, needround = 0, ch_m_num = 0;
  int ch_num = 0, exch_num = 0, signif = 0, lastpos = -1;
  signif = lfminus(buf_it, spec, &value, icount);
  int exponent = 0;
  char mantistr[20] = {'\0'};
  get_mant_lg(mantistr, &exponent, value);
  for (int i = 0; mantistr[i] != '\0'; i++) {
    ch_m_num++;
  }
  int expv = (((exponent - 1) < -4) || (spec.accur <= (exponent - 1))) ? 1 : 0;
  if (expv) {
    if (ch_m_num == 0) exponent = 1;
    int expval = exponent - 1;
    expobr_e(expfnum, expval, &exch_num);
    mantobr_ge(digres, mantistr, &ch_num, spec, enddig, ch_m_num, &needround);
  } else {
    gfcaseaccur(mantistr, spec, &flnulcount, &enddig, &needround, exponent,
                ch_m_num);
    mantobr_gf(digres, mantistr, &flnulcount, &ch_num, spec, enddig, ch_m_num,
               exponent);
  }
  if (needround) {
    rounder(digres, &ch_num);
  }
  if (!expv && !spec.fhash) {
    for (int g = 0; g < ch_num && lastpos == -1; g++) {
      if (digres[g] != 0) lastpos = g;
    }
  }
  if (lastpos < 0) lastpos = 0;
  if (!spec.fminus)
    align(buf_it, spec, ch_num + exch_num - lastpos, signif, icount);
  revdigtobufg(buf_it, digres, ch_num, lastpos);
  if (expv) expadd(buf_it, expfnum, exch_num, upcs);
  (*icount) += ch_num - lastpos + exch_num;
  if (spec.fminus)
    align(buf_it, spec, ch_num + exch_num - lastpos, signif, icount);
}

void case_s(char **buf_it, flags spec, char *value, int *icount) {
  int ch_num = 0, delprt = 0;
  while (*value) {
    ch_num++;
    value++;
  }
  value -= ch_num;
  if (spec.point && !spec.accur) delprt = ch_num;
  if (spec.point && spec.accur && spec.accur <= ch_num)
    delprt = ch_num - spec.accur;
  if (!spec.fminus) align(buf_it, spec, ch_num - delprt, 0, icount);
  for (int k = 0; k < ch_num && !(spec.point && (spec.accur == 0)); k++) {
    **buf_it = value[k];
    if (spec.point && (spec.accur == k + 1)) k = ch_num;
    (*buf_it)++;
    (*icount)++;
  }
  if (spec.fminus) align(buf_it, spec, ch_num - delprt, 0, icount);
}

void case_ls(char **buf_it, flags spec, wchar_t *value, int *icount) {
  int ch_num = 0;
  ch_num = wcstombs(S21_NULL, value, 0);

  if (!spec.fminus) align(buf_it, spec, ch_num, 0, icount);
  wcstombs(*buf_it, value, ch_num + 3);
  (*buf_it) += ch_num;
  (*icount) += ch_num;
  if (spec.fminus) align(buf_it, spec, ch_num, 0, icount);
}

void case_p(char **buf_it, flags spec, va_list args, int *icount) {
  long unsigned int address = va_arg(args, long unsigned int);
  char hexString[18];
  int adrlen = 0, delprt = 0;
  while (address != 0) {
    int digit = address % 16;
    hexString[adrlen++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'a');
    address /= 16;
  }
  hexString[adrlen++] = 'x';
  hexString[adrlen++] = '0';
  int start = 0, end = adrlen - 1;
  while (start < end) {
    char temp = hexString[start];
    hexString[start] = hexString[end];
    hexString[end] = temp;
    start++;
    end--;
  }
  if (spec.point && !spec.accur) delprt = adrlen;
  if (spec.point && spec.accur && spec.accur <= adrlen)
    delprt = adrlen - spec.accur;
  if (!spec.fminus) align(buf_it, spec, adrlen - delprt, 0, icount);
  for (int k = 0; k < adrlen && !(spec.point && (spec.accur == 0)); k++) {
    **buf_it = hexString[k];
    if (spec.point && (spec.accur == k + 1)) k = adrlen;
    (*buf_it)++;
    (*icount)++;
  }
  if (spec.fminus) align(buf_it, spec, adrlen - delprt, 0, icount);
}

void case_u(char **buf_it, flags spec, long unsigned int value, int *icount) {
  if (spec.sizel) {
    value = (long unsigned int)value;
  } else if (spec.sizeh) {
    value = (short unsigned int)value;
  } else {
    value = (unsigned int)value;
  }
  int ch_num = 1;
  char strofnum[25];
  long unsigned int cvalue = value;
  while ((cvalue / 10) != 0) {
    strofnum[ch_num] = (value % 10) + '0';
    value /= 10;
    cvalue /= 10;
    ch_num++;
  }
  strofnum[ch_num] = (value % 10) + '0';
  unslintobr(buf_it, strofnum, spec, icount, &ch_num, 0);
}

void case_x(char **buf_it, flags spec, long unsigned int value, int *icount,
            int upcs) {
  if (spec.sizel) {
    value = (long unsigned int)value;
  } else if (spec.sizeh) {
    value = (short unsigned int)value;
  } else {
    value = (unsigned int)value;
  }
  int ch_num = 1, prefix = 0;
  char strofnum[25];
  long unsigned int cvalue = value;
  char hex = upcs ? 'A' : 'a';
  while ((cvalue / 16) != 0) {
    strofnum[ch_num] =
        (value % 16) < 10 ? ((value % 16) + '0') : ((value % 16 - 10) + hex);
    value /= 16;
    cvalue /= 16;
    ch_num++;
  }
  strofnum[ch_num] =
      (value % 16) < 10 ? ((value % 16) + '0') : ((value % 16 - 10) + 'A');
  if (value && spec.fhash) prefix = 2;
  unslintobr(buf_it, strofnum, spec, icount, &ch_num, prefix);
}

void case_o(char **buf_it, flags spec, long unsigned int value, int *icount) {
  if (spec.sizel) {
    value = (long unsigned int)value;
  } else if (spec.sizeh) {
    value = (short unsigned int)value;
  } else {
    value = (unsigned int)value;
  }
  int ch_num = 1, prefix = 0;
  char strofnum[25];
  long unsigned int cvalue = value;
  while ((cvalue / 8) != 0) {
    strofnum[ch_num] = (value % 8) + '0';
    value /= 8;
    cvalue /= 8;
    ch_num++;
  }
  strofnum[ch_num] = (value % 8) + '0';
  if (value && spec.fhash && (ch_num + 1 > spec.accur)) prefix = 1;
  unslintobr(buf_it, strofnum, spec, icount, &ch_num, prefix);
}

void case_e(char **buf_it, flags spec, double value, int *icount, int upcs) {
  if (spec.point && !spec.accur) spec.accur = 0;
  if (!spec.point && !spec.accur) spec.accur = 6;
  int digres[350] = {0};
  int flnulcount = 0, enddig = 0, needround = 0, ch_m_num = 0;
  int ch_num = 0, signif = 0;
  signif = fminus(buf_it, spec, &value, icount);
  int exponent = 0;
  char mantistr[20] = {'\0'};
  get_mant_f(mantistr, &exponent, value);
  for (int i = 0; mantistr[i] != '\0'; i++) {
    ch_m_num++;
  }
  if (ch_m_num == 0) {
    exponent = 1;
  }
  int exch_num = 0, expval = exponent - 1;
  char expfnum[25] = {0};
  expobr_e(expfnum, expval, &exch_num);
  mantobr_e(digres, mantistr, &flnulcount, &ch_num, spec, enddig, ch_m_num,
            &needround);
  if (needround) {
    rounder(digres, &ch_num);
  }
  if (!spec.fminus) align(buf_it, spec, ch_num + exch_num, signif, icount);
  revdigtobuf(buf_it, digres, ch_num);
  expadd(buf_it, expfnum, exch_num, upcs);
  (*icount) += ch_num + exch_num;
  if (spec.fminus) align(buf_it, spec, ch_num + exch_num, signif, icount);
}

void case_le(char **buf_it, flags spec, long double value, int *icount,
             int upcs) {
  if (spec.point && !spec.accur) spec.accur = 0;
  if (!spec.point && !spec.accur) spec.accur = 6;
  int digres[5000] = {0};
  int flnulcount = 0, enddig = 0, needround = 0, ch_m_num = 0;
  int ch_num = 0, signif = 0;
  signif = lfminus(buf_it, spec, &value, icount);
  int exponent = 0;
  char mantistr[20] = {'\0'};
  get_mant_lf(mantistr, &exponent, value);
  for (int i = 0; mantistr[i] != '\0'; i++) {
    ch_m_num++;
  }
  if (ch_m_num == 0) {
    exponent = 1;
  }
  int exch_num = 0, expval = exponent - 1;
  char expfnum[25] = {0};
  expobr_e(expfnum, expval, &exch_num);
  mantobr_e(digres, mantistr, &flnulcount, &ch_num, spec, enddig, ch_m_num,
            &needround);
  if (needround) {
    rounder(digres, &ch_num);
  }
  if (!spec.fminus) align(buf_it, spec, ch_num + exch_num, signif, icount);
  revdigtobuf(buf_it, digres, ch_num);
  expadd(buf_it, expfnum, exch_num, upcs);
  (*icount) += ch_num + exch_num;
  if (spec.fminus) align(buf_it, spec, ch_num + exch_num, signif, icount);
}

void switcher(char **buf_it, const char *format_iter, va_list args, flags spec,
              int *icount) {
  if (*format_iter == 'c') {
    case_c(buf_it, spec, va_arg(args, wchar_t), icount);
  } else if (*format_iter == 'd') {
    case_d(buf_it, spec, va_arg(args, long int), icount);
  } else if (*format_iter == 'f') {
    dif_lf(buf_it, spec, args, icount);
  } else if (*format_iter == 's') {
    dif_ls(buf_it, spec, args, icount);
  } else if (*format_iter == 'p') {
    case_p(buf_it, spec, args, icount);
  } else if (*format_iter == 'u') {
    case_u(buf_it, spec, va_arg(args, long unsigned int), icount);
  } else if (*format_iter == 'o') {
    case_o(buf_it, spec, va_arg(args, long unsigned int), icount);
  } else if (*format_iter == 'x') {
    case_x(buf_it, spec, va_arg(args, long unsigned int), icount, 0);
  } else if (*format_iter == 'X') {
    case_x(buf_it, spec, va_arg(args, long unsigned int), icount, 1);
  } else if (*format_iter == 'E') {
    dif_le(buf_it, spec, args, icount, 1);
  } else if (*format_iter == 'e') {
    dif_le(buf_it, spec, args, icount, 0);
  } else if (*format_iter == 'G') {
    dif_lg(buf_it, spec, args, icount, 1);
  } else if (*format_iter == 'g') {
    dif_lg(buf_it, spec, args, icount, 0);
  } else if (*format_iter == '%') {
    **buf_it = '%';
    (*buf_it)++;
    (*icount)++;
  } else {
    **buf_it = *format_iter;
    (*buf_it)++;
    (*icount)++;
  }
}

void rounder(int *digres, int *ch_num) {
  int afterpoint = 0;
  for (int h = 0; h < *ch_num; h++) {
    if (digres[h] != -1) {
      if (!h) {
        digres[h]++;
      }
      if (digres[h + 1] == -1) afterpoint = 1;
      if ((digres[h] == 10) && afterpoint && (h == (*(ch_num)-1))) {
        (*ch_num)++;
      }
      if ((digres[h] == 10) && (digres[h + 1] != -1)) {
        digres[h] = 0;
        digres[h + 1]++;
      }
      if ((digres[h] == 10) && (digres[h + 1] == -1)) {
        digres[h] = 0;
        digres[h + 2]++;
      }
    }
  }
}

void mantobr_f(int *digres, const char *mantistr, int *flnulcount, int *ch_num,
               flags spec, int enddig, int ch_m_num, int exponent) {
  int pointpos = -1;
  if (exponent >= 1) {
    pointpos = exponent;
  }
  while (*flnulcount) {
    digres[*ch_num] = 0;
    (*ch_num)++;
    (*flnulcount)--;
  }
  if ((exponent >= ch_m_num) && (spec.accur != 0)) {
    digres[*ch_num - (exponent - ch_m_num)] = -1;
    (*ch_num)++;
    digres[*ch_num] = 0;
  }
  if (!spec.accur && spec.fhash) {
    digres[*ch_num] = -1;
    (*ch_num)++;
    digres[*ch_num] = 0;
  }
  for (int j = enddig; j >= 0 && mantistr[j] != 0; j--) {
    digres[*ch_num] = (mantistr[j] - '0');
    (*ch_num)++;
    if (pointpos == j) {
      digres[*ch_num] = -1;
      (*ch_num)++;
    }
  }
  if (exponent < 1) {
    int less = (spec.accur * (-1)) < exponent ? exponent : (spec.accur * (-1));
    for (int ex = less; ex < 0; ex++) {
      digres[*ch_num] = 0;
      (*ch_num)++;
    }
    if (!(spec.accur == 0 && exponent == 0)) {
      digres[*ch_num] = -1;
      (*ch_num)++;
      digres[*ch_num] = 0;
      (*ch_num)++;
    }
  }
}

void mantobr_gf(int *digres, const char *mantistr, int *flnulcount, int *ch_num,
                flags spec, int enddig, int ch_m_num, int exponent) {
  int pointpos = -1;
  if (exponent >= 1) {
    pointpos = exponent;
  }
  while (*flnulcount && spec.fhash) {
    digres[*ch_num] = 0;
    (*ch_num)++;
    (*flnulcount)--;
  }
  if (spec.fhash && (exponent != 0)) {
    digres[*ch_num] = -1;
    (*ch_num)++;
    digres[*ch_num] = 0;
  }
  for (int j = enddig; j >= 0 && mantistr[j] != 0; j--) {
    digres[*ch_num] = (mantistr[j] - '0');
    (*ch_num)++;
    if (pointpos == j) {
      digres[*ch_num] = -1;
      (*ch_num)++;
    }
  }
  if (exponent < 1) {
    int less = (spec.accur * (-1)) < exponent ? exponent : (spec.accur * (-1));
    for (int ex = less; ex < 0; ex++) {
      digres[*ch_num] = 0;
      (*ch_num)++;
    }
    if ((!(spec.accur == 0 && exponent == 0))) {
      if (ch_m_num != 0) {
        digres[*ch_num] = -1;
        (*ch_num)++;
      }
      digres[*ch_num] = 0;
      (*ch_num)++;
    }
  }
}

void mantobr_ge(int *digres, const char *mantistr, int *ch_num, flags spec,
                int enddig, int ch_m_num, int *needround) {
  int flnumblen = ch_m_num - 1;
  if (flnumblen <= spec.accur) {
    enddig = ch_m_num - 1;
  } else {
    enddig = spec.accur - 1;
    if (mantistr[enddig + 1] >= '5' && mantistr[enddig + 1] <= '9' &&
        (enddig + 1) != (ch_m_num - 1)) {
      *needround = 1;
    }
  }
  while (mantistr[enddig] == '0') {
    enddig--;
  }
  for (int j = enddig; j >= 0; j--) {
    digres[*ch_num] = (mantistr[j] - '0');
    (*ch_num)++;
    if (j == 1) {
      digres[*ch_num] = -1;
      (*ch_num)++;
    }
  }
  if (ch_m_num == 0) {
    *ch_num = 0;
    digres[*ch_num] = 0;
    (*ch_num)++;
    digres[*ch_num] = -1;
    (*ch_num)++;
    digres[*ch_num] = 0;
    (*ch_num)++;
  }
}

void mantobr_e(int *digres, const char *mantistr, int *flnulcount, int *ch_num,
               flags spec, int enddig, int ch_m_num, int *needround) {
  if (ch_m_num != 0) {
    int flnumblen = ch_m_num - 1;
    if (flnumblen <= spec.accur) {
      *flnulcount = spec.accur - flnumblen;
      enddig = ch_m_num - 1;
    } else {
      enddig = spec.accur;
      if (mantistr[enddig + 1] >= '5' && mantistr[enddig + 1] <= '9' &&
          (enddig + 1) != (ch_m_num - 1)) {
        *needround = 1;
      }
    }
  } else {
    *flnulcount = spec.accur;
    enddig = -1;
  }
  while (*flnulcount) {
    digres[*ch_num] = 0;
    (*ch_num)++;
    (*flnulcount)--;
  }
  for (int j = enddig; j >= 0; j--) {
    digres[*ch_num] = (mantistr[j] - '0');
    (*ch_num)++;
    if (j == 1) {
      digres[*ch_num] = -1;
      (*ch_num)++;
    }
  }
  if (ch_m_num == 0) {
    if (spec.accur != 0) {
      digres[*ch_num] = -1;
      (*ch_num)++;
    }
    digres[*ch_num] = 0;
    (*ch_num)++;
  }
}

void expobr_e(char *expfnum, int expval, int *exch_num) {
  int exnegnum = expval < 0 ? 1 : 0;
  if (exnegnum) expval /= (-1);
  int cvalue = expval;
  while ((cvalue / 10) != 0) {
    expfnum[*exch_num] = (expval % 10);
    expval /= 10;
    cvalue /= 10;
    (*exch_num)++;
  }
  expfnum[*exch_num] = (expval % 10);
  (*exch_num)++;
  if (*exch_num < 2) {
    expfnum[*exch_num] = 0;
    (*exch_num)++;
  }
  expfnum[*exch_num] = exnegnum ? -3 : -4;
  (*exch_num)++;
  expfnum[*exch_num] = -2;
  (*exch_num)++;
}

void unslintobr(char **buf_it, char *strofnum, flags spec, int *icount,
                int *ch_num, int prefix) {
  int nls = (spec.accur - (*ch_num)) > 0 ? (spec.accur - (*ch_num)) : 0;
  if (!spec.point) addprefunslint(buf_it, spec, prefix, icount);
  if (!spec.fminus) align(buf_it, spec, (*ch_num) + nls + prefix, 0, icount);
  if (spec.point) addprefunslint(buf_it, spec, prefix, icount);
  for (int an = 0; an < nls; an++) {
    **buf_it = '0';
    (*buf_it)++;
    (*icount)++;
  }
  if (spec.point && !spec.accur && (*ch_num) == 1 &&
      strofnum[(*ch_num)] == '0') {
    if (!spec.width)
      (*ch_num) = 0;
    else
      strofnum[(*ch_num)] = ' ';
  }
  for (int i = (*ch_num); i > 0; i--) {
    **buf_it = strofnum[i];
    (*buf_it)++;
    (*icount)++;
  }
  if (spec.fminus) align(buf_it, spec, (*ch_num) + nls + prefix, 0, icount);
}

void expadd(char **buf_it, const char *expfnum, int exch_num, int upcs) {
  for (int h = exch_num - 1; h >= 0; h--) {
    if (expfnum[h] == -2) {
      **buf_it = upcs ? 'E' : 'e';
      (*buf_it)++;
    } else if (expfnum[h] == -3) {
      **buf_it = '-';
      (*buf_it)++;
    } else if (expfnum[h] == -4) {
      **buf_it = '+';
      (*buf_it)++;
    } else {
      **buf_it = expfnum[h] + '0';
      (*buf_it)++;
    }
  }
}

void dif_ls(char **buf_it, flags spec, va_list args, int *icount) {
  if (spec.sizel) {
    case_ls(buf_it, spec, va_arg(args, wchar_t *), icount);
  } else {
    case_s(buf_it, spec, va_arg(args, char *), icount);
  }
}

void dif_lf(char **buf_it, flags spec, va_list args, int *icount) {
  if (spec.sizeld) {
    case_lf(buf_it, spec, va_arg(args, long double), icount);
  } else {
    case_f(buf_it, spec, va_arg(args, double), icount);
  }
}

void dif_lg(char **buf_it, flags spec, va_list args, int *icount, int upcs) {
  if (spec.sizeld) {
    case_lg(buf_it, spec, va_arg(args, long double), icount, upcs);
  } else {
    case_g(buf_it, spec, va_arg(args, double), icount, upcs);
  }
}

void dif_le(char **buf_it, flags spec, va_list args, int *icount, int upcs) {
  if (spec.sizeld) {
    case_le(buf_it, spec, va_arg(args, long double), icount, upcs);
  } else {
    case_e(buf_it, spec, va_arg(args, double), icount, upcs);
  }
}

void revdigtobuf(char **buf_it, const int *digres, int ch_num) {
  for (int h = ch_num - 1; h >= 0; h--) {
    if (digres[h] == -1) {
      **buf_it = '.';
      (*buf_it)++;
    } else {
      **buf_it = digres[h] + '0';
      (*buf_it)++;
    }
  }
}

void revdigtobufg(char **buf_it, const int *digres, int ch_num, int lastpos) {
  for (int h = ch_num - 1; h >= lastpos; h--) {
    if (digres[h] == -1) {
      **buf_it = '.';
      (*buf_it)++;
    } else {
      **buf_it = digres[h] + '0';
      (*buf_it)++;
    }
  }
}

void gfcaseaccur(const char *mantistr, flags spec, int *flnulcount, int *enddig,
                 int *needround, int exponent, int ch_m_num) {
  int flnumblen = ch_m_num - exponent;
  if (exponent >= 1 && spec.accur) spec.accur = spec.accur - exponent;
  if (!spec.fhash && exponent >= 1 && !spec.point) {
    spec.accur = 1;
  }
  if (spec.fhash && !spec.point) spec.accur = 6 - exponent;
  if (flnumblen <= spec.accur) {
    (*flnulcount) = spec.accur - flnumblen;
    (*enddig) = ch_m_num - 1;
  } else {
    (*enddig) = exponent + spec.accur - 1;
    if (mantistr[(*enddig) + 1] >= '5' && mantistr[(*enddig) + 1] <= '9' &&
        ((*enddig) + 1) != (ch_m_num - 1)) {
      *needround = 1;
    }
  }
}

void addprefunslint(char **buf_it, flags spec, int prefix, int *icount) {
  if (prefix > 0) {
    **buf_it = '0';
    (*buf_it)++;
    (*icount)++;
    if (prefix == 2) {
      **buf_it = spec.specificier == 'X' ? 'X' : 'x';
      (*buf_it)++;
      (*icount)++;
    }
  }
}

int get_mant_f(char *mantistr, int *exponent, double value) {
  if (value != 0.0) {
    uint64_t mantissa;
    int intres[20] = {0};
    int mant_num = 0;
    int startpos = 0;
    *exponent = 0;
    while (value >= 2.0) {
      value /= 10.0;
      (*exponent)++;
    }
    while (value < 1.0) {
      value *= 10.0;
      (*exponent)--;
    }
    mantissa = (uint64_t)(value * 1e16);
    while ((mantissa / 10) != 0) {
      intres[mant_num] = (mantissa % 10);
      value /= 10;
      mantissa /= 10;
      mant_num++;
    }
    intres[mant_num] = (mantissa % 10);
    for (int i = 0; i <= mant_num - startpos; i++) {
      mantistr[i] = intres[mant_num - i] + '0';
    }
    (*exponent)++;
    mantistr[mant_num - startpos + 1] = '\0';
  } else {
    mantistr[1] = '\0';
  }
  return value;
}

int get_mant_g(char *mantistr, int *exponent, double value) {
  if (value != 0.0) {
    uint64_t mantissa;
    int intres[20] = {0};
    int mant_num = 0;
    int startpos = 0;
    *exponent = 0;
    while (value >= 2.0) {
      value /= 10.0;
      (*exponent)++;
    }
    while (value < 1.0) {
      value *= 10.0;
      (*exponent)--;
    }
    mantissa = (uint64_t)(value * 1e16);
    while ((mantissa / 10) != 0) {
      intres[mant_num] = (mantissa % 10);
      value /= 10;
      mantissa /= 10;
      mant_num++;
    }
    intres[mant_num] = (mantissa % 10);
    for (int i = 0; i <= mant_num; i++) {
      if (intres[i] != 0) {
        startpos = i;
        i = mant_num;
      }
    }
    for (int i = 0; i <= mant_num - startpos; i++) {
      mantistr[i] = intres[mant_num - i] + '0';
    }
    (*exponent)++;
    mantistr[mant_num - startpos + 1] = '\0';
  } else {
    mantistr[1] = '\0';
  }
  return value;
}

int get_mant_lf(char *mantistr, int *exponent, long double value) {
  if (value != 0.0) {
    uint64_t mantissa;
    int intres[20] = {0};
    int mant_num = 0;
    int startpos = 0;
    *exponent = 0;
    while (value >= 2.0) {
      value /= 10.0;
      (*exponent)++;
    }
    while (value < 1.0) {
      value *= 10.0;
      (*exponent)--;
    }
    mantissa = (uint64_t)(value * 1e16);
    while ((mantissa / 10) != 0) {
      intres[mant_num] = (mantissa % 10);
      value /= 10;
      mantissa /= 10;
      mant_num++;
    }
    intres[mant_num] = (mantissa % 10);
    for (int i = 0; i <= mant_num - startpos; i++) {
      mantistr[i] = intres[mant_num - i] + '0';
    }
    (*exponent)++;
    mantistr[mant_num - startpos + 1] = '\0';
  } else {
    mantistr[1] = '\0';
  }
  return value;
}

int get_mant_lg(char *mantistr, int *exponent, long double value) {
  if (value != 0.0) {
    uint64_t mantissa;
    int intres[20] = {0};
    int mant_num = 0;
    int startpos = 0;
    *exponent = 0;
    while (value >= 2.0) {
      value /= 10.0;
      (*exponent)++;
    }
    while (value < 1.0) {
      value *= 10.0;
      (*exponent)--;
    }
    mantissa = (uint64_t)(value * 1e16);
    while ((mantissa / 10) != 0) {
      intres[mant_num] = (mantissa % 10);
      value /= 10;
      mantissa /= 10;
      mant_num++;
    }
    intres[mant_num] = (mantissa % 10);
    for (int i = 0; i <= mant_num; i++) {
      if (intres[i] != 0) {
        startpos = i;
        i = mant_num;
      }
    }
    for (int i = 0; i <= mant_num - startpos; i++) {
      mantistr[i] = intres[mant_num - i] + '0';
    }
    (*exponent)++;
    mantistr[mant_num - startpos + 1] = '\0';
  } else {
    mantistr[1] = '\0';
  }
  return value;
}