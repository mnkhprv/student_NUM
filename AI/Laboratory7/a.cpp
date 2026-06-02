#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ctime>
#include <random>

using namespace std;

struct Row {
    vector<string> features;
    string label;
};

struct Node {
    int feature_index;
    string threshold;
    Node* left;
    Node* right;
    string prediction;
    bool is_leaf;

    Node() : left(nullptr), right(nullptr), is_leaf(false), feature_index(-1) {}
};

double calculate_gini(const vector<Row>& data) {
    if (data.empty()) return 0;
    map<string, int> counts;
    for (const auto& row : data) counts[row.label]++;

    double impurity = 1.0;
    for (auto const& item : counts) {
        double prob = (double)item.second / data.size();
        impurity -= prob * prob;
    }
    return impurity;
}

void best_split(const vector<Row>& data, int& best_feat, string& best_thresh) {
    double best_gini = 1.0;
    if (data.empty()) return;
    int n_features = data[0].features.size();

    for (int i = 0; i < n_features; i++) {
        for (const auto& row : data) {
            string val = row.features[i];
            vector<Row> left_set, right_set;

            for (const auto& r : data) {
                if (r.features[i] == val) left_set.push_back(r);
                else right_set.push_back(r);
            }

            if (left_set.empty() || right_set.empty()) continue;

            double p = (double)left_set.size() / data.size();
            double gini = p * calculate_gini(left_set) + (1 - p) * calculate_gini(right_set);

            if (gini < best_gini) {
                best_gini = gini;
                best_feat = i;
                best_thresh = val;
            }
        }
    }
}

Node* build_tree(vector<Row> data, int depth, int max_depth) {
    Node* node = new Node();
    map<string, int> counts;
    for (auto& r : data) counts[r.label]++;
    
    string majority_label = "";
    int max_c = -1;
    for (auto const& item : counts) {
        if (item.second > max_c) { majority_label = item.first; max_c = item.second; }
    }

    if (counts.size() == 1 || depth == max_depth || data.size() < 2) {
        node->is_leaf = true;
        node->prediction = majority_label;
        return node;
    }

    int feat_idx = -1;
    string thresh = "";
    best_split(data, feat_idx, thresh);

    if (feat_idx == -1) {
        node->is_leaf = true;
        node->prediction = majority_label;
        return node;
    }

    node->feature_index = feat_idx;
    node->threshold = thresh;

    vector<Row> left_data, right_data;
    for (auto& r : data) {
        if (r.features[feat_idx] == thresh) left_data.push_back(r);
        else right_data.push_back(r);
    }

    node->left = build_tree(left_data, depth + 1, max_depth);
    node->right = build_tree(right_data, depth + 1, max_depth);
    return node;
}

void delete_tree(Node* node) {
    if (node == nullptr) return;
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}

vector<Row> load_csv(string filename) {
    vector<Row> data;
    ifstream file(filename);
    
    if (!file.is_open()) {
        perror("Файл нээхэд алдаа гарлаа");
        return data;
    }

    string line, word;
    if (!getline(file, line)) return data;

    while (getline(file, line)) {
        if (line.empty() || line.find_first_not_of(" \t\n\r") == string::npos) continue;

        stringstream ss(line);
        vector<string> columns;
        
        while (getline(ss, word, ',')) {
            word.erase(remove(word.begin(), word.end(), '\r'), word.end());
            word.erase(remove(word.begin(), word.end(), '\n'), word.end());
            columns.push_back(word);
        }

        if (columns.size() >= 12) {
            Row row;
            row.label = columns.back(); 
            
            for (size_t i = 0; i < columns.size() - 1; ++i) {
                row.features.push_back(columns[i]);
            }
            data.push_back(row);
        }
    }
    
    file.close();
    return data;
}


int main() {
    string path = "loan_train.csv";
    cout << "Файл уншиж эхэллээ: " << path << endl; 
    vector<Row> dataset = load_csv(path);

    if (dataset.empty()) {
        cerr << "АЛДАА: Өгөгдөл хоосон байна эсвэл файл олдсонгүй!" << endl; 
        return 1;
    }

    cout << "Dataset loaded: " << dataset.size() << " rows." << endl;

    random_device rd;
    mt19937 g(rd());
    shuffle(dataset.begin(), dataset.end(), g);

    int train_size = dataset.size() * 0.8;
    vector<Row> train_data(dataset.begin(), dataset.begin() + train_size);
    vector<Row> test_data(dataset.begin() + train_size, dataset.end());

    cout << "Training tree (max depth 3)..." << endl;
    Node* root = build_tree(train_data, 0, 3);

    int correct = 0;
    for (const auto& row : test_data) {
        Node* curr = root;
        while (!curr->is_leaf) {
            if (row.features[curr->feature_index] == curr->threshold) curr = curr->left;
            else curr = curr->right;
        }
        if (curr->prediction == row.label) correct++;
    }

    cout << "------------------------------------" << endl;
    cout << "Accuracy: " << (double)correct / test_data.size() * 100 << "%" << endl;
    cout << "Correct: " << correct << " / " << test_data.size() << endl;

    delete_tree(root);
    return 0;
}