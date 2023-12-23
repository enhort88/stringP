#include "s21_string_test.h"

START_TEST(s21_strtok_test_1) {
  char *test_str_1 = NULL;
  char *test_str_2 = NULL;
  s21_strtok(test_str_1, test_str_2);
}
END_TEST

START_TEST(s21_strtok_test_2) {
  char test_str_1[28] = "test string # test string !";
  char *test_str_2 = NULL;
  s21_strtok(test_str_1, test_str_2);
}
END_TEST

START_TEST(s21_strtok_test_3) {
  char *test_str_1 = NULL;
  char test_str_2[28] = "test string # test string !";
  s21_strtok(test_str_1, test_str_2);
}
END_TEST

START_TEST(s21_strtok_test_4) {
  char test_str_11[28] = "";
  char test_str_12[] = "";
  char test_str_21[28] = "";
  char test_str_22[] = "";

  char *test_str_3 = strtok(test_str_11, test_str_12);
  char *test_str_4 = s21_strtok(test_str_21, test_str_22);
  ck_assert_pstr_eq(test_str_3, test_str_4);

  while ((test_str_3 != NULL) || (test_str_4 != NULL)) {
    test_str_3 = strtok(S21_NULL, test_str_12);
    test_str_4 = s21_strtok(S21_NULL, test_str_22);
    ck_assert_pstr_eq(test_str_3, test_str_4);
  }

  ck_assert_pstr_eq(test_str_3, test_str_4);
}
END_TEST

START_TEST(s21_strtok_test_5) {
  char test_str_11[28] = "test string # test string !";
  char test_str_12[] = "";
  char test_str_21[28] = "test string # test string !";
  char test_str_22[] = "";

  char *test_str_3 = strtok(test_str_11, test_str_12);
  char *test_str_4 = s21_strtok(test_str_21, test_str_22);
  ck_assert_pstr_eq(test_str_3, test_str_4);

  while ((test_str_3 != NULL) || (test_str_4 != NULL)) {
    test_str_3 = strtok(S21_NULL, test_str_12);
    test_str_4 = s21_strtok(S21_NULL, test_str_22);
    ck_assert_pstr_eq(test_str_3, test_str_4);
  }

  ck_assert_pstr_eq(test_str_3, test_str_4);
}
END_TEST

START_TEST(s21_strtok_test_6) {
  char test_str_11[28] = "";
  char test_str_12[] = "/";
  char test_str_21[28] = "";
  char test_str_22[] = "/";

  char *test_str_3 = strtok(test_str_11, test_str_12);
  char *test_str_4 = s21_strtok(test_str_21, test_str_22);
  ck_assert_pstr_eq(test_str_3, test_str_4);

  while ((test_str_3 != NULL) || (test_str_4 != NULL)) {
    test_str_3 = strtok(S21_NULL, test_str_12);
    test_str_4 = s21_strtok(S21_NULL, test_str_22);
    ck_assert_pstr_eq(test_str_3, test_str_4);
  }

  ck_assert_pstr_eq(test_str_3, test_str_4);
}
END_TEST

START_TEST(s21_strtok_test_7) {
  char test_str_11[28] = "test string # test string !";
  char test_str_12[] = "/";
  char test_str_21[28] = "test string # test string !";
  char test_str_22[] = "/";

  char *test_str_3 = strtok(test_str_11, test_str_12);
  char *test_str_4 = s21_strtok(test_str_21, test_str_22);
  ck_assert_pstr_eq(test_str_3, test_str_4);

  while ((test_str_3 != NULL) || (test_str_4 != NULL)) {
    test_str_3 = strtok(S21_NULL, test_str_12);
    test_str_4 = s21_strtok(S21_NULL, test_str_22);
    ck_assert_pstr_eq(test_str_3, test_str_4);
  }

  ck_assert_pstr_eq(test_str_3, test_str_4);
}
END_TEST

START_TEST(s21_strtok_test_8) {
  char test_str_11[] = "test/ string/ # /test str/ing !";
  char test_str_12[] = "/";
  char test_str_21[] = "test/ string/ # /test str/ing !";
  char test_str_22[] = "/";

  char *test_str_3 = strtok(test_str_11, test_str_12);
  char *test_str_4 = s21_strtok(test_str_21, test_str_22);
  ck_assert_pstr_eq(test_str_3, test_str_4);

  while ((test_str_3 != NULL) || (test_str_4 != NULL)) {
    test_str_3 = strtok(S21_NULL, test_str_12);
    test_str_4 = s21_strtok(S21_NULL, test_str_22);
    ck_assert_pstr_eq(test_str_3, test_str_4);
  }

  ck_assert_pstr_eq(test_str_3, test_str_4);
}
END_TEST

START_TEST(s21_strtok_test_9) {
  char test_str_11[] = "/test/ string/ # /test str/ing !/";
  char test_str_12[] = "/";
  char test_str_21[] = "/test/ string/ # /test str/ing !/";
  char test_str_22[] = "/";

  char *test_str_3 = strtok(test_str_11, test_str_12);
  char *test_str_4 = s21_strtok(test_str_21, test_str_22);
  ck_assert_pstr_eq(test_str_3, test_str_4);

  while ((test_str_3 != NULL) || (test_str_4 != NULL)) {
    test_str_3 = strtok(S21_NULL, test_str_12);
    test_str_4 = s21_strtok(S21_NULL, test_str_22);
    ck_assert_pstr_eq(test_str_3, test_str_4);
  }

  ck_assert_pstr_eq(test_str_3, test_str_4);
}
END_TEST

START_TEST(s21_strtok_test_10) {
  char test_str_11[] = "/test/ string/ # /test str/ing !/";
  char test_str_12[] = "$/";
  char test_str_21[] = "/test/ string/ # /test str/ing !/";
  char test_str_22[] = "$/";

  char *test_str_3 = strtok(test_str_11, test_str_12);
  char *test_str_4 = s21_strtok(test_str_21, test_str_22);
  ck_assert_pstr_eq(test_str_3, test_str_4);

  while ((test_str_3 != NULL) || (test_str_4 != NULL)) {
    test_str_3 = strtok(S21_NULL, test_str_12);
    test_str_4 = s21_strtok(S21_NULL, test_str_22);
    ck_assert_pstr_eq(test_str_3, test_str_4);
  }

  ck_assert_pstr_eq(test_str_3, test_str_4);
}
END_TEST

START_TEST(s21_strtok_test_11) {
  char test_str_11[] = "/test/ string/ # /test str/ing !#!";
  char test_str_12[] = "e/#t!";
  char test_str_21[] = "/test/ string/ # /test str/ing !#!";
  char test_str_22[] = "e/#t!";

  char *test_str_3 = strtok(test_str_11, test_str_12);
  char *test_str_4 = s21_strtok(test_str_21, test_str_22);
  ck_assert_pstr_eq(test_str_3, test_str_4);

  while ((test_str_3 != NULL) || (test_str_4 != NULL)) {
    test_str_3 = strtok(S21_NULL, test_str_12);
    test_str_4 = s21_strtok(S21_NULL, test_str_22);
    ck_assert_pstr_eq(test_str_3, test_str_4);
  }

  ck_assert_pstr_eq(test_str_3, test_str_4);
}
END_TEST

START_TEST(s21_strtok_test_12) {
  char test_str_11[] = "/test/ string/ # /test str/ing !#!";
  char test_str_12[] = "e/#t!";
  char test_str_21[] = "/test/ string/ # /test str/ing !#!";
  char test_str_22[] = "e/#t!";
  test_str_11[22] = 255;
  test_str_12[2] = 255;
  test_str_21[22] = 255;
  test_str_22[2] = 255;

  char *test_str_3 = strtok(test_str_11, test_str_12);
  char *test_str_4 = s21_strtok(test_str_21, test_str_22);
  ck_assert_pstr_eq(test_str_3, test_str_4);

  while ((test_str_3 != NULL) || (test_str_4 != NULL)) {
    test_str_3 = strtok(S21_NULL, test_str_12);
    test_str_4 = s21_strtok(S21_NULL, test_str_22);
    ck_assert_pstr_eq(test_str_3, test_str_4);
  }

  ck_assert_pstr_eq(test_str_3, test_str_4);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m s21_strtok_test \033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_strtok_test_1);
  tcase_add_test(tcase, s21_strtok_test_2);
  tcase_add_test(tcase, s21_strtok_test_3);
  tcase_add_test(tcase, s21_strtok_test_4);
  tcase_add_test(tcase, s21_strtok_test_5);
  tcase_add_test(tcase, s21_strtok_test_6);
  tcase_add_test(tcase, s21_strtok_test_7);
  tcase_add_test(tcase, s21_strtok_test_8);
  tcase_add_test(tcase, s21_strtok_test_9);
  tcase_add_test(tcase, s21_strtok_test_10);
  tcase_add_test(tcase, s21_strtok_test_11);
  tcase_add_test(tcase, s21_strtok_test_12);

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
