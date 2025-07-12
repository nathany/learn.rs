# Hello FFI

This is an exploration of using the safe keyword for C FFI with the `abs` and `labs` functions, with
the former being demonstrated in [chapter 20] of *The Rust Programming Language* book (3rd edition).

While all modern platforms use 32-bits for a `c_int`, if we extend that example to `labs` we will find
that on Windows, C uses 32-bit for `long` whereas on Mac/Linux, C uses 64-bit for `long`.

If we write the following function declarations, we will find that the test fails with no warnings or compiler errors on Windows. After all, Rust doesn't know that `labs` takes a `c_long` instead of an `i64` unless we tell it.

```rust
unsafe extern "C" {
    safe fn abs(input: i32) -> i32;
    safe fn labs(input: i64) -> i64;
}
```

In that case `std::ffi::c_long` would be more appropriate than `i64` -- see the docs for [c_long][].

```rust
use std::ffi::{c_int, c_long};

unsafe extern "C" {
    safe fn abs(input: c_int) -> c_int;
    safe fn labs(input: c_long) -> c_long;
}
```

In this case Rust can provide a nice compile-time error when we run cargo build:

```rust
13 |     println!("Absolute value of {num2} according to C: {}", labs(num2));
   |                                                             ---- ^^^^ expected `i32`, found `i64`
   |                                                             |
   |                                                             arguments to this function are incorrect
```

At least on Windows. Unfortunately there are still no compilers errors or clippy warnings on Mac.

[chapter 20]: https://doc.rust-lang.org/book/ch20-01-unsafe-rust.html#using-extern-functions-to-call-external-code
[c_long]: https://doc.rust-lang.org/1.88.0/std/ffi/type.c_long.html

I opened [an issue](https://github.com/rust-lang/book/issues/4443) with The Rust Programming Language book. Hopefully some minor tweaks to chapter 20 will make more readers aware of this subtle logic bug with cross-platform FFI.
