use std::ffi::c_long;

unsafe extern "C" {
    safe fn labs(input: c_long) -> c_long;
}

fn main() {
    let num: i64 = -9876543210;
    println!("Absolute value of {num} according to C: {}", labs(num));
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
