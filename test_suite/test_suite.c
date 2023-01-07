#include "core.h"
#include "int_assertions.h"
#include "str_assertions.h"


TestSuite* ts;

#define TEST_START                          ts = TestSuite_init();
#define TEST_END                            TestSuite_commitCase(ts);\
                                            TestSuite_print(ts);\
                                            TestSuite_deconstruct(ts)

#define ADD_CASE(func, name)                TestSuite_newCase(ts, name); func() 
#define TEST_PASS(msg)                      TestSuite_pass(ts, msg)
#define TEST_FAIL(msg)                      TestSuite_fail(ts, msg)   
// Below is for adding formatting ala printf("%d", 1) to a manual pass/fail message
#define TEST_PASS_FMT(msg, ...)             TestSuite_pass(ts, msg, __VA_ARGS__)
#define TEST_FAIL_FMT(msg, ...)             TestSuite_fail(ts, msg, __VA_ARGS__)            


#define ASSERT_EQUAL_INT(val1, val2)        assert_equal_int(ts, val1, val2)
#define ASSERT_NOT_EQUAL_INT(val1, val2)    assert_not_equal_int(ts, val1, val2)
#define ASSERT_GREATER_THAN_INT(val1, val2) assert_greater_than_int(ts, val1, val2)

#define ASSERT_EQUAL_STR(val1, val2)        assert_equal_str(ts, val1, val2)
#define ASSERT_NOT_EQUAL_STR(val1, val2)    assert_not_equal_str(ts, val1, val2)