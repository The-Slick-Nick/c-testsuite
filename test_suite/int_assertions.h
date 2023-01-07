/*
int_assertions.h

Assertion functions revolving around integers
*/
#include <stdbool.h>
#include "core.h"

// Compares two integers to assess their equality
int assert_equal_int(TestSuite* ts, int val1, int val2)
{
    char* msg = NULL;
    int return_code;
    if(val1 == val2)
    {
        msg = format_string("%d == %d", val1, val2);
        return_code = TestSuite_pass(ts, msg);
    }
    else
    {
        char* msg = format_string("%d != %d", val1, val2);
        return_code = TestSuite_fail(ts, msg);
    }
    free(msg);
    return return_code;
}

// Compare two integers to assess their inequality
int assert_not_equal_int(TestSuite* ts, int val1, int val2)
{
    char* msg = NULL;
    int return_code;
    if(val1 != val2)
    {
        msg = format_string("%d != %d", val1, val2);
        return_code = TestSuite_pass(ts, msg);
    }
    else
    {
        msg = format_string("%d == %d", val1, val2);
        return_code = TestSuite_fail(ts, msg);
    }
    free(msg);
    return return_code;
}

// Compare two integers and assert that val1 > val2
int assert_greater_than_int(TestSuite* ts, int val1, int val2)
{
    char* msg = NULL;
    int return_code;
    if (val1 > val2)
    {
        msg = format_string("%d > %d", val1, val2);
        return_code = TestSuite_pass(ts, msg);
    }
    else if (val1 == val2)
    {
        msg = format_string("%d == %d", val1, val2);
        return_code = TestSuite_fail(ts, msg);
    }
    else
    {
        msg = format_string("%d < %d", val1, val2);
        return_code = TestSuite_fail(ts, msg);
    }
    free(msg);
    return return_code;
}


// Tests that a boolean value is true
int assert_true(TestSuite* ts, bool val)
{
    if (val)
        return TestSuite_pass(ts, "Value is true");
    else
        return TestSuite_fail(ts, "Value is false");
}

// Tests that a boolean value is false
int assert_false(TestSuite* ts, bool val)
{
    if (!val)
        return TestSuite_pass(ts, "Value is false");
    else
        return TestSuite_pass(ts, "Value is true");
}