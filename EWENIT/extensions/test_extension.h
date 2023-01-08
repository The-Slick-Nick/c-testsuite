#include "../core.h"

// The ASSERT macro can:
// 1. Be defined in the same file as its assertion function (as in here)
// 2. Be defined in a separate file. Note that extensions_master.h must then include
//    both to work correctly (though the assertion and function files need not #include
//    eachother. )
#define ASSERT_EQUALS_SIX(val1) assert_equals_six(ts, val1)

int assert_equals_six(TestSuite* ts, int val1)
{
    if (val1 == 6)
        return TestSuite_pass(ts, "%d == 6", val1);
    else
        return TestSuite_fail(ts, "%d != 6", val1);
}