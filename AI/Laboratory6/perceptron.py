import csv
import random
LEARNING_RATE = 0.1
TRAIN_PERC = 0.7
EPOCHS = 50

def load_iris_dataset(path):
    dataset = []
    with open(path, newline="", encoding="utf-8-sig") as csv_file:
        reader = csv.DictReader(csv_file)
        for row in reader:
            dataset.append(
                {
                    "features": [
                        float(row["SepalLengthCm"]),
                        float(row["SepalWidthCm"]),
                        float(row["PetalLengthCm"]),
                        float(row["PetalWidthCm"]),
                    ],
                    "label": row["Species"],
                }
            )
    return dataset

def split_train_test(data, train_ratio=TRAIN_PERC, seed=42):
    random.seed(seed)
    random.shuffle(data)
    splitIndex = int(len(data) * train_ratio)
    train_data = data[:splitIndex]
    test_data = data[splitIndex:]
    return train_data, test_data

def compute_min_max(train_data):
    num_features = len(train_data[0]["features"])
    mins = [float("inf")] * num_features
    maxs = [float("-inf")] * num_features
    for row in train_data:
        x = row["features"]
        for i in range(num_features):
            if x[i] < mins[i]:
                mins[i] = x[i]
            if x[i] > maxs[i]:
                maxs[i] = x[i]
    
    return mins, maxs

def normalize_dataset(data, mins, maxs):
    normalized = []
    for row in data:
        x = row["features"]
        y = row["label"]

        new_x = []
        for i in range(len(x)):
            if maxs[i] == mins[i]:
                new_x.append(0)
            else:
                new_x.append((x[i] - mins[i]) / (maxs[i] - mins[i]))
        normalized.append((new_x, y))
    return normalized

class MultiClassPerceptron:
    def __init__(self, n_features, classes, learning_rate = LEARNING_RATE, epochs=EPOCHS):
        self.learning_rate = learning_rate
        self.epochs = epochs
        self.n_features = n_features
        self.classes = classes
        self.models =  {}
        
        for cls in classes:
            self.models[cls] = {
                "weights": [0.0] * n_features,
                "bias": 0.0
            }

    

    def compute_score(self, x, cls):
        score = 0.0
        weights = self.models[cls]["weights"]
        bias = self.models[cls]["bias"]

        for xi, wi in zip(x, weights):
            score += xi * wi
        score += bias

        return score

    def predict(self, x):
            scores = {}
            for cls in self.classes:
                scores[cls] = self.compute_score(x, cls)
            best_class = max(scores, key=scores.get)
            return best_class
            '''
            weighted_sum = 0
            for xi, wi in zip(x, self.weights):
                weighted_sum += xi*wi
            weighted_sum += self.bias 
            return self.step(weighted_sum)
            '''
    
    def train(self, training_data):
        for epoch in range(self.epochs):
            erros = 0
            for x, y in training_data:
                pred = self.predict(x)
                if pred != y:
                    erros += 1

                    for i in range(self.n_features):
                        self.models[y]["weights"][i] += self.learning_rate * x[i]
                    self.models[y]["bias"] += self.learning_rate

                    for i in range(self.n_features):
                        self.models[pred]["weights"][i] -= self.learning_rate * x[i]
                    self.models[pred]["bias"] -= self.learning_rate
            print(f"Epoch {epoch+1}: errors = {erros}")

            if erros == 0:
                break


                

'''
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
    erros = 0
    print(f"\nEpoch {epoch + 1}")
    for x_inputs, true_y in training_data:
        pred_y = perceptron(x_inputs, w_weights, bias)
        if pred_y != true_y:
            erros += 1
            for i in range(len(w_weights)):
                w_weights[i] = w_weights[i] + learning_rate * (true_y - pred_y) * x_inputs[i]
            bias = bias + learning_rate * (true_y - pred_y)

    print(f"Weights: {[round(w, 3) for w in w_weights]}")
    print(f"Bias: {bias:.3f}")
    print(f"Errors: {erros}")

    if erros == 0:
        break

class Perceptron:
    def __init__(self, classes, n_features, learning_rate=LEARNING_RATE, epochs=EPOCHS):
        self.classes = classes
        self.models = {}

        for cls in classes:
            self.models[cls] = Perceptron(
                n_features=n_features,
                learning_rate=learning_rate,
                epochs=epochs
            )

    def train(self, train_data):
        for cls in self.classes:
            print(f"\nTraining for class: {cls} vs Rest")
            binary_data = []

            for x, y in train_data:
                target = 1 if y == cls else 0
                binary_data.append((x, target))

            self.models[cls].train(binary_data)

    def predict(self, x):
        scores = {}

        for cls, model in self.models.items():
            score = 0.0
            for xi, wi in zip(x, model.weights):
                score += xi * wi
            score += model.bias
            scores[cls] = score

        best_class = max(scores, key=scores.get)
        return best_class
'''


def evaluate(model, test_data):
    correct = 0
    wrong = 0
    total = len(test_data)

    print("\n Test үр дүн ")
    for x, true_y in test_data:
        pred_y = model.predict(x)

        if pred_y == true_y:
            print(f"True: {true_y:15s} | Pred: {pred_y}")
            correct += 1
        else:
            print(f"False: {true_y:15s} | Pred: {pred_y}")
            wrong += 1

    accuracy = correct / total
    print(f"\nCorrect: {correct}")
    print(f"Wrong: {wrong}")
    return accuracy


def main():
    filename = "Iris.csv"   

    data = load_iris_dataset(filename)
    print(f"Нийт өгөгдлийн тоо: {len(data)}")

    train_data, test_data = split_train_test(data, train_ratio=TRAIN_PERC, seed=42)
    print(f"Training өгөгдөл: {len(train_data)}")
    print(f"Test өгөгдөл: {len(test_data)}")

    mins, maxs = compute_min_max(train_data)
    train_data = normalize_dataset(train_data, mins, maxs)
    test_data = normalize_dataset(test_data, mins, maxs)

    classes = ["Iris-setosa", "Iris-versicolor", "Iris-virginica"]

    model = MultiClassPerceptron(
        classes=classes,
        n_features=4,
        learning_rate=LEARNING_RATE,
        epochs=EPOCHS
    )

    model.train(train_data)

    accuracy = evaluate(model, test_data)
    print(f"\nTest Accuracy = {accuracy * 100:.2f}%")

if __name__ == "__main__":
    main()