#include "s21_string_test.h"

START_TEST(s21_strchr_test_1) {
  char *test_str_1 = NULL;
  unsigned char test_char = 't';
  s21_strchr(test_str_1, test_char);
}
END_TEST

START_TEST(s21_strchr_test_2) {
  char test_str_1[] = "";

  int test_char = 't';
  ck_assert_pstr_eq(strchr(test_str_1, test_char),
                    s21_strchr(test_str_1, test_char));
}
END_TEST

START_TEST(s21_strchr_test_3) {
  char test_str_1[28] = "test string # test string !";

  int test_char = '?';
  ck_assert_pstr_eq(strchr(test_str_1, test_char),
                    s21_strchr(test_str_1, test_char));

  test_char = 1000;
  ck_assert_pstr_eq(strchr(test_str_1, test_char),
                    s21_strchr(test_str_1, test_char));

  test_char = -1000;
  ck_assert_pstr_eq(strchr(test_str_1, test_char),
                    s21_strchr(test_str_1, test_char));
}
END_TEST

START_TEST(s21_strchr_test_4) {
  char test_str_1[28] = "test string # test string !";

  int test_char = 't';
  ck_assert_pstr_eq(strchr(test_str_1, test_char),
                    s21_strchr(test_str_1, test_char));

  test_char = '#';
  ck_assert_pstr_eq(strchr(test_str_1, test_char),
                    s21_strchr(test_str_1, test_char));

  test_char = '!';
  ck_assert_pstr_eq(strchr(test_str_1, test_char),
                    s21_strchr(test_str_1, test_char));
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m s21_strchr_test \033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_strchr_test_1);
  tcase_add_test(tcase, s21_strchr_test_2);
  tcase_add_test(tcase, s21_strchr_test_3);
  tcase_add_test(tcase, s21_strchr_test_4);

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
