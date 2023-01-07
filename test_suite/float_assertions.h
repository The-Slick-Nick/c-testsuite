/*
float_assertions.h

Assertion functions revolving around floating point numbers
*/
#include <stdbool.h>
#include "core.h"

// Compares two floats for exact equality
int assert_equal_float(TestSuite* ts, float val1, float val2)
{
    if (val1 == val2)
        return TestSuite_pass(ts, "%f == %f", val1, val2);
    else
        return TestSuite_fail(ts, "%f != %f", val1, val2);
}

// Compare two floats to assess their inequality
int assert_not_equal_float(TestSuite* ts, float val1, float val2)
{
    if (val1 != val2)
        return TestSuite_pass(ts, "%f != %f", val1, val2);
    else
        return TestSuite_fail(ts, "%f == %f", val1, val2);
}

// Compare two floats and assert that val1 > val2
int assert_greater_than_float(TestSuite* ts, float val1, float val2)
{
    if (val1 > val2)
        return TestSuite_pass(ts, "%f > %f", val1, val2);
    else if (val1 == val2)
        return TestSuite_fail(ts, "%f == %f", val1, val2);
    else
        return TestSuite_fail(ts, "%f < %f", val1, val2);
}
