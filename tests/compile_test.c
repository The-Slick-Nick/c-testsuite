#include "../EWENIT/EWENIT.h"


int test1() {
    int a = 4;
    ASSERT_EQUAL_INT(4, a);
    return 0;
}

int test2() {
    int b = 5;
    ASSERT_EQUAL_INT(2, b);
    return 0;
}


int main() {
    EWENIT_START;
    ADD_CASE(test1);
    ADD_CASE(test2);
    EWENIT_END_VERBOSE;
    return 0;
}
