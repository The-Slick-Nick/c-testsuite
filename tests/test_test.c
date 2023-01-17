#include "../EWENIT/EWENIT.c"


void test_integers()
{
    // 3 passes, 4 fails

    ASSERT_EQUAL_INT(1, 1);
    ASSERT_EQUAL_INT(2, 1);
    ASSERT_NOT_EQUAL_INT(3, 45);
    ASSERT_NOT_EQUAL_INT(10, 10);

    ASSERT_GREATER_THAN_INT(5, 1);
    ASSERT_GREATER_THAN_INT(2, 6);
    ASSERT_GREATER_THAN_INT(2, 2);
}

void test_strings()
{
    // 2 passes, 3 fails
    ASSERT_EQUAL_STR("HELLO", "HELLO");
    ASSERT_EQUAL_STR("THIS", "THAT");
    ASSERT_EQUAL_STR("LONG", "SHORT");

    ASSERT_NOT_EQUAL_STR("ONE", "TWO");
    ASSERT_NOT_EQUAL_STR("HELLO", "HELLO");
}

void test_floats()
{
    // 3 passes, 4 fails
    ASSERT_EQUAL_FLOAT(1.5f, 1.5f);
    ASSERT_EQUAL_FLOAT(1.5f, 2);
    ASSERT_NOT_EQUAL_FLOAT(1.5f, 3.2f);
    ASSERT_NOT_EQUAL_FLOAT(1.5f, 1.5f);
    ASSERT_GREATER_THAN_FLOAT(3.5f, 1.0f);
    ASSERT_GREATER_THAN_FLOAT(3.5f, 3.5f);
    ASSERT_GREATER_THAN_FLOAT(1.2f, 2.4f);
}

void test_doubles()
{
    // 3 passes, 4 fails
    ASSERT_EQUAL_DOUBLE(1.5f, 1.5f);
    ASSERT_EQUAL_DOUBLE(1.5f, 2);
    ASSERT_NOT_EQUAL_DOUBLE(1.5f, 3.2f);
    ASSERT_NOT_EQUAL_DOUBLE(1.5f, 1.5f);
    ASSERT_GREATER_THAN_DOUBLE(3.5f, 1.0f);
    ASSERT_GREATER_THAN_DOUBLE(3.5f, 3.5f);
    ASSERT_GREATER_THAN_DOUBLE(1.2f, 2.4f);

    ASSERT_ALMOST_EQUAL_DOUBLE(0.5f, (double)4/8);  // PASS
    ASSERT_ALMOST_EQUAL_DOUBLE(0.6f, (double)6/12); // FAIL

    ASSERT_NOT_ALMOST_EQUAL_DOUBLE(0.5f, 0.428571f); // PASS
    ASSERT_NOT_ALMOST_EQUAL_DOUBLE((double)12/20, (double)6/10); // FAIL
}

void test_extension()
{
    ASSERT_EQUALS_SIX(6);
    ASSERT_EQUALS_SIX(5);

    ASSERT_EQUALS_SEVEN(7);
    ASSERT_EQUALS_SEVEN(17);
}

void test_manual()
{
    TEST_PASS("PASS1");
    TEST_PASS_FMT("PASS%d", 2);

    TEST_FAIL("FAIL1");
    TEST_FAIL_FMT("FAIL%d", 2);

    // Only if compiler supports ##__VA_ARGS__
    if (OPTIONAL_VARIADIC_SUPPORTED)
    {
        TEST_PASS("PASS%d", 3);
        TEST_FAIL("FAIL%d", 3);
    }
}

// Using the test framework to test itself lol
void meta_test()
{
    int expected_pass = 17;
    int expected_fail = 21;
    int expected_total = 38;

    if (OPTIONAL_VARIADIC_SUPPORTED)
    {
        expected_pass++;
        expected_fail++;
        expected_total += 2;
    }

    ASSERT_EQUAL_INT(ts->total_pass, expected_pass);
    ASSERT_EQUAL_INT(ts->total_fail, expected_fail);
    ASSERT_EQUAL_INT(ts->total_tests, expected_total);
}

int main()
{
    EWENIT_START;
    ADD_CASE(test_integers);
    ADD_CASE(test_strings);
    ADD_CASE(test_floats);
    ADD_CASE(test_doubles);
    ADD_CASE(test_extension);
    ADD_CASE(test_manual);
    ADD_CASE(meta_test);

    EWENIT_END;
}