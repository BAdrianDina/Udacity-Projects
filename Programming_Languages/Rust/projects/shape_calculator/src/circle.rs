pub struct Circle {
    pub radius: f64,
}

impl Circle {
    pub fn area(&self) -> f64 {
        std::f64::consts::PI * self.radius * self.radius
    }

    pub fn circumference(&self) -> f64 {
        2.0 * std::f64::consts::PI * self.radius
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_circle_area() {
        let circle = Circle { radius: 2.0 };
        let expected_area = std::f64::consts::PI * 2.0 * 2.0;
        assert!((circle.area() - expected_area).abs() < 1e-6); // Allow for floating-point precision errors
    }
}
