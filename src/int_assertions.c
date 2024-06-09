#include <stdbool.h>
#include "int_assertions.h"
#include "assertion_constants.h"


/* ============================================================================
 *  INTEGER ASSERTIONS
 * ========================================================================= */
// Compares two ints for exact equality
int assert_equal_int(TestSuite* ts, int val1, int val2, char* file_name, long line_num)
{
    char msg[MSG_BUFF_SIZE];

    if (val1 == val2) {
        snprintf(msg, MSG_BUFF_SIZE, "%d == %d", val1, val2);
        return TestSuite_pass(ts, file_name, line_num, msg);
    }
    else {
        snprintf(msg, MSG_BUFF_SIZE, "%d != %d", val1, val2);
        return TestSuite_fail(ts, file_name, line_num, msg);
    }
}

// Compare two ints to assess their inequality
int assert_not_equal_int(TestSuite* ts, int val1, int val2, char* file_name, long line_num)
{

    char msg[MSG_BUFF_SIZE];

    if (val1 != val2) {
        snprintf(msg, MSG_BUFF_SIZE, "%d != %d", val1, val2);
        return TestSuite_pass(ts, file_name, line_num, msg);
    }
    else {
        snprintf(msg, MSG_BUFF_SIZE, "%d == %d", val1, val2);
        return TestSuite_fail(ts, file_name, line_num, msg);
    }
}

// Compare two ints and assert that val1 > val2
int assert_greater_than_int(TestSuite* ts, int val1, int val2, char* file_name, long line_num)
{

    char msg[MSG_BUFF_SIZE];

    if (val1 > val2) {
        snprintf(msg, MSG_BUFF_SIZE, "%d > %d", val1, val2);
        return TestSuite_pass(ts, file_name, line_num, msg);
    }
    else {
        snprintf(msg, MSG_BUFF_SIZE, "%d <= %d", val1, val2);
        return TestSuite_fail(ts, file_name, line_num, msg);
    }
}


/* ============================================================================
 *  BOOLEAN ASSERTIONS
 * ========================================================================= */

// Ensure value is true
int assert_true(TestSuite* ts, int val1, char* file_name, long line_num)
{

    char msg[MSG_BUFF_SIZE];

    if (val1) {
        snprintf(msg, MSG_BUFF_SIZE, "%d is true", val1);
        return TestSuite_pass(ts, file_name, line_num, msg);
    }
    else {
        snprintf(msg, MSG_BUFF_SIZE, "%d is false", val1);
        return TestSuite_fail(ts, file_name, line_num, msg);
    }
}

// Ensure value is false
int assert_false(TestSuite* ts, int val1, char* file_name, long line_num)
{
    char msg[MSG_BUFF_SIZE];

    if (!val1) {
        snprintf(msg, MSG_BUFF_SIZE, "%d is false", val1);
        return TestSuite_pass(ts, file_name, line_num, msg);
    }
    else {
        snprintf(msg, MSG_BUFF_SIZE, "%d is true", val1);
        return TestSuite_fail(ts, file_name, line_num, msg);
    }
}


/* ============================================================================
 *  LONG ASSERTIONS
 * ========================================================================= */

// Compares two longs for exact equality
int assert_equal_long(TestSuite* ts, long val1, long val2, char* file_name, long line_num)
{
    char msg[MSG_BUFF_SIZE];

    if (val1 == val2) {
        snprintf(msg, MSG_BUFF_SIZE, "%ld == %ld", val1, val2);
        return TestSuite_pass(ts, file_name, line_num, msg);
    }
    else {
        snprintf(msg, MSG_BUFF_SIZE, "%ld != %ld", val1, val2);
        return TestSuite_fail(ts, file_name, line_num, msg);
    }
}

// Compare two longs to assess their inequality
int assert_not_equal_long(TestSuite* ts, long val1, long val2, char* file_name, long line_num)
{

    char msg[MSG_BUFF_SIZE];

    if (val1 != val2) {
        snprintf(msg, MSG_BUFF_SIZE, "%ld != %ld", val1, val2);
        return TestSuite_pass(ts, file_name, line_num, msg);
    }
    else {
        snprintf(msg, MSG_BUFF_SIZE, "%ld == %ld", val1, val2);
        return TestSuite_fail(ts, file_name, line_num, msg);
    }
}

// Compare two longs and assert that val1 > val2
int assert_greater_than_long(TestSuite* ts, long val1, long val2, char* file_name, long line_num)
{

    char msg[MSG_BUFF_SIZE];

    if (val1 > val2) {
        snprintf(msg, MSG_BUFF_SIZE, "%ld > %ld", val1, val2);
        return TestSuite_pass(ts, file_name, line_num, msg);
    }
    else {
        snprintf(msg, MSG_BUFF_SIZE, "%ld <= %ld", val1, val2);
        return TestSuite_fail(ts, file_name, line_num, msg);
    }
}

