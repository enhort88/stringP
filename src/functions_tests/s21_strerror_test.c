#include "s21_string_test.h"

START_TEST(s21_strerror_test_1) {
  int test_num_1 = -1;

  ck_assert_pstr_eq(strerror(test_num_1), s21_strerror(test_num_1));
}
END_TEST

START_TEST(s21_strerror_test_2) {
  int test_num_1 = 0;

  ck_assert_pstr_eq(strerror(test_num_1), s21_strerror(test_num_1));
}
END_TEST

START_TEST(s21_strerror_test_3) {
  int test_num_1 = -1;
  int test_num_2 = 140;

  for (; test_num_1 <= test_num_2; test_num_1++) {
    ck_assert_pstr_eq(strerror(test_num_1), s21_strerror(test_num_1));
  }
}
END_TEST

START_TEST(s21_strerror_test_4) {
  int test_num_1 = 133;

  ck_assert_pstr_eq(strerror(test_num_1), s21_strerror(test_num_1));
}
END_TEST

START_TEST(s21_strerror_test_5) {
  int test_num_1 = 134;

  ck_assert_pstr_eq(strerror(test_num_1), s21_strerror(test_num_1));
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m s21_strerror_test \033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_strerror_test_1);
  tcase_add_test(tcase, s21_strerror_test_2);
  tcase_add_test(tcase, s21_strerror_test_3);
  tcase_add_test(tcase, s21_strerror_test_4);
  tcase_add_test(tcase, s21_strerror_test_5);

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
