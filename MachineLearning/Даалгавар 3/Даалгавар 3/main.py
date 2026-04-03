import sys
from collections import Counter

def load_data(filepath):
    with open(filepath, 'r') as f:
        lines = f.read().splitlines()
    headers = lines[0].split('\t')
    data = [line.split('\t') for line in lines[1:] if line.strip()] 
    return headers, data

def get_labels(data):
    return [row[-1] for row in data]

def majority_vote(labels):
    counts = Counter(labels)
    majority_label = max(counts.keys(), key= lambda label: (counts[label], label))
    return majority_label

def predict(majority_label, num):
    return [majority_label] * num

def calculate_error(predictions, true_labels):
    incorrect = sum(p != t for p, t in zip(predictions, true_labels))

    return incorrect / len(true_labels)

def write_labels(filepath, predictions):
    with open(filepath, 'w') as f:
        f.write('\n'.join(predictions) + '\n')

def write_metrics(filepath, train_error, test_error):
    with open(filepath, 'w') as f:
        f.write(f'error(train): {train_error:.6f}\n')
        f.write(f'error(test): {test_error:.6f}\n')

        
    
    
    
    

def main():
    if len(sys.argv) != 6:
        print("Usage: python main.py <train input> <test input> "
              "<train out> <test out> <metrics out>")
        sys.exit(1)

    train_input = sys.argv[1]
    test_input  = sys.argv[2]
    train_out   = sys.argv[3]
    test_out    = sys.argv[4]
    metrics_out = sys.argv[5]

    train_headers, train_data = load_data(train_input)
    _test_headers, test_data  = load_data(test_input)

    train_labels = get_labels(train_data)
    test_labels  = get_labels(test_data)

    majority_label = majority_vote(train_labels)

    train_predictions = predict(majority_label, len(train_data))
    test_predictions  = predict(majority_label, len(test_data))

    train_error = calculate_error(train_predictions, train_labels)
    test_error  = calculate_error(test_predictions,  test_labels)

    write_labels(train_out,  train_predictions)
    write_labels(test_out,   test_predictions)
    write_metrics(metrics_out, train_error, test_error)

    print(f"\n{train_input}")
    print(f"Majority label : {majority_label}")
    print(f"error(train)   : {train_error:.6f}")
    print(f"error(test)    : {test_error:.6f}")


if __name__ == '__main__':
    main()