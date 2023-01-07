/*
str_assertions.h

Assertion functions revolving around strings
*/
#include <string.h>
#include "core.h"

int assert_equal_str(TestSuite* ts, char* val1, char* val2)
{
    int idx;
    int len1 = strlen(val1);
    int len2 = strlen(val2);
    int return_code;
    char chr1, chr2;
    char* msg;

    if (len1 != len2)
    {
        msg = format_string(
            "String lengths differ: %d vs %d\n      %s\n      %s",
            len1, len2, val1, val2
        );
        return_code = TestSuite_fail(ts, msg);
        free(msg);
        return return_code;
    }

    for(idx = 0; idx < len1; idx++)
    {
        chr1 = *(val1 + idx);
        chr2 = *(val2 + idx);
        if(chr1 != chr2)
        {
            char* indicator = (char*)malloc((idx + 1) * sizeof(char));
            for(int i = 0; i < idx; i++)
            {
                *(indicator + i) = ' ';
            }
            *(indicator + idx) = '^';

            msg = format_string(
                "Strings differ at index %d\n      %s\n      %s\n      %s",
                idx, val1, val2, indicator
            );
            return_code = TestSuite_fail(ts, msg);
            free(indicator);
            free(msg);
            return return_code;
        }
    }

    msg = format_string("Strings equal\n      %s\n      %s", val1, val2);
    return_code = TestSuite_pass(ts, msg);
    free(msg);
    return return_code;
}

int assert_not_equal_str(TestSuite* ts, char* val1, char* val2)
{
    char* msg;
    int return_code;
    if(strcmp(val1, val2) != 0)
    {
        msg = format_string("Strings differ\n      %s\n      %s", val1, val2);
        return_code = TestSuite_pass(ts, msg);
    }
    else
    {
        msg = format_string("Strings equal\n      %s\n      %s", val1, val2);
        return_code = TestSuite_fail(ts, msg);
    }
    free(msg);
    return return_code;
}