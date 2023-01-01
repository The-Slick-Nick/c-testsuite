/*
test_suite.c

Methods for unit testing
RETURN CODES
0   SUCCESS
-1  TEST FAILURE

USAGE
Create a test file in form XXX_test.c
#include ".../test_suite.c"

Write test methods in the form 
    int test_some_func(TestSuite* ts)
    {
        ... some code ...
        assert_function(ts, "test_some_func", ...)
    }

Assert functions are defined in this file and are used to test equality/inequality
and various other properties of expected function results.

Then, in a main method, do:

1 int main()
2 {
3   TestSuite* ts = TestSuite_init();
4   test_some_func(ts);
5   ... other test functions ...
6
7   TestSuite.print(ts);
8   TestSuite_deconstruct(ts);
9 }

3.  Initializes a TestSuite struct
4-5 Runs tests and passes TestSuite to it, recording results
7   Prints results of tests

*/
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include "strlist.c"

#define TEST_SUCCESS 0
#define TEST_FAILURE -1
#define TEST_ERROR -2 

// Define TestSuite structure
typedef struct TestSuite{
    int pass;  // Number of test successes
    int fail;  // Number of test failures
    StrList* errors;  // Pointer to linked list of string error messages
} TestSuite;

// Initialization function for TestSuite
TestSuite* TestSuite_init()
{
    StrList* error_list = StrList_init();
    TestSuite* ts = (TestSuite*)malloc(sizeof(TestSuite));
    ts->pass = 0;
    ts->fail = 0;
    ts->errors = error_list;
    return ts;
};

// Frees any memory allocated within a TestSuite
void TestSuite_deconstruct(TestSuite* ts)
{
    // Free list of error messages
    StrList_deconstruct(ts->errors);
    free(ts);
}

// Uses a double-call to vsnprintf to generate a variable-length error message
char* error_message(char* base_str, ...)
{
    va_list arg_list;
    va_start(arg_list, base_str);

    int length = 1 + vsnprintf(NULL, 0, base_str, arg_list);
    char* to_return = malloc(length * sizeof(char));

    va_end(arg_list);
    va_start(arg_list, base_str);

    vsnprintf(to_return, length, base_str, arg_list);

    va_end(arg_list);


    return to_return;
}

// Copy a string literal into a malloc() defined char array for storage in a StrList
char* error_title(char* title_str)
{
    int alloc_len = strlen(title_str) + 1;
    char* to_return = (char*)malloc(alloc_len * sizeof(char));
    strcpy(to_return, title_str);
    return to_return;
}

// Print status of tests - prints test failure and reports on # success/fail
void TestSuite_print(TestSuite* ts)
{
    _listitem* current = ts->errors->head;

    printf("\n");
    printf("_______________________\n");

    for(current = ts->errors->head; current != NULL; current = current->next)
        {
            printf("%s\n", current->title);
            printf("%s\n", current->content);
            printf("_______________________\n");
        }

    printf("Successes: %d\n", ts->pass);
    printf("Failures: %d\n", ts->fail);

}

/* TEST FUNCTIONS */

// Compares two integers to assess their equality
int assert_equal_int(TestSuite* ts, char* test_name, int val1, int val2)
{
    if(val1 == val2)
    {
        printf("*");
        ts->pass++;
        return TEST_SUCCESS;
    }
    else if(val1 != val2)
    {
        printf("F");
        ts->fail++;
        char* err_msg = error_message(
            "TEST FAILURE AT assert_equal_int\n%d != %d\n", val1, val2
        );
        char* err_title = error_title(test_name);

        StrList_append(ts->errors, err_title, err_msg);
        return TEST_FAILURE;
    }
    else
        return TEST_ERROR;

}

// Compare two integers to assess their inequality
int assert_not_equal_int(TestSuite* ts, char* test_name, int val1, int val2)
{
    if(val1 != val2)
    {
        printf("*");
        ts->pass++;
        return TEST_SUCCESS;
    }
    else if(val1 == val2)
    {
        printf("F");
        ts->fail++;
        char* err_msg = error_message(
            "TEST FAILURE AT assert_not_equal_int\n%d == %d\n", val1, val2
        );
        char* err_title = error_title(test_name);
        StrList_append(ts->errors, err_title, err_msg);
        return TEST_FAILURE;
    }
    else
        return TEST_ERROR;
}

// Tests that a boolean value is true
int assert_true(TestSuite* ts, char* test_name, bool val)
{
    if(val)
    {
        printf("*");
        ts->pass++;
        return TEST_SUCCESS;
    }
    else if(!val)
    {
        printf("F");
        ts->fail++;

        char* err_msg = error_message("TEST FAILURE AT assert_true\n%d != true", val);
        char* err_title = error_title(test_name);

        StrList_append(ts->errors, err_title, err_msg);
        return TEST_FAILURE;
    }
    else
        return TEST_ERROR;
}

// Tests that a boolean value is false
int assert_false(TestSuite* ts, char* test_name, bool val)
{
    if(!val)
    {
        printf("*");
        ts->pass++;
        return TEST_SUCCESS;
    }
    else if(val)
    {
        printf("F");
        ts->fail++;
        char* err_msg = error_message("TEST FAILURE AT assert_false\n%d != false", val);
        char* err_title = error_title(test_name);
        StrList_append(ts->errors, err_title, err_msg);
        return TEST_FAILURE;
    }
    else
        return TEST_ERROR;
}