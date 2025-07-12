// labs_test.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    printf("Testing labs() with different integer types on Windows\n");
    printf("sizeof(int) = %zu bytes\n", sizeof(int));
    printf("sizeof(long) = %zu bytes\n", sizeof(long));
    printf("sizeof(long long) = %zu bytes\n", sizeof(long long));
    printf("sizeof(int64_t) = %zu bytes\n", sizeof(int64_t));
    printf("sizeof(size_t) = %zu bytes\n", sizeof(size_t));
    printf("\n");

    // Test with correct types first
    int int_val = -42;
    long long_val = -123456L;
    long long longlong_val = -9876543210LL;

    printf("Correct usage:\n");
    printf("abs(%d) = %d\n", int_val, abs(int_val));
    printf("labs(%ld) = %ld\n", long_val, labs(long_val));
    printf("llabs(%lld) = %lld\n", longlong_val, llabs(longlong_val));
    printf("\n");

    // Now test the problematic case - calling labs with int64_t
    printf("Problematic usage - calling labs() with int64_t:\n");
    int64_t big_val = -9876543210LL;  // This is bigger than 32-bit long on Windows

    // This should generate a warning on MSVC because int64_t is 64-bit
    // but labs expects long (32-bit on Windows)
    printf("int64_t value: %lld\n", big_val);

    // This line should cause a compiler warning about type mismatch
    long result = labs(big_val);  // Passing int64_t to function expecting long
    // MSVC warning:
    // labs.c(35): warning C4244: 'function': conversion from 'int64_t' to 'long', possible loss of data
    //
    // clang warning in editor on Windows (but not on Mac and presumably not on Linux):
    // Absolute value function 'labs' given an argument of type 'int64_t' (aka 'long long') but has parameter of
    // type 'long' which may cause truncation of value (clang -Wabsolute-value)

    printf("labs(int64_t %lld) = %ld\n", big_val, result);
    printf("Notice: result may be truncated or garbage!\n");

    return 0;
}
