pub struct Square {
    pub side: f64,
}

impl Square {
    pub fn area(&self) -> f64 {
        self.side * self.side
    }

    pub fn perimeter(&self) -> f64 {
        4.0 * self.side
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_square_area() {
        let square = Square { side: 4.0 };
        assert_eq!(square.area(), 16.0);
    }
}
