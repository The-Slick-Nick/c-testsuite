/*========================================================================================
int_assertions.h

Assertion functions revolving around inting point numbers
========================================================================================*/
#include <stdbool.h>
#include "core.h"

// Compares two ints for exact equality
int assert_equal_int(TestSuite* ts, int val1, int val2)
{
    if (val1 == val2)
        return TestSuite_pass(ts, "%d == %d", val1, val2);
    else
        return TestSuite_fail(ts, "%d != %d", val1, val2);
}

// Compare two ints to assess their inequality
int assert_not_equal_int(TestSuite* ts, int val1, int val2)
{
    if (val1 != val2)
        return TestSuite_pass(ts, "%d != %d", val1, val2);
    else
        return TestSuite_fail(ts, "%d != %d", val1, val2);
}

// Compare two ints and assert that val1 > val2
int assert_greater_than_int(TestSuite* ts, int val1, int val2)
{
    if (val1 > val2)
        return TestSuite_pass(ts, "%d > %d", val1, val2);
    else if (val1 == val2)
        return TestSuite_fail(ts, "%d == %d", val1, val2);
    else
        return TestSuite_fail(ts, "%d < %d", val1, val2);
}
