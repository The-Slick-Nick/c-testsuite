/*
test_components.h

Core structures and macros for writing test cases
*/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "strlist.h"

/* Result code macros */
#define TEST_SUCCESS 0
#define TEST_FAILURE -1
#define TEST_ERROR -2

#ifndef INCLUDE_GUARD_TEST_SUITE
#define INCLUDE_GUARD_TEST_SUITE

/* TestSuite structure definition */
typedef struct TestSuite{
    int n_pass;         // Number of test successes
    int n_fail;         // Number of test failures
    int n_err;          // Number of test errors
    StrList* error_msg; // Linked list of error messages
} TestSuite;


// Initialization function for TestSuite
// Returns pointer to a newly defined TestSuite
TestSuite* TestSuite_init()
{
    TestSuite* ts = (TestSuite*)malloc(sizeof(TestSuite));
    ts->n_pass = 0;
    ts->n_fail = 0;
    ts->n_err = 0;
    ts->error_msg = StrList_init();
    return ts;
}

// Frees any memory allocated as part of a TestSuite
void TestSuite_deconstruct(TestSuite* ts)
{
    StrList_deconstruct(ts->error_msg);
    free(ts);
}

// Print Status of tests - prints test failure and reports on # success/fail
void TestSuite_print(TestSuite* ts)
{
    printf("\n");
    printf("______________________\n");
    for(_listitem* current=ts->error_msg->head;current!=NULL;current=current->next)
    {
        printf("%s\n", current->title);
        printf("%s\n", current->content);
        printf("______________________\n");
    }

    printf("Successes: %d\n", ts->n_pass);
    printf("Failures: %d\n", ts->n_fail);
    printf("Errors %d\n", ts->n_err);

}

// Uses a double-call to vnsprintf and parsing of a va_list to generate and return
// a pointer to a formatted variable length message.
// Used primarily for generating error messages and error titles
char* format_string(char* base_str, ...)
{
    va_list arg_list;
    va_start(arg_list, base_str);

    // Passing NULL as destination to vsnprintf will return length of target
    // resulting string
    int length = 1 + vsnprintf(NULL, 0, base_str, arg_list);
    char* to_return = (char*)malloc(length * sizeof(char));

    // Now that length is known, make second call to vsnprintf to generate desired
    // string
    vsnprintf(to_return, length, base_str, arg_list);
    
    // I'm not sure why but we need to va_end if we have used va_start
    va_end(arg_list);
    return to_return;
}

#endif