# Hello FFI

This is an exploration of using the safe keyword for C FFI with the `abs` and `labs` functions, with
the former being demonstrated in [chapter 20] of *The Rust Programming Language* book (3rd edition).

While all modern platforms use 32-bits for a `c_int`, if we extend that example to `labs` we will find
that on Windows, C uses 32-bit for `long` whereas on Mac/Linux, C uses 64-bit for `long`.

In that case `std::ffi::c_long` would be more appropriate than `u64` -- see the docs for [c_long][].

[chapter 20]: https://doc.rust-lang.org/book/ch20-01-unsafe-rust.html#using-extern-functions-to-call-external-code
[c_long]: https://doc.rust-lang.org/1.88.0/std/ffi/type.c_long.html
