# labs.c

This is a little C test to demonstrate the difference between `long` on Windows and Mac/Linux,
prior to doing a similar experiment over an FFI boundary.

## Windows

In "Developer Powershell for VS", run:

```Powershell
cl /W4 labs.c /Fe:labs.exe
```

This produces the warning:

```Powershell
labs.c(35): warning C4244: 'function': conversion from 'int64_t' to 'long', possible loss of data
```

But only because we [asked for all warnings](https://learn.microsoft.com/en-us/cpp/build/reference/compiler-option-warning-level?view=msvc-170) with /W4. The default /W1 only displays severe warnings.

As expected, the output is truncated for the problematic usage:

```Powershell
./labs.exe

Testing labs() with different integer types on Windows
sizeof(int) = 4 bytes
sizeof(long) = 4 bytes
sizeof(long long) = 8 bytes
sizeof(int64_t) = 8 bytes
sizeof(size_t) = 8 bytes
Correct usage:
abs(-42) = 42
labs(-123456) = 123456
llabs(-9876543210) = 9876543210
Problematic usage - calling labs() with int64_t:
int64_t value: -9876543210
labs(int64_t -9876543210) = 1286608618
Notice: result may be truncated or garbage!
```

## macOS

In Terminal run:

```bash
clang -Wall -Wextra -Wconversion labs.c -o labs
./labs
```

No truncation on Mac because long is 64-bit.

No warnings in my editor or from clang on Mac (Linux and gcc are untested).
Suggesting a portability nightmare for the inexperienced.
