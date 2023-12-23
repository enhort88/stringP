#include "s21_string_test.h"

START_TEST(s21_sprintf_test_1) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%-+30.2d %-10s a%4cz finish [%-+5d][% d] %%\n";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 15, "banan", 'Q', 55, -33);
  n2 = s21_sprintf(buffer2, strb, 15, "banan", 'Q', 55, -33);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_2) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "Number: %6d\nWord: %s гугель\n";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 42, "hello world");
  n2 = s21_sprintf(buffer2, strb, 42, "hello world");
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_3) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  short sh1 = 32767;
  char strb[300] = "N1: %d N2: % hd %% % d %+ld\n";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 0762, sh1, -2147483647, 2147483648);
  n2 = s21_sprintf(buffer2, strb, 0762, sh1, -2147483647, 2147483648);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_4) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "[%-10c] df [%15c]\n";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, '`', '`');
  n2 = s21_sprintf(buffer2, strb, '`', '`');
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_5) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  short sh2 = -32768;
  char strb[300] = "%- #8.00002f| |% d|%+d|%+hd\n";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 545., 0, -0, sh2);
  n2 = s21_sprintf(buffer2, strb, 545., 0, -0, sh2);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_6) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] =
      "%012u %-9.6u  %-6.9u %- 9.6d  %-+6.9d [%u] [%.u] [%.0u] [%.5u]";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 42949672U, 1285U, 3657U, 1219, 9832, 0, 0, 0, 0);
  n2 = s21_sprintf(buffer2, strb, 42949672U, 1285U, 3657U, 1219, 9832, 0, 0, 0,
                   0);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_7) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] =
      "{%-7.9s} (%-6.9s) [%-.1s] {%-8.2s} (%.s) (%3.s) |%9.6s| |%9.6s| |%9.4s|";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, "first", "dfgdfgdfgdfgfd", "second",
               "fdd dgdgjoi dfgj", "three", "three", "fourtri", "four", "five");
  n2 = s21_sprintf(buffer2, strb, "first", "dfgdfgdfgdfgfd", "second",
                   "fdd dgdgjoi dfgj", "three", "three", "fourtri", "four",
                   "five");
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_8) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%15s j %d";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, "", 15);
  n2 = s21_sprintf(buffer2, strb, "", 15);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_9) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%80ls sdf %% %20ls";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb,
               L"fs€df fs€dfffs€df fs€dffs€df fs€dffs€df fs€df☒\ns€df☒",
               L"€df☒\ns€df☒");
  n2 = s21_sprintf(buffer2, strb,
                   L"fs€df fs€dfffs€df fs€dffs€df fs€dffs€df fs€df☒\ns€df☒",
                   L"€df☒\ns€df☒");
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_10) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  unsigned short ush1 = 65535;
  char strb[300] = "%-15u %025lu short %010hu";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 4294967295U, 18446744073709551615UL, ush1);
  n2 = s21_sprintf(buffer2, strb, 4294967295U, 18446744073709551615UL, ush1);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_11) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%0#20.f %-+15.2f %012f";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, -1234567890.123456, 46463535454.12345,
               0.15000000900003);
  n2 = s21_sprintf(buffer2, strb, -1234567890.123456, 46463535454.12345,
                   0.15000000900003);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_12) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%+012.f [%1u] [%1.u] [%1.0u] [%1.5u]";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 0.15000000900003, 0, 0, 0, 0);
  n2 = s21_sprintf(buffer2, strb, 0.15000000900003, 0, 0, 0, 0);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_13) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] =
      "%9.6d %4.6d %7.7d %4.6d %+9.6d |%1.2d| %-+1.9d %+0d %+8.5d |";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 1557, -3968, 1285, 0, 3121, 0, 148, 148, 148);
  n2 = s21_sprintf(buffer2, strb, 1557, -3968, 1285, 0, 3121, 0, 148, 148, 148);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_14) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%4.6d %4.d %4.d %+d %+.d %0+6d %-8d %-8d  %5d %5d";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 0, -0, -6534, -0, 0, 1, 0, 71928, 0, 716);
  n2 = s21_sprintf(buffer2, strb, 0, -0, -6534, -0, 0, 1, 0, 71928, 0, 716);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_15) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%-20.10e %1.1E %e %e";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 =
      sprintf(buffer1, strb, 12345678e4, 0.0000000005, 12345.6789, __DBL_MAX__);
  n2 = s21_sprintf(buffer2, strb, 12345678e4, 0.0000000005, 12345.6789,
                   __DBL_MAX__);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_16) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%-+12.3f %-+15.10e кратчайш %-+15.10g";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 46463535454.12345, 46463535454.1234567890,
               46463535454.1234567890);
  n2 = s21_sprintf(buffer2, strb, 46463535454.12345, 46463535454.1234567890,
                   46463535454.1234567890);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_17) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%f %e кратчайш %g";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 12345.6789, 12345.6789, 12345.6789);
  n2 = s21_sprintf(buffer2, strb, 12345.6789, 12345.6789, 12345.6789);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_18) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%f %e кратчайш []->%g []->%g [.]->%.g [.2]->%.2g";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 54321.123, 54321.123, 54321.123, 0.123, 0.123,
               0.123);
  n2 = s21_sprintf(buffer2, strb, 54321.123, 54321.123, 54321.123, 0.123, 0.123,
                   0.123);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_19) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%f %e кратч без реш с нулями %g %g %.g %.2g";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 54321., 54321., 54321., 0., 0., 0.);
  n2 = s21_sprintf(buffer2, strb, 54321., 54321., 54321., 0., 0., 0.);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_20) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] =
      "%f %e с нулями # кратч  [#]->%#g [#]->%#g [#.]->%#.g [#.2]->%#.2g";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 4321., 54321., 54321., 0.123, 0.123, 0.123);
  n2 = s21_sprintf(buffer2, strb, 4321., 54321., 54321., 0.123, 0.123, 0.123);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_21) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%.8f %.8e кратчайш %.8g | %f %e кратчайш %G";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 12345.6789, 12345.6789, 12345.6789,
               0.0000123456789, 0.0000123456789, 0.0000123456789);
  n2 = s21_sprintf(buffer2, strb, 12345.6789, 12345.6789, 12345.6789,
                   0.0000123456789, 0.0000123456789, 0.0000123456789);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_22) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%-20.10g %1.1G %g %g";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 12345678e4, 0.0000000005, 12345.6789, 15.2);
  n2 = s21_sprintf(buffer2, strb, 12345678e4, 0.0000000005, 12345.6789, 15.2);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_23) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "x %-9.7x X %9.7X %09X o %-9.7o o %09o %9.7o";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 300, 155, 300, 199, 144, 12);
  n2 = s21_sprintf(buffer2, strb, 300, 155, 300, 199, 144, 12);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_24) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "x %#-9.7x X %#9.7X %#09X o %#-9.7o o %#09o %#9.7o %#9.3o";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 300, 155, 300, 199, 144, 12, 125);
  n2 = s21_sprintf(buffer2, strb, 300, 155, 300, 199, 144, 12, 125);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_25) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%p |%5.2f| |%*.*f| %25p %.o";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, &strb, 4325.798, 5, 2, 4325.798, &strb, 0);
  n2 = s21_sprintf(buffer2, strb, &strb, 4325.798, 5, 2, 4325.798, &strb, 0);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_26) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "Lf %.8Lf %.2Lf %.2Lf";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 123.45678l, -123.45678l, 0.999l);
  n2 = s21_sprintf(buffer2, strb, 123.45678l, -123.45678l, 0.999l);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_27) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%Lf %Le %Lg";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 12345.6789l, 12345.6789l, 12345.6789l);
  n2 = s21_sprintf(buffer2, strb, 12345.6789l, 12345.6789l, 12345.6789l);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

START_TEST(s21_sprintf_test_28) {
  setlocale(0, "");
  int n1 = 0, n2 = 0;
  char strb[300] = "%Lf %Le []->%Lg []->%Lg [.]->%.Lg [.2]->%.2Lg";
  char buffer1[500] = {'0'};
  char buffer2[500] = {'0'};
  n1 = sprintf(buffer1, strb, 54321.123l, 54321.123l, 54321.123l, 0.123l,
               0.123l, 0.123l);
  n2 = s21_sprintf(buffer2, strb, 54321.123l, 54321.123l, 54321.123l, 0.123l,
                   0.123l, 0.123l);
  ck_assert_int_eq(n1, n2);
  ck_assert_pstr_eq(buffer1, buffer2);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m s21_sprintf_test \033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_sprintf_test_1);
  tcase_add_test(tcase, s21_sprintf_test_2);
  tcase_add_test(tcase, s21_sprintf_test_3);
  tcase_add_test(tcase, s21_sprintf_test_4);
  tcase_add_test(tcase, s21_sprintf_test_5);
  tcase_add_test(tcase, s21_sprintf_test_6);
  tcase_add_test(tcase, s21_sprintf_test_7);
  tcase_add_test(tcase, s21_sprintf_test_8);
  tcase_add_test(tcase, s21_sprintf_test_9);
  tcase_add_test(tcase, s21_sprintf_test_10);
  tcase_add_test(tcase, s21_sprintf_test_11);
  tcase_add_test(tcase, s21_sprintf_test_12);
  tcase_add_test(tcase, s21_sprintf_test_13);
  tcase_add_test(tcase, s21_sprintf_test_14);
  tcase_add_test(tcase, s21_sprintf_test_15);
  tcase_add_test(tcase, s21_sprintf_test_16);
  tcase_add_test(tcase, s21_sprintf_test_17);
  tcase_add_test(tcase, s21_sprintf_test_18);
  tcase_add_test(tcase, s21_sprintf_test_19);
  tcase_add_test(tcase, s21_sprintf_test_20);
  tcase_add_test(tcase, s21_sprintf_test_21);
  tcase_add_test(tcase, s21_sprintf_test_22);
  tcase_add_test(tcase, s21_sprintf_test_23);
  tcase_add_test(tcase, s21_sprintf_test_24);
  tcase_add_test(tcase, s21_sprintf_test_25);
  tcase_add_test(tcase, s21_sprintf_test_26);
  tcase_add_test(tcase, s21_sprintf_test_27);
  tcase_add_test(tcase, s21_sprintf_test_28);

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
