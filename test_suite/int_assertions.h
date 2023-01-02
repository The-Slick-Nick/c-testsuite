/*
int_assertions.h

Assertion functions revolving around integers
*/
#include <stdbool.h>
#include "test_components.h"

// Compares two integers to assess their equality
int assert_equal_int(TestSuite* ts, char* test_name, int val1, int val2)
{
    if(val1 == val2)
    {
        printf("*");
        ts->n_pass++;
        return TEST_SUCCESS;
    }
    else if(val1 != val2)
    {
        printf("F");
        ts->n_fail++;
        char* err_msg = format_string(
            "assert_equal_int failure:\n%d != %d\n", val1, val2
        );
        char* err_title = format_string(test_name);

        StrList_append(ts->error_msg, err_title, err_msg);
        return TEST_FAILURE;
    }
    else
    {
        printf("E");
        ts->n_err++;
        return TEST_ERROR;
    }

}

// Compare two integers to assess their inequality
int assert_not_equal_int(TestSuite* ts, char* test_name, int val1, int val2)
{
    if(val1 != val2)
    {
        printf("*");
        ts->n_pass++;
        return TEST_SUCCESS;
    }
    else if(val1 == val2)
    {
        printf("F");
        ts->n_fail++;
        char* err_msg = format_string(
            "assert_not_equal_int failure:\n%d == %d\n", val1, val2
        );

        char* err_title = format_string(test_name);
        StrList_append(ts->error_msg, err_title, err_msg);
        return TEST_FAILURE;
    }
    else
    {
        printf("E");
        return TEST_ERROR;
    }
}

// Compare two integers and assert that val1 > val2
int assert_greater_than_int(TestSuite* ts, char* test_name, int val1, int val2)
{
    if(val1 > val2)
    {
        printf("*");
        ts->n_pass++;
        return TEST_SUCCESS;
    }
    else
    {
        printf("F");
        ts->n_fail++;
        char* err_title = format_string(test_name);
        char* err_msg;
        // Deal with two different scenarios for failure
        if(val1 == val2)
        {
            err_msg = format_string(
                "Failure at assert_greater_than_int:\n%d == %d", val1, val2
            );
        }
        else
        {
            err_msg = format_string(
                "Failure at assert_greater_than_int:\n%d < %d", val1, val2
            );
        }
        StrList_append(ts->error_msg, err_title, err_msg);
        return TEST_FAILURE;
    }
}


// Tests that a boolean value is true
int assert_true(TestSuite* ts, char* test_name, bool val)
{
    if(val)
    {
        printf("*");
        ts->n_pass++;
        return TEST_SUCCESS;
    }
    else if(!val)
    {
        printf("F");
        ts->n_fail++;

        char* err_msg = format_string(
            "assert_true failure:\n%d != true", val
        );
        char* err_title = format_string(test_name);

        StrList_append(ts->error_msg, err_title, err_msg);
        return TEST_FAILURE;
    }
    else
    {
        printf("E");
        ts->n_err++;
        return TEST_ERROR;
    }
}

// Tests that a boolean value is false
int assert_false(TestSuite* ts, char* test_name, bool val)
{
    if(!val)
    {
        printf("*");
        ts->n_pass++;
        return TEST_SUCCESS;
    }
    else if(val)
    {
        printf("F");
        ts->n_fail++;

        char* err_msg = format_string(
            "assert_false failure:\n%d != false", val
        );
        char* err_title = format_string(test_name);

        StrList_append(ts->error_msg, err_title, err_msg);
        return TEST_FAILURE;
    }
    else
    {
        printf("E");
        ts->n_err++;
        return TEST_ERROR;
    }
}