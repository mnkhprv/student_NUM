import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


def preprocess_data(df):
    df_clean = df.copy()
    cat_cols = ['Gender', 'Married', 'Dependents', 'Education', 'Self_Employed', 'Credit_History', 'Area']
    for col in cat_cols:
        df_clean[col] = df_clean[col].fillna(df_clean[col].mode()[0])
    num_cols = ['Loan_Amount', 'Term']
    for col in num_cols:
        df_clean[col] = df_clean[col].fillna(df_clean[col].median())
    df_clean['Status'] = df_clean['Status'].map({'Y': 1, 'N': 0})
    df_clean['Dependents'] = df_clean['Dependents'].replace('3+', '3').astype(int)
    label_cols = ['Gender', 'Married', 'Education', 'Self_Employed', 'Area']
    for col in label_cols:
        df_clean[col] = df_clean[col].astype('category').cat.codes
    return df_clean

class Node:
    def __init__(self, feature=None, threshold=None, left=None, right=None, value=None):
        self.feature = feature
        self.threshold = threshold
        self.left = left
        self.right = right
        self.value = value

def entropy(y):
    if len(y) == 0: return 0
    counts = np.bincount(y)
    probs = counts / len(y)
    return -np.sum([p * np.log2(p) for p in probs if p > 0])

class DecisionTree:
    def __init__(self, max_depth=3):
        self.max_depth = max_depth
        self.root = None

    def fit(self, X, y):
        self.root = self._grow_tree(X, y)

    def _grow_tree(self, X, y, depth=0):
        n_samples, n_feats = X.shape
        n_labels = len(np.unique(y))
        if depth >= self.max_depth or n_labels == 1 or n_samples < 2:
            return Node(value=np.bincount(y).argmax())
        
        best_feat, best_thresh = self._best_split(X, y)
        if best_feat is None: return Node(value=np.bincount(y).argmax())

        left_idxs = np.where(X[:, best_feat] <= best_thresh)[0]
        right_idxs = np.where(X[:, best_feat] > best_thresh)[0]
        left = self._grow_tree(X[left_idxs, :], y[left_idxs], depth + 1)
        right = self._grow_tree(X[right_idxs, :], y[right_idxs], depth + 1)
        return Node(best_feat, best_thresh, left, right)

    def _best_split(self, X, y):
        best_gain = -1
        split_idx, split_thresh = None, None
        for feat_idx in range(X.shape[1]):
            thresholds = np.unique(X[:, feat_idx])
            for thr in thresholds:
                gain = self._ig(y, X[:, feat_idx], thr)
                if gain > best_gain:
                    best_gain, split_idx, split_thresh = gain, feat_idx, thr
        return split_idx, split_thresh

    def _ig(self, y, col, thr):
        p_ent = entropy(y)
        l, r = np.where(col <= thr)[0], np.where(col > thr)[0]
        if len(l) == 0 or len(r) == 0: return 0
        c_ent = (len(l)/len(y))*entropy(y[l]) + (len(r)/len(y))*entropy(y[r])
        return p_ent - c_ent
    def _most_common_label(self, y):
        return np.bincount(y).argmax() if len(y) > 0 else 0

    def predict(self, X):
        return np.array([self._traverse_tree(x, self.root) for x in X])

    def _traverse_tree(self, x, node):
        if node.value is not None: return node.value
        if x[node.feature] <= node.threshold:
            return self._traverse_tree(x, node.left)
        return self._traverse_tree(x, node.right)
    



def draw_node(ax, node, x, y, dx, dy, feature_names):
    if node.value is not None:
        label = "APPROVED" if node.value == 1 else "DENIED"
        color = "lightgreen" if node.value == 1 else "lightcoral"
        ax.text(x, y, label, bbox=dict(boxstyle="round,pad=0.3", fc=color, ec="black"), 
                ha='center', va='center', fontsize=10)
    else:
        label = f"{feature_names[node.feature]}\n<= {node.threshold}"
        ax.text(x, y, label, bbox=dict(boxstyle="round,pad=0.3", fc="lightblue", ec="black"), 
                ha='center', va='center', fontsize=8)
        
        lx, ly = x - dx, y - dy
        ax.plot([x, lx], [y, ly], 'k-', lw=1)
        ax.text((x + lx)/2, (y + ly)/2, 'True', ha='right', fontsize=7)
        draw_node(ax, node.left, lx, ly, dx/2, dy, feature_names)
        
        rx, ry = x + dx, y - dy
        ax.plot([x, rx], [y, ry], 'k-', lw=1)
        ax.text((x + rx)/2, (y + ry)/2, 'False', ha='left', fontsize=7)
        draw_node(ax, node.right, rx, ry, dx/2, dy, feature_names)


df = pd.read_csv('loan_train.csv')
feature_names = df.columns.tolist()[:-1]
df_processed = preprocess_data(df)

X = df_processed.drop('Status', axis=1).values
y = df_processed['Status'].values

clf = DecisionTree(max_depth=3)
clf.fit(X, y)
preds = clf.predict(X)
acc = np.mean(preds == y)
print(f"\nСургалтын өгөгдөл дээрх нарийвчлал: {acc * 100:.2f}%")

fig, ax = plt.subplots(figsize=(12, 8))
ax.axis('off')
draw_node(ax, clf.root, 0.5, 1.0, 0.25, 0.2, feature_names)

plt.title("Loan Approval Decision Tree (From Scratch)", fontsize=15)
plt.show() 