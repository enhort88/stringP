#include "s21_string_test.h"

START_TEST(s21_sscanf_test_1) {
  setlocale(0, "");
  int a = 0;
  int b = 0;

  const char *str = "1 3 € ПрИвЕт мир друг";
  const char *form = "%d %d %lc %ls %2ls\n";
  int num11;
  int num12;
  wchar_t ch1;
  wchar_t words11[BUFF];
  wchar_t words12[BUFF];

  int num21;
  int num22;
  wchar_t ch2;
  wchar_t words21[BUFF];
  wchar_t words22[BUFF];

  a = s21_sscanf(str, form, &num11, &num12, &ch1, &words11, &words12);
  b = sscanf(str, form, &num21, &num22, &ch2, &words21, &words22);

  ck_assert_int_eq(num11, num21);
  ck_assert_int_eq(num12, num22);
  ck_assert_int_eq(ch1, ch2);
  ck_assert_mem_eq(words11, words21, 12);
  ck_assert_mem_eq(words11, words21, 4);

  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sscanf_test_2) {
  setlocale(0, "");
  int a = 0;
  int b = 0;

  const char *str = "1.0012121e213 3 ! Hello";
  const char *form = "%e %lu %c %s\n";
  float num11;
  long unsigned int num12;
  char ch1;
  char words1[BUFF];

  float num21;
  long unsigned int num22;
  char ch2;
  char words2[BUFF];

  a = s21_sscanf(str, form, &num11, &num12, &ch1, &words1);
  b = sscanf(str, form, &num21, &num22, &ch2, &words2);

  ck_assert_float_eq(num11, num21);
  ck_assert_int_eq(num12, num22);
  ck_assert_int_eq(ch1, ch2);
  ck_assert_str_eq(words1, words2);

  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sscanf_test_3) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "0xA 100 ! Hello";
  const char *form = "%e %u %c %s\n";
  float num11;
  unsigned int num12;
  char ch1;
  char words1[BUFF];

  float num21;
  unsigned int num22;
  char ch2;
  char words2[BUFF];

  a = s21_sscanf(str, form, &num11, &num12, &ch1, &words1);
  b = sscanf(str, form, &num21, &num22, &ch2, &words2);

  ck_assert_float_eq(num11, num21);
  ck_assert_int_eq(num12, num22);
  ck_assert_int_eq(ch1, ch2);
  ck_assert_str_eq(words1, words2);

  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(s21_sscanf_test_4) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "100 100";
  const char *form = "%1d %1u\n";
  int num11;
  unsigned int num12;

  int num21;
  unsigned int num22;

  a = s21_sscanf(str, form, &num11, &num12);
  b = sscanf(str, form, &num21, &num22);

  ck_assert_float_eq(num11, num21);
  ck_assert_int_eq(num12, num22);

  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(s21_sscanf_test_5) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "0xA12 076 077 ! Hello";
  const char *form = "%x %o %lo %c %s\n";
  unsigned int num11;
  unsigned int num12;
  long unsigned int num13;
  char ch1;
  char words1[BUFF];

  unsigned int num21;
  unsigned int num22;
  long unsigned int num23;
  char ch2;
  char words2[BUFF];

  a = s21_sscanf(str, form, &num11, &num12, &num13, &ch1, &words1);
  b = sscanf(str, form, &num21, &num22, &num23, &ch2, &words2);

  ck_assert_float_eq(num11, num21);
  ck_assert_int_eq(num12, num22);
  ck_assert_int_eq(num13, num23);
  ck_assert_int_eq(ch1, ch2);
  ck_assert_str_eq(words1, words2);

  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sscanf_test_6) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "0xfff12 3 *! hello";
  const char *form = "%p %hi %c %s";
  void *num11;
  short int num12;
  char ch1;
  char words1[BUFF];

  void *num21;
  short int num22;

  char ch2;
  char words2[BUFF];

  a = s21_sscanf(str, form, &num11, &num12, &ch1, &words1);
  b = sscanf(str, form, &num21, &num22, &ch2, &words2);

  ck_assert_ptr_eq(num11, num21);
  ck_assert_int_eq(num12, num22);

  ck_assert_int_eq(ch1, ch2);
  ck_assert_str_eq(words1, words2);

  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(s21_sscanf_test_7) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "0xA10 34 hello s";
  const char *form = "%x %ld %s";
  unsigned int num11;
  long int num12;
  char words1[BUFF];

  unsigned int num21;
  long int num22;
  char words2[BUFF];

  a = s21_sscanf(str, form, &num11, &num12, &words1);
  b = sscanf(str, form, &num21, &num22, &words2);

  ck_assert_int_eq(num11, num21);
  ck_assert_int_eq(num12, num22);
  ck_assert_str_eq(words1, words2);

  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(s21_sscanf_test_8) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "0xA10 0xA11 34 hello";
  const char *form = "%i %li %hd %s";
  int num11;
  long int num12;
  short int num13;
  char words1[BUFF];

  int num21;
  long int num22;
  short int num23;
  char words2[BUFF];

  a = s21_sscanf(str, form, &num11, &num12, &num13, &words1);
  b = sscanf(str, form, &num21, &num22, &num23, &words2);

  ck_assert_int_eq(num11, num21);
  ck_assert_int_eq(num12, num22);
  ck_assert_int_eq(num13, num23);
  ck_assert_str_eq(words1, words2);

  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(s21_sscanf_test_9) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "15 055 0xB10 7 hello";
  const char *form = "%hu %ho %hx %lo %s";
  short unsigned int num11;
  short unsigned int num12;
  short unsigned int num13;
  long unsigned int num14;
  char words1[BUFF];

  short unsigned int num21;
  short unsigned int num22;
  short unsigned int num23;
  long unsigned int num24;
  char words2[BUFF];

  a = s21_sscanf(str, form, &num11, &num12, &num13, &num14, &words1);
  b = sscanf(str, form, &num21, &num22, &num23, &num24, &words2);

  ck_assert_int_eq(num11, num21);
  ck_assert_int_eq(num12, num22);
  ck_assert_int_eq(num13, num23);
  ck_assert_int_eq(num14, num24);
  ck_assert_str_eq(words1, words2);

  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(s21_sscanf_test_10) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "0xA10 0xA11 34 hello";
  const char *form = "%i %li %hd %s";
  int num11;
  long int num12;
  short int num13;
  char words1[BUFF];

  int num21;
  long int num22;
  short int num23;
  char words2[BUFF];

  a = s21_sscanf(str, form, &num11, &num12, &num13, &words1);
  b = sscanf(str, form, &num21, &num22, &num23, &words2);

  ck_assert_int_eq(num11, num21);
  ck_assert_int_eq(num12, num22);
  ck_assert_int_eq(num13, num23);
  ck_assert_str_eq(words1, words2);

  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(s21_sscanf_test_11) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "1.1 1.2 0x12 hello";
  const char *form = "%f %Lf %hi %s";
  float num11;
  long double num12;
  short int num13;
  char words1[BUFF];

  float num21;
  long double num22;
  short int num23;
  char words2[BUFF];

  a = s21_sscanf(str, form, &num11, &num12, &num13, &words1);
  b = sscanf(str, form, &num21, &num22, &num23, &words2);

  ck_assert_float_eq(num11, num21);
  ck_assert_double_eq(num12, num22);
  ck_assert_int_eq(num13, num23);
  ck_assert_str_eq(words1, words2);

  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(s21_sscanf_test_12) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "0772 0xc82 0xc1.1 hello T";
  const char *form = "%Le %lx %e %s";
  long double num11;
  long unsigned int num12;
  float num13;
  char words1[BUFF];

  long double num21;
  long unsigned int num22;
  float num23;
  char words2[BUFF];

  a = s21_sscanf(str, form, &num11, &num12, &num13, &words1);
  b = sscanf(str, form, &num21, &num22, &num23, &words2);

  ck_assert_ldouble_eq_tol(num11, num21, 1e-20);
  ck_assert_int_eq(num12, num22);
  ck_assert_float_eq(num13, num23);
  ck_assert_str_eq(words1, words2);

  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(s21_sscanf_test_13) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "-45 -0x2 -12 h";
  const char *form = "%d %i %i %s";
  int num11;
  int num12;
  int num13;
  char words1[BUFF];

  int num21;
  int num22;
  int num23;
  char words2[BUFF];

  a = s21_sscanf(str, form, &num11, &num12, &num13, &words1);
  b = sscanf(str, form, &num21, &num22, &num23, &words2);

  ck_assert_int_eq(num11, num21);
  ck_assert_int_eq(num12, num22);
  ck_assert_int_eq(num13, num23);
  ck_assert_mem_eq(words1, words2, 1);

  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(s21_sscanf_test_14) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "12 34 12";
  const char *form = "%d %d %d";
  int num11;
  int num12;
  int num13 = 999999;

  int num21;
  int num22;
  int num23 = 999999;

  a = s21_sscanf(str, form, &num11, &num12, &num13);
  b = sscanf(str, form, &num21, &num22, &num23);

  ck_assert_int_eq(num11, num21);
  ck_assert_int_eq(num12, num22);
  ck_assert_int_eq(num13, num23);
  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(s21_sscanf_test_15) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "0xC234 2e+2 3e2 010";
  const char *form = "%Le %e %Le %*Le";
  long double num11;
  float num12;
  long double num13;

  long double num21;
  float num22;
  long double num23;

  a = s21_sscanf(str, form, &num11, &num12, &num13);
  b = sscanf(str, form, &num21, &num22, &num23);

  ck_assert_double_eq(num11, num21);
  ck_assert_float_eq(num12, num22);
  ck_assert_double_eq(num13, num23);
  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(s21_sscanf_test_16) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "010 11 010 012 012";
  const char *form = "%e %li %li %hi %i";
  float num11;
  long int num12;
  long int num13;
  short int num14;
  int num15;

  float num21;
  long int num22;
  long int num23;
  short int num24;
  int num25;

  a = s21_sscanf(str, form, &num11, &num12, &num13, &num14, &num15);
  b = sscanf(str, form, &num21, &num22, &num23, &num24, &num25);

  ck_assert_float_eq(num11, num21);
  ck_assert_int_eq(num12, num22);
  ck_assert_int_eq(num13, num23);
  ck_assert_int_eq(num14, num24);
  ck_assert_int_eq(num15, num25);

  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(s21_sscanf_test_17) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "1 2 3 4 5";
  const char *form = "%x %hx %lx %o %ho";
  unsigned int num11;
  short unsigned int num12;
  long unsigned int num13;
  unsigned int num14;
  short unsigned int num15;

  unsigned int num21;
  short unsigned int num22;
  long unsigned int num23;
  unsigned int num24;
  short unsigned int num25;

  a = s21_sscanf(str, form, &num11, &num12, &num13, &num14, &num15);
  b = sscanf(str, form, &num21, &num22, &num23, &num24, &num25);

  ck_assert_int_eq(num11, num21);
  ck_assert_int_eq(num12, num22);
  ck_assert_int_eq(num13, num23);
  ck_assert_int_eq(num14, num24);
  ck_assert_int_eq(num15, num25);

  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(s21_sscanf_test_18) {
  int a = 0;
  int b = 0;
  const char *str = "12e5 0xc82";
  const char *form = "%E %X";
  float num11;
  unsigned int num12;

  float num21;
  unsigned int num22;

  a = s21_sscanf(str, form, &num11, &num12);
  b = sscanf(str, form, &num21, &num22);

  ck_assert_double_eq(num11, num21);
  ck_assert_int_eq(num12, num22);

  ck_assert_int_eq(a, b);
}
END_TEST
START_TEST(s21_sscanf_test_19) {
  setlocale(0, "");
  int a = 0;
  int b = 0;
  const char *str = "1.797693e+308";
  const char *form = "%Le";
  long double num11;

  long double num21;

  a = s21_sscanf(str, form, &num11);
  b = sscanf(str, form, &num21);

  ck_assert_ldouble_eq_tol(num11, num21, 1e+292);

  ck_assert_int_eq(a, b);
}
END_TEST
Suite *suite(void) {
  Suite *suite = suite_create("\033[32m s21_sscanf_test \033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_sscanf_test_1);
  tcase_add_test(tcase, s21_sscanf_test_2);
  tcase_add_test(tcase, s21_sscanf_test_3);
  tcase_add_test(tcase, s21_sscanf_test_4);
  tcase_add_test(tcase, s21_sscanf_test_5);
  tcase_add_test(tcase, s21_sscanf_test_6);
  tcase_add_test(tcase, s21_sscanf_test_7);
  tcase_add_test(tcase, s21_sscanf_test_8);
  tcase_add_test(tcase, s21_sscanf_test_9);
  tcase_add_test(tcase, s21_sscanf_test_10);
  tcase_add_test(tcase, s21_sscanf_test_11);
  tcase_add_test(tcase, s21_sscanf_test_12);
  tcase_add_test(tcase, s21_sscanf_test_13);
  tcase_add_test(tcase, s21_sscanf_test_14);
  tcase_add_test(tcase, s21_sscanf_test_15);
  tcase_add_test(tcase, s21_sscanf_test_16);
  tcase_add_test(tcase, s21_sscanf_test_17);
  tcase_add_test(tcase, s21_sscanf_test_18);
  tcase_add_test(tcase, s21_sscanf_test_19);

  suite_add_tcase(suite, tcase);
  return suite;
}

void case_test_runner(Suite *suite, int *fail_count) {
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  *fail_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
}

int main(void) {
  int fail_count = 0;
  case_test_runner(suite(), &fail_count);

  return fail_count;
}
