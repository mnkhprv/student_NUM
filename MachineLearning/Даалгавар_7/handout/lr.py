import numpy as np
import argparse

def sigmoid(x: np.ndarray):
    """
    Сигмойд функц: z утгыг 0-ээс 1-ийн хооронд магадлал болгон хувиргана.
    """
    x = np.clip(x, -500, 500)
    return 1.0 / (1.0 + np.exp(-x))

def train(
    theta: np.ndarray, 
    X: np.ndarray,     
    y: np.ndarray,     
    num_epoch: int, 
    learning_rate: float
) -> None:
    """
    Stochastic Gradient Descent (SGD) ашиглан сургах функц.
    """
    n = X.shape[0]
    for epoch in range(num_epoch):
        for i in range(n):
            x_i = X[i]
            y_i = y[i]
            
            # 1. Таамаглал (Prediction)
            prediction = sigmoid(np.dot(theta, x_i))
            
            # 2. Градиент тооцох болон Theta-г шинэчлэх
            # Gradient of Binary Cross Entropy: (y_hat - y) * x
            gradient = (prediction - y_i) * x_i
            theta -= learning_rate * gradient

def predict(
    theta: np.ndarray, 
    X: np.ndarray      
) -> np.ndarray:
    """
    Сургасан theta-г ашиглан 0 эсвэл 1 шошгыг таамаглах.
    """
    probabilities = sigmoid(np.matmul(X, theta))
    return (probabilities >= 0.5).astype(int)

def compute_error(
    y_pred: np.ndarray, 
    y: np.ndarray
) -> float:
    """
    Алдааны хувийг тооцоолох (буруу таасан жишээний эзлэх хувь).
    """
    return np.mean(y_pred != y)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("train_input", type=str, help='path to formatted training data')
    parser.add_argument("validation_input", type=str, help='path to formatted validation data')
    parser.add_argument("test_input", type=str, help='path to formatted test data')
    parser.add_argument("train_out", type=str, help='file to write train predictions to')
    parser.add_argument("test_out", type=str, help='file to write test predictions to')
    parser.add_argument("metrics_out", type=str, help='file to write metrics to')
    parser.add_argument("num_epoch", type=int, help='number of epochs of SGD')
    parser.add_argument("learning_rate", type=float, help='learning rate for SGD')
    args = parser.parse_args()

    train_data = np.loadtxt(args.train_input, delimiter='\t')
    val_data = np.loadtxt(args.validation_input, delimiter='\t')
    test_data = np.loadtxt(args.test_input, delimiter='\t')

    y_train, X_train = train_data[:, 0], train_data[:, 1:]
    y_val, X_val = val_data[:, 0], val_data[:, 1:]
    y_test, X_test = test_data[:, 0], test_data[:, 1:]

    X_train = np.insert(X_train, 0, 1.0, axis=1)
    X_val = np.insert(X_val, 0, 1.0, axis=1)
    X_test = np.insert(X_test, 0, 1.0, axis=1)

    theta = np.zeros(X_train.shape[1])

    train(theta, X_train, y_train, args.num_epoch, args.learning_rate)

    y_train_pred = predict(theta, X_train)
    y_test_pred = predict(theta, X_test)

    train_error = compute_error(y_train_pred, y_train)
    test_error = compute_error(y_test_pred, y_test)

    np.savetxt(args.train_out, y_train_pred, fmt='%d')
    np.savetxt(args.test_out, y_test_pred, fmt='%d')

    with open(args.metrics_out, 'w') as f:
        f.write(f"error(train): {train_error:.6f}\n")
        f.write(f"error(test): {test_error:.6f}\n")

    print(f"Training complete. Train Error: {train_error:.6f}, Test Error: {test_error:.6f}")