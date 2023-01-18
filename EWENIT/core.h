/*========================================================================================
core.h

Core components for my janky testing framework EWENIT

Definitions/methods for structs:
    TestSuite
    _caseitem
    _assertionitem

Any methods/structs preceded with an underscore
(_caseitem, _assertionitem, and associated methods) should be considered private
and should probably never be directly called outside of this file.

========================================================================================*/


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


/*----------------------------------------------------------------------------------------
HELPER METHOD DEFINITIONS
----------------------------------------------------------------------------------------*/

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
// Returns a newly-allocated character array pointer
char* format_string_valist(char* base_str, va_list arg_list)
{
    int length = 1 + vsnprintf(NULL, 0, base_str, arg_list);
    char* to_return = (char*)malloc(length * sizeof(char));

    vsnprintf(to_return, length, base_str, arg_list);
    return to_return;
}


/*----------------------------------------------------------------------------------------
STRUCT DEFINITIONS
----------------------------------------------------------------------------------------*/


// _assertionitem - individual assertion element - one per assertion per test case
typedef struct TestAssertion {
    int status_code;            // Integer representing status of an assertion
    unsigned int file_name_offset;            // File name assertion was called from
    int line_num;               // Row number assertion was called from
    unsigned int msg_offset;                  // Message to print for this assertion
} _assertionitem;

typedef struct TestCaseItem {
    bool is_committed;
    int num_pass;
    int num_fail;
    int num_tests;
    unsigned int name_offset;   // Offset to strlib pointer containing name

    size_t length;
    size_t _size;
    _assertionitem* assertions; // Now this is a dynamically allocated array
} _caseitem;


// TestSuite - head manager struct for tests
typedef struct {
    int total_pass;             // Grand total number of successes recorded
    int total_fail;             // Grand total number of failures recorded
    int total_tests;            // Grand total number of assertions ran

    int cases_pass;             // Number of test cases passed
    int cases_fail;             // Number of test cases failed
    int num_cases;              // Total number of _caseitem elements

    size_t strlib_length;   
    size_t strlib_size;
    char* strlib;      

    size_t length;              // length of cases
    size_t _size;                // Internal size of array allocated for cases
    _caseitem* cases;           // Array of _caseitem elements

} TestSuite;


/*----------------------------------------------------------------------------------------
INITIALIZATION & DECONSTRUCTION 
----------------------------------------------------------------------------------------*/

// Starting at head _caseitem, traverse all _caseitems and free any allocated memory
// Private method


// TestSuite
// Public method
TestSuite* TestSuite_init()
{
    TestSuite* self = (TestSuite*)malloc(sizeof(TestSuite));
    self->total_pass = 0;
    self->total_fail = 0;
    self->total_tests = 0;

    self->cases_pass = 0;
    self->cases_fail = 0;
    self->num_cases = 0;

    self->strlib_length = 0;
    self->strlib_size = 4;
    self->strlib = (char*)malloc(4 * sizeof(char));

    self->length = 0;
    self->_size = 4;
    self->cases = (_caseitem*)malloc(4 * sizeof(_caseitem));

    return self;
}

void _caseitem_init(_caseitem* self, unsigned int name_offset)
{
    self->is_committed = false;
    self->num_pass = 0;
    self->num_fail = 0;
    self->num_tests = 0;
    self->name_offset = name_offset;

    self->length = 0;
    self->_size = 4;
    self->assertions = (_assertionitem*)malloc(4 * sizeof(_assertionitem));
}

void _assertionitem_init(
    _assertionitem* self, int status_code, unsigned int msg_offset,
    unsigned int file_name_offset, int line_num
)
{
    self->status_code = status_code;
    self->msg_offset = msg_offset;
    self->file_name_offset = file_name_offset;
    self->line_num = line_num;

}

void _caseitem_deconstruct(_caseitem* self)
{
    if (self == NULL)
        return;

    // Only thing malloc'd for this
    free(self->assertions);
    free(self);
}

// Public method
void TestSuite_deconstruct(TestSuite* self)
{
    if (self == NULL)
        return;

    for (int i = 0; i < self->length; i++)
    {
        _caseitem_deconstruct(self->cases + i);
    }

    free(self->strlib);
    free(self->cases);
    free(self);
}


/*----------------------------------------------------------------------------------------
PRINT METHODS
----------------------------------------------------------------------------------------*/

// Private method
// Prints a summary of success/failure for all assertions in a given test case
void _caseitem_print(_caseitem* self)
{

    _assertionitem ass;

    if (self == NULL)
        return;

    if (self->num_tests == 0)
        return;

    if (!self->is_committed)
        return;

    // Print name if one was given
    printf("%s\n", self->name);

    // NOTE: first need to sort self->assertions by (1) func name (2) line num
    //  (for better organization/reference)

    // Print all assertions for this test case
    for (int i = 0; i < self->num_tests; i++)
    {
        ass = *(self->assertions + i);
        printf("[%ld] ", ass.line_num);
        switch (ass.status_code)
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
        if (ass.msg == NULL)
        {
            printf("\n");
            return;
        }
        printf(": %s\n", ass.msg);
    }

    PRINT_SINGLE_LINE;
    printf("[%dP] ", self->num_pass);
    printf("[%dF] ", self->num_fail);
    printf("Total: %d\n", self->num_tests);
}

// Private method
// Compact printing of a case item. Prints a one-line summary of this test case
void _caseitem_printCompact(_caseitem* self)
{
    _assertionitem ass;
    if (ci == NULL)
        return;

    if (ci->num_tests == 0)
        return;

    if (!ci->is_committed)
        return;

    if (ci->name == NULL)
        printf("UNTITLED: ");
    else
        printf("%s: ", ci->name);

    // Print overall status for _caseitem
    if (ci->num_fail > 0)
        printf("Failed ");
    else
        printf("Passed ");

    printf("[");
    for (int i = 0; i < self->num_tests; i++)
    {
        ass =  *(self->assertions + i);
        switch (ass.status_code)
        {
            case STATUS_CODE_PASS:
                printf("P");
                break;
            case STATUS_CODE_FAIL:
                printf("F");
                break;
            default:
                break;
        }
    }
    printf("]");
}

// Public method
void TestSuite_print(TestSuite* ts)
{
    for (_caseitem* cur = ts->case_head; cur != NULL; cur = cur->next)
    {
        PRINT_DOUBLE_LINE;
        _caseitem_print(cur);
        printf("\n");
    }
    PRINT_DOUBLE_LINE;
    printf("Assertions\n");
    printf("[%dP] [%dF] Total: %d", ts->total_pass, ts->total_fail, ts->total_tests);
    printf("\n\nTest Cases\n");
    printf("[%dP] [%dF] Total: %d", ts->cases_pass, ts->cases_fail, ts->num_cases);
    printf("\n");

}

// Public method
void TestSuite_printCompact(TestSuite* ts)
{
    PRINT_DOUBLE_LINE;
    for (_caseitem* cur = ts->case_head; cur != NULL; cur = cur->next)
    {
        _caseitem_printCompact(cur);
        printf("\n");
    }
    PRINT_DOUBLE_LINE;
    printf("Assertions ");
    printf("[%dP] [%dF] Total: %d\n", ts->total_pass, ts->total_fail, ts->total_tests);
    printf("Test Cases ");
    printf("[%dP] [%dF] Total: %d\n", ts->cases_pass, ts->cases_fail, ts->num_cases);
}

/*----------------------------------------------------------------------------------------
ASSERTION/TEST CASE MANAGEMENT
----------------------------------------------------------------------------------------*/

// Shorthand to add an _assertionitem to a provided _caseitem
// Private method
void _caseitem_resizeAssertions(_caseitem* self)
{
    while (self->length >= self->_size)
    {
        self->_size *= 2;
    }
    self->assertions = (_assertionitem*)realloc(
        self->assertions, self->_size * sizeof(_assertionitem)
    );
}

void _caseitem_addAssertion(
    _caseitem* self, int status_code, unsigned int msg_offset,
    unsigned int file_name_offset, int line_num
)
{
    if (self->length >= self->_size)
        _caseitem_resizeAssertions(self);

    _assertionitem_init(
        self->assertions + self->length, status_code, msg_offset, file_name_offset,
        line_num
    );
    self->length++;
}

void TestSuite_resizeCases(TestSuite* self)
{
    while (self->length >= self->_size)
    {
        self->_size *= 2;
    }
    self->cases = (_caseitem*)realloc(self->cases, self->_size * sizeof(_caseitem));
}

// A _caseitem is considered incomplete until it has been committed. This method commits
// it, adding success/fail/total counts to TestSuite and flagging it as considered
// Public method
int TestSuite_commitCase(TestSuite* self)
{
    if (self->length == 0)
        return -1;

    _caseitem* current = (self->cases + self->length - 1);

    if (current->is_committed)
        return -1;

    self->total_pass += current->num_pass;
    self->total_fail += current->num_fail;
    self->total_tests += current->num_tests;

    self->num_cases++;

    // Determine if the case as a whole succeeded or failed
    if (current->num_fail > 0)
        self->cases_fail++;
    else
        self->cases_pass++;

    current->is_committed = true;
    return 0;
}

// Adds a new test case. First commits the old running one at tail _caseitem, then
// appends a brand new one to the right side
// Public method
int TestSuite_newCase(TestSuite* self, char* case_name)
{
    // New case - commit the old one
    TestSuite_commitCase(self);

    unsigned int case_name_offset = TestSuite_addString(self, case_name);

    if (self->length >= self->_size)
        TestSuite_resizeCases(self);

    _caseitem_init(self->cases + self->length, case_name_offset);
    self->length++;

    return 0;
}

// Call to indicate an assertion passed on the current running _caseitem
// Public method
int TestSuite_pass(TestSuite* self, char* file_name, long line_num, char* msg, ...)
{
    if (self->length == 0)
        return -1;

    va_list arg_list;
    unsigned int msg_offset;
    unsigned int file_name_offset;
    _caseitem* current_case;

    va_start(arg_list, msg);

    msg_offset = TestSuite_vaddString(self, msg, arg_list);
    file_name_offset = TestSuite_vaddString(self, file_name, arg_list);

    current_case = (self->cases + self->length - 1);

    _caseitem_addAssertion(
        current_case, STATUS_CODE_PASS, msg_offset, file_name_offset, line_num 
    );

    current_case->num_pass++;
    current_case->num_tests++;

    va_end(arg_list);
    return 0;
}

// Call to indicate an assertion failed on the current running _caseitem
// Public method
int TestSuite_fail(TestSuite* self, char* file_name, long line_num, char* msg, ...)
{
    if (self->length == 0)
        return -1;

    va_list arg_list;
    unsigned int msg_offset;
    unsigned int file_name_offset;
    _caseitem* current_case;

    va_start(arg_list, msg);

    msg_offset = TestSuite_vaddString(self, msg, arg_list);
    file_name_offset = TestSuite_vaddString(self, file_name, arg_list);

    current_case = (self->cases + self->length - 1);

    _caseitem_addAssertion(
        current_case, STATUS_CODE_FAIL, msg_offset, file_name_offset, line_num 
    );

    current_case->num_fail++;
    current_case->num_tests++;

    va_end(arg_list);
    return 0;
}


void TestSuite_resizeStrlib(TestSuite* self, size_t target_size)
{
    while (target_size > self->strlib_size)
    {
        self->strlib_size *= 2;
    }
    self->strlib = (char*)realloc(self->strlib, self->strlib_size * sizeof(char));
}


// Add a string to TestSuite's string library
// Returns offset to strlib pointer that string is found at
unsigned int TestSuite_vaddString(TestSuite* self, char* new_str, va_list arg_list)
{
    size_t num_new_chars;
    unsigned int start_length = self->length;

    // First identify how many extra characters will need added
    num_new_chars = vsnprintf(NULL, 0, new_str, arg_list);

    // Resize our library if needed
    TestSuite_resizeStrlib(self, num_new_chars + self->length);
    vnsnprintf(self->strlib + self->length, num_new_chars, new_str, arg_list);
    self->length += num_new_chars;
    return start_length;
}

unsigned int TestSuite_addString(TestSuite* self, char* new_str, ...)
{
    va_list arg_list;
    int return_offset;

    va_start(arg_list, new_str);
    return_offset = TestSuite_vaddString(self, new_str, arg_list);
    va_end(arg_list);
    return return_offset;
}

#endif