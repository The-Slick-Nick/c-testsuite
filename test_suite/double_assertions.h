/*
double_assertions.h

Assertion functions revolving around doubleing point numbers
*/
#include <stdbool.h>
#include "core.h"

// Compares two doubles for exact equality
int assert_equal_double(TestSuite* ts, double val1, double val2)
{
    if (val1 == val2)
        return TestSuite_pass(ts, "%f == %f", val1, val2);
    else
        return TestSuite_fail(ts, "%f != %f", val1, val2);
}

// Compare two doubles to assess their inequality
int assert_not_equal_double(TestSuite* ts, double val1, double val2)
{
    if (val1 != val2)
        return TestSuite_pass(ts, "%f != %f", val1, val2);
    else
        return TestSuite_fail(ts, "%f != %f", val1, val2);
}

// Compare two doubles and assert that val1 > val2
int assert_greater_than_double(TestSuite* ts, double val1, double val2)
{
    if (val1 > val2)
        return TestSuite_pass(ts, "%f > %f", val1, val2);
    else if (val1 == val2)
        return TestSuite_fail(ts, "%f == %f", val1, val2);
    else
        return TestSuite_fail(ts, "%f < %f", val1, val2);
}
