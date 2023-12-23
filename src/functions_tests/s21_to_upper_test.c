#include "s21_string_test.h"

START_TEST(s21_to_upper_1) {
  char s1[30] = "Hello, world!";
  char *s2 = s21_to_upper(s1);
  char s3[30] = "HELLO, WORLD!";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_to_upper_2) {
  char s1[30] = "111111111";
  char *s2 = s21_to_upper(s1);
  char s3[30] = "111111111";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_to_upper_3) {
  char s1[30] = "";
  char *s2 = s21_to_upper(s1);
  char s3[30] = "";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_to_upper_4) {
  char *s1 = S21_NULL;
  char *s2 = s21_to_upper(s1);
  char *s3 = S21_NULL;
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_to_upper_5) {
  char s1[30] =
      "!;'/]}{"
      "}";
  char *s2 = s21_to_upper(s1);
  char s3[30] =
      "!;'/]}{"
      "}";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST
START_TEST(s21_to_upper_6) {
  char s1[30] = "hello";
  char *s2 = s21_to_upper(s1);
  char s3[30] = "HELLO";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_to_upper_7) {
  char s1[30] = "hEllO 232323 hi";
  char *s2 = s21_to_upper(s1);
  char s3[30] = "HELLO 232323 HI";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST
Suite *suite(void) {
  Suite *s = suite_create("\033[32m s21_to_upper_test \033[0m");
  TCase *tc = tcase_create("core");
  tcase_add_test(tc, s21_to_upper_1);
  tcase_add_test(tc, s21_to_upper_2);
  tcase_add_test(tc, s21_to_upper_3);
  tcase_add_test(tc, s21_to_upper_4);
  tcase_add_test(tc, s21_to_upper_5);
  tcase_add_test(tc, s21_to_upper_6);
  tcase_add_test(tc, s21_to_upper_7);
  suite_add_tcase(s, tc);
  return s;
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