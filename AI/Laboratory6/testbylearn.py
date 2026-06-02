import csv

training_data = [
    ([0, 0], 0),
    ([0, 1], 0),
    ([1, 0], 0),
    ([1, 1], 1)
]
w_weights = [0.2, 0.4]
threshold = 0.5
learning_rate = 0.1
bias = 0.3

def weightConvert(w, learning_rate, true_y, pred_y, x):
    return w + learning_rate * (true_y - pred_y) * x

def step(weighted_sum):
    if weighted_sum < threshold:
        return 0
    return 1

def perceptron(x_inputs, w_weights, bias):
    weighted_sum = 0
    for x, w in zip(x_inputs, w_weights):
        weighted_sum += x*w
    weighted_sum += bias 
    print("weighted_sum: ", weighted_sum)
    return step(weighted_sum)




for epoch in range(5):
    print(f"\nEpoch {epoch + 1}")
    for x_inputs, true_y in training_data:
        pred_y = perceptron(x_inputs, w_weights, bias)
        if pred_y != true_y:
            for i in range(len(w_weights)):
                w_weights[i] = w_weights[i] + learning_rate * (true_y - pred_y) * x_inputs[i]
            bias = bias + learning_rate * (true_y - pred_y)

        print(f"Input: {x_inputs}, True: {true_y}, Pred: {pred_y}, Weights: {w_weights}, Bias: {bias:.2f}")
