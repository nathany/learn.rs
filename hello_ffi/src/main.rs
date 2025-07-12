unsafe extern "C" {
    safe fn abs(input: i32) -> i32;

    safe fn labs(input: i64) -> i64;
}

fn main() {
    println!("Absolute value of -3 according to C: {}", abs(-3));

    let num: i64 = -9876543210;
    println!("Absolute value of {num} according to C: {}", labs(num));
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
