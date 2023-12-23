#include "s21_string_test.h"

START_TEST(s21_to_lower_1) {
  char s1[30] = "Hello, world!";
  char *s2 = s21_to_lower(s1);
  char s3[30] = "hello, world!";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_to_lower_2) {
  char s1[30] = "111111111";
  char *s2 = s21_to_lower(s1);
  char s3[30] = "111111111";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_to_lower_3) {
  char s1[30] = "";
  char *s2 = s21_to_lower(s1);
  char s3[30] = "";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_to_lower_4) {
  char *s1 = S21_NULL;
  char *s2 = s21_to_upper(s1);
  char *s3 = S21_NULL;
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_to_lower_5) {
  char s1[30] =
      "!;'/]}{"
      "}";
  char *s2 = s21_to_lower(s1);
  char s3[30] =
      "!;'/]}{"
      "}";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_to_lower_6) {
  char s1[30] = "HELLO";
  char *s2 = s21_to_lower(s1);
  char s3[30] = "hello";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(s21_to_lower_7) {
  char s1[30] = "HellO 12 HI";
  char *s2 = s21_to_lower(s1);
  char s3[30] = "hello 12 hi";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST
Suite *suite(void) {
  Suite *s = suite_create("\033[32m s21_to_lower_test \033[0m");
  TCase *tc = tcase_create("core");
  tcase_add_test(tc, s21_to_lower_1);
  tcase_add_test(tc, s21_to_lower_2);
  tcase_add_test(tc, s21_to_lower_3);
  tcase_add_test(tc, s21_to_lower_4);
  tcase_add_test(tc, s21_to_lower_5);
  tcase_add_test(tc, s21_to_lower_6);
  tcase_add_test(tc, s21_to_lower_7);
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