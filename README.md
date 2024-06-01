# EWENIT v2.0.1
A basic unit testing framework for C.
## Usage

```.c
#include "EWENIT.h" /* or wherever the header is located */
```

## An Example
```c
/* example_test.c */

#include "EWENIT.h" 

// =======================================
 /* NOTE: In an actual application, these
  * will likely be imported from elsewhere
  */
int intFunc() {
    return 4;
}

char* strFunc() {
    return "Good result";
}

// =======================================
// Test cases
void test1() {
    int intResult = intFunc();
    ASSERT_EQUAL_INT(intResult, 4); // succeeds
    return 0;
}

void test2() {
    char* strResult = strFunc();
    ASSERT_NOT_EQUAL_STR(strResult, "Bad result"); // succeeds
    return 0;
}

void test3() {
    int intResult = intFunc();
    ASSERT_GREATER_THAN_INT(intResult, 10); // fails
}

void test4() {
    char* strResult = strFunc();
    ASSERT_EQUAL_STR(strResult, "Another bad one"); // fails
}

// =======================================
// Run suite

int main() {
    EWENIT_START;
    ADD_CASE(test1);
    ADD_CASE_CUSTOM(test2, "String Test");
    ADD_CASE(test3);
    ADD_CASE(test4);
    EWENIT_END;
}

```

## Macros

### Initialization
##### `EWENIT_START`
Begins and prepares the test suite. Must be called before any 
assertions can be made.
##### `TEST_START`
An alias for EWENIT_START
***
### Ending
##### `EWENIT_END`
##### `TEST_END`
An alias for EWENIT_END.
##### `EWENIT_END_COMPACT`
##### `TEST_END_COMPACT`
An alias for EWENIT_END_COMPACT
##### `EWENIT_END_VERBOSE`
##### `TEST_END_VERBOSE`
An alias for EWENIT_END_VERBOSE
***
### Test case management
##### `ADD_CASE(func)`
Adds `func` to the test suite. The name used when reporting out
on test status will be the name of `func` itself. `func` should have a void return value and take no arguments, e.g.
```c
void func() {
    /* test code here 
}
```
```c
ADD_CASE(func)
```
##### `ADD_CASE_CUSTOM(func, name)`
Adds `func` to the test suite, giving it a custom `name` to use when reporting on status on test suite execution.
```c
ADD_CASE(func, "Nicer name for func");
```
***
### Assertions
* For assertions with arguments `val1` and `val2`, checks that the relationship described holds true for that respective assertion's type (int, str, float, double, etc.)
* For boolean assertions `ASSERT_TRUE(val)` and `ASSERT_FALSE(val)`, simply checks that `val` is appropriately `true` or `false`.
* For assertions that imply a significance to argument order (greater than, less than, etc.),  `val1` is taken as the "first" value for the comparison, and `val2` the "second". e.g. ASSERT_GREATER_THAN_INT(`val1`, `val2`) checks that `val1` > `val2`.


#### Integers
##### `ASSERT_EQUAL_INT(val1, val2)`
##### `ASSERT_NOT_EQUAL_INT(val1, val2)`
##### `ASSERT_GREATER_THAN_INT(val1, val2)`
#### Booleans
##### `ASSERT_TRUE(val)`
##### `ASSERT_FALSE(val)`
#### Strings
##### `ASSERT_EQUAL_STR(val1, val2)`
##### `ASSERT_NOT_EQUAL_STR(val1, val2)`
#### Floats
##### `ASSERT_EQUAL_FLOAT(val1, val2)`
##### `ASSERT_NOT_EQUAL_FLOAT(val1, val2)`
##### `ASSERT_GREATER_THAN_FLOAT(val1, val2)`
##### `ASSSERT_ALMOST_EQUAL_FLOAT(val1, val2)`
##### `ASSERT_NOT_ALMOST_EQUAL_FLOAT(val1, val2)`
#### Doubles
##### `ASSERT_EQUAL_DOUBLE(val1, val2)`
##### `ASSERT_NOT_EQUAL_DOUBLE(val1, val2)`
##### `ASSERT_GREATER_THAN_DOUBLE(val1, val2)`
##### `ASSERT_ALMOST_EQUAL_DOUBLE(val1, val2)`
##### `ASSERT_NOT_ALMOST_EQUAL_DOUBLE(val1, val2)`
#### Manual assertions
##### `TEST_PASS(msg)`
Manually log a success with the provided message.
##### `TEST_PASS_FMT(msg, ...)`
Manually log a success with the provided message with support for format arguments (%d, %f, %s, etc.)


