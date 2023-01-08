#include "core.h"
#include "int_assertions.h"
#include "str_assertions.h"
#include "float_assertions.h"
#include "double_assertions.h"

#define EWENIT_START                            ts = TestSuite_init();
#define TEST_START                              EWENIT_START
#define EWENIT_END                              TestSuite_commitCase(ts);\
                                                TestSuite_print(ts);\
                                                TestSuite_deconstruct(ts)
#define TEST_END                                EWENIT_END

#define ADD_CASE(func, name)                    TestSuite_newCase(ts, name); func() 
#define TEST_PASS(msg)                          TestSuite_pass(ts, msg)
#define TEST_FAIL(msg)                          TestSuite_fail(ts, msg)   
// Below is for adding formatting ala printf("%d", 1) to a manual pass/fail message
#define TEST_PASS_FMT(msg, ...)                 TestSuite_pass(ts, msg, __VA_ARGS__)
#define TEST_FAIL_FMT(msg, ...)                 TestSuite_fail(ts, msg, __VA_ARGS__)

#define ERROR_CHECK(x)                          if (x < 0) do \
                                                   {printf("ASSERTION UNSUCCESSFUL\n");}\
                                                   while (0)

#define ASSERT_EQUAL_INT(val1, val2)            ERROR_CHECK(assert_equal_int(ts, val1, val2))
#define ASSERT_NOT_EQUAL_INT(val1, val2)        ERROR_CHECK(assert_not_equal_int(ts, val1, val2))
#define ASSERT_GREATER_THAN_INT(val1, val2)     ERROR_CHECK(assert_greater_than_int(ts, val1, val2))
#define ASSERT_EQUAL_STR(val1, val2)            ERROR_CHECK(assert_equal_str(ts, val1, val2))
#define ASSERT_NOT_EQUAL_STR(val1, val2)        ERROR_CHECK(assert_not_equal_str(ts, val1, val2))
#define ASSERT_EQUAL_FLOAT(val1, val2)          ERROR_CHECK(assert_equal_float(ts, val1, val2))
#define ASSERT_NOT_EQUAL_FLOAT(val1, val2)      ERROR_CHECK(assert_not_equal_float(ts, val1, val2))
#define ASSERT_GREATER_THAN_FLOAT(val1, val2)   ERROR_CHECK(assert_greater_than_float(ts, val1, val2))
#define ASSERT_EQUAL_DOUBLE(val1, val2)         ERROR_CHECK(assert_equal_double(ts, val1, val2))
#define ASSERT_NOT_EQUAL_DOUBLE(val1, val2)     ERROR_CHECK(assert_not_equal_double(ts, val1, val2))
#define ASSERT_GREATER_THAN_DOUBLE(val1, val2)  ERROR_CHECK(assert_greater_than_double(ts, val1, val2))
