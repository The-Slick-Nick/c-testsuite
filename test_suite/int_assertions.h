/*
int_assertions.h

Assertion functions revolving around integers
*/
#include <stdbool.h>
#include "core.h"

// Compares two integers to assess their equality
int assert_equal_int(TestSuite* ts, int val1, int val2)
{
    if(val1 == val2)
        return TestSuite_pass(ts, "%d == %d", val1, val2);
    else
        return TestSuite_fail(ts, "%d != %d", val1, val2);
}

// Compare two integers to assess their inequality
int assert_not_equal_int(TestSuite* ts, int val1, int val2)
{
    if(val1 != val2)
        return TestSuite_pass(ts, "%d != %d", val1, val2);
    else
        return TestSuite_fail(ts, "%d == %d", val1, val2);
}

// Compare two integers and assert that val1 > val2
int assert_greater_than_int(TestSuite* ts, int val1, int val2)
{
    if (val1 > val2)
        return TestSuite_pass(ts, "%d > %d", val1, val2);
    else if (val1 == val2)
        return TestSuite_fail(ts, "%d == %d", val1, val2);
    else
        return TestSuite_fail(ts, "%d < %d", val1, val2);
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