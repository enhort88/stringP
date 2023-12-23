#include "s21_string_test.h"

START_TEST(s21_trim_1) {
  char s1[] = " bimp ";
  char s2[] = " ";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "bimp";
  s4 = s21_trim(s1, s2);
  ck_assert_str_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(s21_trim_2) {
  char s1[] = "      bimp";
  char *s2 = " ";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "bimp";
  s4 = s21_trim(s1, s2);
  ck_assert_pstr_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(s21_trim_3) {
  char s1[] = "bimp  ";
  char *s2 = " ";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "bimp";
  s4 = s21_trim(s1, s2);
  ck_assert_pstr_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(s21_trim_4) {
  char s1[] = "///i ooOO))";
  char *s2 = "/";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "i ooOO))";
  s4 = s21_trim(s1, s2);
  ck_assert_pstr_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(s21_trim_5) {
  char s1[] = "pull";
  char *s2 = "pull";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "";
  s4 = s21_trim(s1, s2);
  ck_assert_pstr_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(s21_trim_6) {
  char *s2 = "";
  char *s3 = {0};
  char *s4 = {0};
  s4 = s21_trim(S21_NULL, s2);
  ck_assert_pstr_eq(s3, S21_NULL);
  if (s4) free(s4);
}
END_TEST

START_TEST(s21_trim_7) {
  char s1[] = " bimp ";
  char s2[] = "p";
  char *s3 = {0};
  char *s4 = {0};
  s3 = " bimp ";
  s4 = s21_trim(s1, s2);
  ck_assert_str_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(s21_trim_8) {
  char s2[] = "pull";
  char *s4 = {0};
  s4 = s21_trim(S21_NULL, s2);
  ck_assert(S21_NULL == s4);
  if (s4) free(s4);
}
END_TEST

Suite *suite(void) {
  Suite *s = suite_create("\033[32m s21_trim_test \033[0m");
  TCase *tc = tcase_create("core");
  tcase_add_test(tc, s21_trim_1);
  tcase_add_test(tc, s21_trim_2);
  tcase_add_test(tc, s21_trim_3);
  tcase_add_test(tc, s21_trim_4);
  tcase_add_test(tc, s21_trim_5);
  tcase_add_test(tc, s21_trim_6);
  tcase_add_test(tc, s21_trim_7);
  tcase_add_test(tc, s21_trim_8);
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