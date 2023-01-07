/*----------------------------------------------------------------------------------------
core.h

Core components for my janky testing framework.

Definitions/methods for structs:
TestSuite
_caseitem
_assertionitem

----------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#ifndef INCLUDE_GUARD_CORE
#define INCLUDE_GUARD_CORE


#define STATUS_CODE_PASS    0
#define STATUS_CODE_FAIL    -1

#define PRINT_SINGLE_LINE   printf("------------------------------\n")
#define PRINT_DOUBLE_LINE   printf("==============================\n")

/* HELPER METHOD DEFINITIONS */

// Uses a double-call to vnsprintf and parsing of a va_list to generate and return
// a pointer to a formatted variable length message. If no variable args are provided,
// simply allocates a new char array ptr, copies base_str into it, then returns it
// Used primarily for generating error messages and making copies
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

// Format string as above with an already-parsed va_list given
char* format_string_valist(char* base_str, va_list arg_list)
{
    int length = 1 + vsnprintf(NULL, 0, base_str, arg_list);
    char* to_return = (char*)malloc(length * sizeof(char));

    vsnprintf(to_return, length, base_str, arg_list);
    return to_return;
}

/* STRUCT DEFINITIONS */

// _assertionitem - individual assertion element - one per assertion per test case
typedef struct TestAssertion {
    int status_code;            // Integer representing status of an assertion
    char* msg;                  // Message to print for this assertion
    struct TestAssertion* next; // Next _assertionitem in list
} _assertionitem;

// _caseitem - individual testcase element storing information about the case
typedef struct TestCaseItem {
    bool is_committed;          // Flag if this _caseitem has been recorded in TestSuite
    int num_pass;               // Number successful assertions for this case
    int num_fail;               // Number of unsuccessful assertions for this case
    int num_tests;              // Total number of assertions for this test case
    char* name;                 // Name provided for this test case
    _assertionitem* ass_head;   // Pointer to head element of assertion list
    _assertionitem* ass_tail;   // Pointer to tail element of assertion list
    struct TestCaseItem* next;  // Pointer to next test case in list
} _caseitem;

// TestSuite - head manager struct for tests
typedef struct {
    int total_pass;             // Grand total number of successes recorded
    int total_fail;             // Grand total number of failures recorded
    int total_tests;            // Grand total number of assertions ran

    int cases_pass;             // Number of test cases passed
    int cases_fail;             // Number of test cases failed
    int num_cases;              // Total number of _caseitem elements
    _caseitem* case_head;       // Pointer to last _caseitem
    _caseitem* case_tail;       // Pointer to last _caseitem in test cases
} TestSuite;


/* INITIALIZATION & DECONSTRUCTION */

// Assertion Item
_assertionitem* _assertionitem_init(int status_code, char* msg)
{
    _assertionitem* ass = (_assertionitem*)malloc(sizeof(_assertionitem));

    ass->status_code = status_code;
    ass->next = NULL;

    // Add message
    if (msg == NULL)
        ass->msg = NULL;
    else
    {
        ass->msg = (char*)malloc((1 + strlen(msg)) * sizeof(char));
        strcpy(ass->msg, msg);
    }

    return ass;
}

void _assertionitem_deconstruct(_assertionitem* ass)
{
    if (ass == NULL)
        return;

    _assertionitem* prev = NULL;
    _assertionitem* current = ass;
    while (current != NULL)
    {
        prev = current;
        current = current->next;

        free(prev->msg);
        free(prev);
    }
}

// Case Item
_caseitem* _caseitem_init(char* case_name)
{
    _caseitem* citem = (_caseitem*)malloc(sizeof(_caseitem));
    citem->is_committed = false;
    citem->num_pass = 0;
    citem->num_fail = 0;
    citem->num_tests = 0;
    
    if (case_name == NULL)
        citem->name = NULL;
    else
    {
        citem->name = (char*)malloc((1 + strlen(case_name)) * sizeof(char));
        strcpy(citem->name, case_name);
    }

    citem->ass_head = NULL;
    citem->ass_tail = NULL;
    citem->next = NULL;
}

// Starting at head _caseitem, traverse all _caseitems and free any allocated memory
void _caseitem_deconstruct(_caseitem* citem)
{
    if (citem == NULL)
        return;

    _caseitem* prev = NULL;
    _caseitem* current = citem;
    while (current != NULL)
    {
        prev = current;
        current = current->next;

        _assertionitem_deconstruct(prev->ass_head);
        free(prev->name);
        free(prev);
    }

}

// TestSuite
TestSuite* TestSuite_init()
{
    TestSuite* ts = (TestSuite*)malloc(sizeof(TestSuite));
    ts->total_pass = 0;
    ts->total_fail = 0;
    ts->total_tests = 0;

    ts->cases_pass = 0;
    ts->cases_fail = 0;
    ts->num_cases = 0;

    ts->case_head = NULL;
    ts->case_tail = NULL;
}

void TestSuite_deconstruct(TestSuite* ts)
{
    if (ts == NULL)
        return;

    _caseitem_deconstruct(ts->case_head);
    free(ts);
}


/* PRINT/AUDIT METHODS */

void _assertionitem_print(_assertionitem* ass)
{
    if (ass == NULL)
        return;

    switch (ass->status_code)
    {
        case STATUS_CODE_PASS:
            printf("Success");
            break;
        case STATUS_CODE_FAIL:
            printf("Fail");
            break;
        default:
            break;
    }

    if (ass->msg == NULL)
    {
        printf("\n");
        return;
    }

    printf(": %s\n", ass->msg);
}

void _caseitem_print(_caseitem* ci)
{
    if (ci == NULL)
        return;

    if (ci->num_tests == 0)
        return;

    // Print name if one was given
    if (ci->name == NULL)
        printf("UNTITLED\n");
    else
        printf("%s\n", ci->name);

    // Print each assertion message for this test case
    for (_assertionitem* cur = ci->ass_head; cur != NULL; cur = cur->next)
    {
        printf("    ");
        _assertionitem_print(cur);
    }
    PRINT_SINGLE_LINE;
    printf("Passed: %d\n", ci->num_pass);
    printf("Failed: %d\n", ci->num_fail);
    printf("Total: %d\n", ci->num_tests);
}


void TestSuite_print(TestSuite* ts)
{
    for (_caseitem* cur = ts->case_head; cur != NULL; cur = cur->next)
    {
        PRINT_DOUBLE_LINE;
        _caseitem_print(cur);
    }
    PRINT_DOUBLE_LINE;
    printf("Assertions passed: %d\n", ts->total_pass);
    printf("Assertions failed: %d\n", ts->total_fail);
    printf("Total Assertions: %d\n", ts->total_tests);
    printf("\n");
    printf("Test Cases passed: %d\n", ts->cases_pass);
    printf("Test Cases failed: %d\n", ts->cases_fail);
    printf("Total Test Cases: %d\n", ts->num_cases);

}


/* ADDING ASSERTIONS/CASES */

// Shorthand to add an _assertionitem to a provided _caseitem
void _testcase_addAssertion(_caseitem* citem, int status_code, char* msg)
{
    _assertionitem* new_ass = _assertionitem_init(status_code, msg);
    if (citem->ass_head == NULL)
        citem->ass_head = new_ass;
    
    if (citem->ass_tail != NULL)
        citem->ass_tail->next = new_ass;

    citem->ass_tail = new_ass;
}

// A _caseitem is considered incomplete until it has been committed. This method commits
// it, adding success/fail/total counts to TestSuite and flagging it as considered
int TestSuite_commitCase(TestSuite* ts)
{
    if (ts->case_tail == NULL)
        return -1;

    if (ts->case_tail->is_committed)
        return -1;

    ts->total_pass += ts->case_tail->num_pass;
    ts->total_fail += ts->case_tail->num_fail;
    ts->total_tests += ts->case_tail->num_tests;

    ts->num_cases++;
    if (ts->case_tail->num_fail > 0)
        ts->cases_fail++;
    else
        ts->cases_pass++;

    ts->case_tail->is_committed = true;
    return 0;
}

// Adds a new test case. First commits the old running one at tail _caseitem, then
// appends a brand new one to the right side
int TestSuite_newCase(TestSuite* ts, char* case_name)
{
    // New case - commit the old one
    TestSuite_commitCase(ts);

    _caseitem* new_case = _caseitem_init(case_name);

    if (ts->case_head == NULL)
        ts->case_head = new_case;

    if (ts->case_tail != NULL)
        ts->case_tail->next = new_case;

    ts->case_tail = new_case;
}

// Call to indicate a test passed on the current running _caseitem
int TestSuite_pass(TestSuite* ts, char* msg, ...)
{
    if (ts->case_tail == NULL)
        return -1;

    // Handle any formatting passed by using format_string_valist
    char* pass_msg;
    va_list arg_list;
    va_start(arg_list, msg);

    pass_msg = format_string_valist(msg, arg_list);

    // Cases are added to the right side
    _testcase_addAssertion(ts->case_tail, STATUS_CODE_PASS, pass_msg);
    ts->case_tail->num_pass++;
    ts->case_tail->num_tests++;

    free(pass_msg);
    va_end(arg_list);
    return 0;
}

// Call to indicate a test failed on the current running _caseitem
int TestSuite_fail(TestSuite* ts, char* msg, ...)
{
    if (ts->case_tail == NULL)
        return -1;

    // Handle any formatting passed by using format_string_valist
    char* fail_msg;
    va_list arg_list;
    va_start(arg_list, msg);

    fail_msg = format_string_valist(msg, arg_list);

    // Cases are added to the right side
    _testcase_addAssertion(ts->case_tail, STATUS_CODE_FAIL, fail_msg);
    ts->case_tail->num_fail++;
    ts->case_tail->num_tests++;

    free(fail_msg);
    va_end(arg_list);
    return 0;
}

#endif