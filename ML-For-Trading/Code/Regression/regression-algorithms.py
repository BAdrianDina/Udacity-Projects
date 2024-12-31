import numpy as np

# Linear Regression class
class LinearRegression:
    def __init__(self):
        self.weights = None  # Coefficients (slope)
        self.bias = None     # Intercept

    def fit(self, X, y, learning_rate=0.01, epochs=1000):
        """
        Fit the model to the data using gradient descent.
        """
        # Ensure X and y are NumPy arrays (to prevent shape mismatches)
        X = np.array(X)  # New: Ensure X is a NumPy array
        y = np.array(y)  # New: Ensure y is a NumPy array

        n_samples, n_features = X.shape  # New: Ensure correct shape for X and initialize weights
        self.weights = np.zeros(n_features)  # Initialize weights (1 per feature)
        self.bias = 0  # Initialize bias

        # Gradient descent
        for _ in range(epochs):
            y_pred = np.dot(X, self.weights) + self.bias  # New: Prediction using matrix multiplication
            dw = (1 / n_samples) * np.dot(X.T, (y_pred - y))  # New: Corrected shape for gradient
            db = (1 / n_samples) * np.sum(y_pred - y)         # Gradient for bias

            # Update weights and bias
            self.weights -= learning_rate * dw  # Gradient step for weights
            self.bias -= learning_rate * db    # Gradient step for bias

    def predict(self, X):
        """
        Predict output using the linear regression model.
        """
        X = np.array(X)  # New: Ensure X is a NumPy array
        return np.dot(X, self.weights) + self.bias  # Matrix multiplication for predictions


# Generate synthetic data
np.random.seed(42)
X = 2 * np.random.rand(100, 1)  # Feature matrix
y = 4 + 3 * X.flatten() + np.random.randn(100)  # New: Flatten y for correct 1D shape

# Split into training and testing sets
split_index = int(0.8 * len(X))
X_train, X_test = X[:split_index], X[split_index:]
y_train, y_test = y[:split_index], y[split_index:]

# Train the model
model = LinearRegression()
model.fit(X_train, y_train, learning_rate=0.01, epochs=1000)

# Make predictions
y_pred = model.predict(X_test)

# Print results
print(f"Weights: {model.weights}")
print(f"Bias: {model.bias}")












# K-nearest neighbours ##########################################


import numpy as np
from collections import Counter
import matplotlib.pyplot as plt

# K-Nearest Neighbors Classifier
class KNearestNeighbors:
    def __init__(self, k=3):
        self.k = k  # Number of neighbors to consider

    def fit(self, X_train, y_train):
        """
        Store the training data.
        """
        self.X_train = X_train
        self.y_train = y_train

    def predict(self, X_test):
        """
        Predict the class for each sample in X_test.
        """
        predictions = [self._predict(x) for x in X_test]
        return np.array(predictions)

    def _predict(self, x):
        """
        Predict the class for a single sample.
        """
        # Compute distances between x and all examples in the training set
        distances = np.linalg.norm(self.X_train - x, axis=1)
        
        # Get the indices of the k-nearest neighbors
        k_indices = np.argsort(distances)[:self.k]
        
        # Get the labels of the k-nearest neighbors
        k_neighbor_labels = [self.y_train[i] for i in k_indices]
        
        # Return the most common class label
        most_common = Counter(k_neighbor_labels).most_common(1)
        return most_common[0][0]

# Generate synthetic data
np.random.seed(42)
X_train = np.random.rand(100, 2)  # 100 samples, 2 features
y_train = np.random.choice([0, 1], size=100)  # Binary classification (0 or 1)

# Generate test points
X_test = np.random.rand(10, 2)

# Train the KNN model
knn = KNearestNeighbors(k=5)
knn.fit(X_train, y_train)

# Predict the class of test points
predictions = knn.predict(X_test)

# Visualization
for label in np.unique(y_train):
    plt.scatter(X_train[y_train == label, 0], X_train[y_train == label, 1], label=f"Class {label}")
plt.scatter(X_test[:, 0], X_test[:, 1], color="red", marker="x", label="Test Points")
plt.xlabel("Feature 1")
plt.ylabel("Feature 2")
plt.title("K-Nearest Neighbors")
plt.legend()
plt.show()

# Print predictions
print(f"Predictions for test points: {predictions}")