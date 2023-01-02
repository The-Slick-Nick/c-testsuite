/*
str_assertions.h

Assertion functions revolving around strings
*/
#include <string.h>
#include "test_components.h"

int assert_equal_str(TestSuite* ts, char* test_name, char* val1, char* val2)
{
    int idx;
    int len1 = strlen(val1);
    int len2 = strlen(val2);
    char chr1, chr2;
    char* err_msg;
    char* err_title = format_string(test_name);

    if(len1 != len2)
    {
        printf("F");
        ts->n_fail++;
        err_msg = format_string(
            "String lengths differ: %d vs %d\n%s\n%s", len1, len2, val1, val2
        );

        StrList_append(ts->error_msg, err_title, err_msg);
        return TEST_FAILURE;

    }
    else
    {
        for(idx = 0; idx < len1; idx++)
        {
            chr1 = *(val1 + idx);
            chr2 = *(val2 + idx);
            if(chr1 != chr2)
            {
                printf("F");
                ts->n_fail++;

                // Create an indicator to append to error message to indicate index diff
                char* indicator = (char*)malloc((idx + 1) * sizeof(char));
                for(int i = 0; i < idx; i++)
                {
                    *(indicator + i) = ' ';
                }
                *(indicator + idx) = '^';

                err_msg = format_string(
                    "Strings differ at index %d\n%s\n%s\n%s", idx, val1, val2, indicator
                );
                free(indicator);
                StrList_append(ts->error_msg, err_title, err_msg);
                return TEST_FAILURE;

            }
        }

        printf("*");
        ts->n_pass++;
        return TEST_SUCCESS;
    }
}
