#include "s21_string_test.h"

START_TEST(s21_memchr_test_1) {
  char *test_str_1 = NULL;
  unsigned char test_char = 't';
  size_t n = 28;
  s21_memchr(test_str_1, test_char, n);
}
END_TEST

START_TEST(s21_memchr_test_2) {
  char test_str_1[28] = "test string # test string !";

  int test_char = 't';
  size_t n = -1;
  ck_assert_pstr_eq(memchr(test_str_1, test_char, n),
                    s21_memchr(test_str_1, test_char, n));

  test_char = 1000;
  n = 28;
  ck_assert_pstr_eq(memchr(test_str_1, test_char, n),
                    s21_memchr(test_str_1, test_char, n));

  test_char = -1000;
  n = 28;
  ck_assert_pstr_eq(memchr(test_str_1, test_char, n),
                    s21_memchr(test_str_1, test_char, n));
}
END_TEST

START_TEST(s21_memchr_test_3) {
  char test_str_1[28] = "test string # test string !";
  unsigned char test_char = '?';
  size_t n = 28;
  ck_assert_pstr_eq(memchr(test_str_1, test_char, n),
                    s21_memchr(test_str_1, test_char, n));
}
END_TEST

START_TEST(s21_memchr_test_4) {
  char test_str_1[28] = "test string # test string !";
  unsigned char test_char = 't';

  size_t n = 0;
  ck_assert_pstr_eq(memchr(test_str_1, test_char, n),
                    s21_memchr(test_str_1, test_char, n));

  n = 1;
  ck_assert_str_eq(memchr(test_str_1, test_char, n),
                   s21_memchr(test_str_1, test_char, n));

  n = 10;
  ck_assert_str_eq(memchr(test_str_1, test_char, n),
                   s21_memchr(test_str_1, test_char, n));

  n = 28;
  ck_assert_str_eq(memchr(test_str_1, test_char, n),
                   s21_memchr(test_str_1, test_char, n));
}
END_TEST

START_TEST(s21_memchr_test_5) {
  char test_str_1[28] = "test string # test string !";
  unsigned char test_char = '#';

  size_t n = 0;
  ck_assert_pstr_eq(memchr(test_str_1, test_char, n),
                    s21_memchr(test_str_1, test_char, n));

  n = 1;
  ck_assert_pstr_eq(memchr(test_str_1, test_char, n),
                    s21_memchr(test_str_1, test_char, n));

  n = 10;
  ck_assert_pstr_eq(memchr(test_str_1, test_char, n),
                    s21_memchr(test_str_1, test_char, n));

  n = 28;
  ck_assert_str_eq(memchr(test_str_1, test_char, n),
                   s21_memchr(test_str_1, test_char, n));
}
END_TEST

START_TEST(s21_memchr_test_6) {
  char test_str_1[28] = "test string # test string !";
  unsigned char test_char = '!';

  size_t n = 0;
  ck_assert_pstr_eq(memchr(test_str_1, test_char, n),
                    s21_memchr(test_str_1, test_char, n));

  n = 1;
  ck_assert_pstr_eq(memchr(test_str_1, test_char, n),
                    s21_memchr(test_str_1, test_char, n));

  n = 10;
  ck_assert_pstr_eq(memchr(test_str_1, test_char, n),
                    s21_memchr(test_str_1, test_char, n));

  n = 28;
  ck_assert_str_eq(memchr(test_str_1, test_char, n),
                   s21_memchr(test_str_1, test_char, n));
}
END_TEST

START_TEST(s21_memchr_test_7) {
  char test_str_1[28] = "test string # test string !";
  unsigned char test_char = 255;
  test_str_1[22] = 255;

  size_t n = 0;
  ck_assert_pstr_eq(memchr(test_str_1, test_char, n),
                    s21_memchr(test_str_1, test_char, n));

  n = 1;
  ck_assert_pstr_eq(memchr(test_str_1, test_char, n),
                    s21_memchr(test_str_1, test_char, n));

  n = 10;
  ck_assert_pstr_eq(memchr(test_str_1, test_char, n),
                    s21_memchr(test_str_1, test_char, n));

  n = 28;
  ck_assert_str_eq(memchr(test_str_1, test_char, n),
                   s21_memchr(test_str_1, test_char, n));
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m s21_memchr_test \033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_memchr_test_1);
  tcase_add_test(tcase, s21_memchr_test_2);
  tcase_add_test(tcase, s21_memchr_test_3);
  tcase_add_test(tcase, s21_memchr_test_4);
  tcase_add_test(tcase, s21_memchr_test_5);
  tcase_add_test(tcase, s21_memchr_test_6);
  tcase_add_test(tcase, s21_memchr_test_7);

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
