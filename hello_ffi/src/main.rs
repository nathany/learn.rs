use std::ffi::{c_int, c_long};

unsafe extern "C" {
    safe fn abs(input: c_int) -> c_int;
    safe fn labs(input: c_long) -> c_long;
}

fn main() {
    let num1: i32 = -42;
    println!("Absolute value of -3 according to C: {}", abs(num1));

    let num2: i64 = -9876543210;
    println!("Absolute value of {num2} according to C: {}", labs(num2));
    // On Windows this is error[E0308]: mismatched types, but on macOS it's not considered an error.
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_labs() {
        let result = labs(-9876543210);
        assert_eq!(result, 9876543210);
    }
}
