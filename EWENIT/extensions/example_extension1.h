/*----------------------------------------------------------------------------------------
Example extension 1

Defining an assert function and an assert macro invoking that function
----------------------------------------------------------------------------------------*/

// This line must be included in order to define the function
#include "../core.h"

// Define the assertion macro to invoke the function
#define ASSERT_EQUALS_SIX(val1) assert_equals_six(ts, val1)


// Define the function being invoked
int assert_equals_six(TestSuite* ts, int val1)
{
    if (val1 == 6)
        return TestSuite_pass(ts, "%d == 6", val1);
    else
        return TestSuite_fail(ts, "%d != 6", val1);
}

