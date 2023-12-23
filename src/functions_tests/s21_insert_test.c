#include "s21_string_test.h"

START_TEST(s21_insert_1) {
  char s1[] = "bimp bimp bimp";
  char s2[] = " hello, world!";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "bimp bimp bimp hello, world!";
  s4 = s21_insert(s1, s2, 14);
  ck_assert_str_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(s21_insert_2) {
  char s1[] = "";
  char s2[] = "";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "";
  s4 = s21_insert(s1, s2, 0);
  ck_assert_str_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(s21_insert_3) {
  char s1[] = "bimp bimp bimp";
  char s2[] = " hello, world!";
  char *s3 = {0};
  char *s4 = {0};
  s3 = S21_NULL;
  s4 = s21_insert(s1, s2, 120);
  ck_assert(s3 == s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(s21_insert_4) {
  char s2[] = " hello, world!";
  char *s3 = {0};
  char *s4 = {0};
  s3 = S21_NULL;
  s4 = s21_insert(S21_NULL, s2, 120);
  ck_assert(s3 == s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(s21_insert_5) {
  char s1[] = "bimp bimp bimp FREE M";
  char s2[] = " hello, world!";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "bimp bimp bimp hello, world! FREE M";
  s4 = s21_insert(s1, s2, 14);
  ck_assert_str_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

Suite *suite(void) {
  Suite *s = suite_create("\033[32m s21_insert_test \033[0m");
  TCase *tc = tcase_create("insert_tc");

  tcase_add_test(tc, s21_insert_1);
  tcase_add_test(tc, s21_insert_2);
  tcase_add_test(tc, s21_insert_3);
  tcase_add_test(tc, s21_insert_4);
  tcase_add_test(tc, s21_insert_5);

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