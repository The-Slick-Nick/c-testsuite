/*========================================================================================
int_assertions.h

Assertion functions revolving around integers
Also includes boolean checks
========================================================================================*/
#ifndef INCLUDE_GUARD_INT_ASSERTIONS
#define INCLUDE_GUARD_INT_ASSERTIONS

#include "core.h"

/* ============================================================================
 *  INTEGER ASSERTIONS
 * ========================================================================= */
int assert_equal_int(TestSuite* ts, int val1, int val2, char* file_name, long line_num);
int assert_not_equal_int(TestSuite* ts, int val1, int val2, char* file_name, long line_num);
int assert_greater_than_int(TestSuite* ts, int val1, int val2, char* file_name, long line_num);


/* ============================================================================
 *  BOOLEAN ASSERTIONS
 * ========================================================================= */
int assert_true(TestSuite* ts, int val1, char* file_name, long line_num);
int assert_false(TestSuite* ts, int val1, char* file_name, long line_num);


/* ============================================================================
 *  LONG ASSERTIONS
 * ========================================================================= */
int assert_equal_long(TestSuite* ts, long val1, long val2, char* file_name, long line_num);
int assert_not_equal_long(TestSuite* ts, long val1, long val2, char* file_name, long line_num);
int assert_greater_than_long(TestSuite* ts, long val1, long val2, char* file_name, long line_num);



#endif
