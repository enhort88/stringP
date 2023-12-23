#include "s21_string_test.h"

START_TEST(s21_memcpy_test_1) {
  char *test_str_1 = NULL;
  char *test_str_2 = NULL;
  size_t n = 28;
  s21_memcpy(test_str_1, test_str_2, n);
}
END_TEST

START_TEST(s21_memcpy_test_2) {
  char test_str_1[28] = "test string # test string !";
  char *test_str_2 = NULL;
  size_t n = 28;
  s21_memcpy(test_str_1, test_str_2, n);
}
END_TEST

START_TEST(s21_memcpy_test_3) {
  char *test_str_1 = NULL;
  char test_str_2[28] = "test string # test string !";
  size_t n = 28;
  s21_memcpy(test_str_1, test_str_2, n);
}
END_TEST

START_TEST(s21_memcpy_test_5) {
  char test_str_1[28] = "test string # test string !";
  char test_str_2[28] = "asdf qwertg # test string !";

  size_t n = 0;
  ck_assert_mem_eq(memcpy(test_str_1, test_str_2, n),
                   s21_memcpy(test_str_1, test_str_2, n), strlen(test_str_1));

  n = 10;
  ck_assert_mem_eq(memcpy(test_str_1, test_str_2, n),
                   s21_memcpy(test_str_1, test_str_2, n), strlen(test_str_1));

  n = 28;
  ck_assert_mem_eq(memcpy(test_str_1, test_str_2, n),
                   s21_memcpy(test_str_1, test_str_2, n), strlen(test_str_1));
}
END_TEST

START_TEST(s21_memcpy_test_6) {
  char test_str_1[28] = "asdf qwertg # test string !";
  char test_str_2[] = "test string #";

  size_t n = 0;
  ck_assert_mem_eq(memcpy(test_str_1, test_str_2, n),
                   s21_memcpy(test_str_1, test_str_2, n), strlen(test_str_1));

  n = 10;
  ck_assert_mem_eq(memcpy(test_str_1, test_str_2, n),
                   s21_memcpy(test_str_1, test_str_2, n), strlen(test_str_1));

  n = 28;
  ck_assert_mem_eq(memcpy(test_str_1, test_str_2, n),
                   s21_memcpy(test_str_1, test_str_2, n), strlen(test_str_1));
}
END_TEST

START_TEST(s21_memcpy_test_7) {
  char test_str_1[] = "test string #";
  char test_str_2[28] = "asdf qwertg # test string !";

  size_t n = 0;
  ck_assert_mem_eq(memcpy(test_str_1, test_str_2, n),
                   s21_memcpy(test_str_1, test_str_2, n), strlen(test_str_1));

  n = 10;
  ck_assert_mem_eq(memcpy(test_str_1, test_str_2, n),
                   s21_memcpy(test_str_1, test_str_2, n), strlen(test_str_1));

  // n = 28;
  n = 14;
  ck_assert_mem_eq(memcpy(test_str_1, test_str_2, n),
                   s21_memcpy(test_str_1, test_str_2, n), strlen(test_str_1));
}
END_TEST

START_TEST(s21_memcpy_test_8) {
  char test_str_1[28] = "test string # test string #";
  char test_str_2[28] = "test string # test string !";
  test_str_1[22] = 254;
  test_str_2[22] = 255;

  size_t n = 0;
  ck_assert_mem_eq(memcpy(test_str_1, test_str_2, n),
                   s21_memcpy(test_str_1, test_str_2, n), strlen(test_str_1));

  n = 10;
  ck_assert_mem_eq(memcpy(test_str_1, test_str_2, n),
                   s21_memcpy(test_str_1, test_str_2, n), strlen(test_str_1));

  n = 28;
  ck_assert_mem_eq(memcpy(test_str_1, test_str_2, n),
                   s21_memcpy(test_str_1, test_str_2, n), strlen(test_str_1));
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m s21_memcpy_test \033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_memcpy_test_1);
  tcase_add_test(tcase, s21_memcpy_test_2);
  tcase_add_test(tcase, s21_memcpy_test_3);
  tcase_add_test(tcase, s21_memcpy_test_5);
  tcase_add_test(tcase, s21_memcpy_test_6);
  tcase_add_test(tcase, s21_memcpy_test_7);
  tcase_add_test(tcase, s21_memcpy_test_8);

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
