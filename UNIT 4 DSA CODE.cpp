
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

struct Node {
    int score;
    Node* left;
    Node* right;
    int height;

    Node(int s) {
        score = s;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

int height(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

// Right Rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + max(height(y->left),
                        height(y->right));

    x->height = 1 + max(height(x->left),
                        height(x->right));

    return x;
}

// Left Rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + max(height(x->left),
                        height(x->right));

    y->height = 1 + max(height(y->left),
                        height(y->right));

    return y;
}

// AVL Insertion
Node* insert(Node* root, int score,
             int& firstUnbalanced,
             string& rotation) {

    if (root == nullptr)
        return new Node(score);

    if (score < root->score) {
        root->left = insert(root->left, score,
                            firstUnbalanced, rotation);
    }
    else if (score > root->score) {
        root->right = insert(root->right, score,
                             firstUnbalanced, rotation);
    }
    else {
        return root;
    }

    root->height = 1 + max(height(root->left),
                          height(root->right));

    int balance = getBalance(root);

    // LL Case
    if (balance > 1 &&
        score < root->left->score) {

        if (firstUnbalanced == -1) {
            firstUnbalanced = root->score;
            rotation = "LL Rotation (Right Rotation)";
        }

        return rightRotate(root);
    }

    // RR Case
    if (balance < -1 &&
        score > root->right->score) {

        if (firstUnbalanced == -1) {
            firstUnbalanced = root->score;
            rotation = "RR Rotation (Left Rotation)";
        }

        return leftRotate(root);
    }

    // LR Case
    if (balance > 1 &&
        score > root->left->score) {

        if (firstUnbalanced == -1) {
            firstUnbalanced = root->score;
            rotation = "LR Rotation";
        }

        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (balance < -1 &&
        score < root->right->score) {

        if (firstUnbalanced == -1) {
            firstUnbalanced = root->score;
            rotation = "RL Rotation";
        }

        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Display Search Path
bool showSearchPath(Node* root, int score) {
    Node* current = root;

    cout << "Search Path: ";

    while (current != nullptr) {
        cout << current->score << " ";

        if (score == current->score) {
            cout << "\n";
            return false;
        }

        if (score < current->score)
            current = current->left;
        else
            current = current->right;
    }

    cout << score << "\n";
    return true;
}

// Display Leaderboard in Descending Order
void displayLeaderboard(Node* root) {
    if (root == nullptr)
        return;

    displayLeaderboard(root->right);
    cout << root->score << " ";
    displayLeaderboard(root->left);
}

// Store scores in descending order
void collectScores(Node* root, vector<int>& scores) {
    if (root == nullptr)
        return;

    collectScores(root->right, scores);
    scores.push_back(root->score);
    collectScores(root->left, scores);
}

int main() {
    Node* root = nullptr;
    int n, score;

    cout << "===== AVL LEADERBOARD APPLICATION =====\n";
    cout << "Enter number of scores: ";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cout << "\nEnter score " << i << ": ";
        cin >> score;

        // Prevent duplicate scores
        Node* temp = root;
        bool duplicate = false;

        while (temp != nullptr) {
            if (score == temp->score) {
                duplicate = true;
                break;
            }
            else if (score < temp->score)
                temp = temp->left;
            else
                temp = temp->right;
        }

        if (duplicate) {
            cout << "Duplicate score not allowed!\n";
            continue;
        }

        // Display path before insertion
        showSearchPath(root, score);

        int firstUnbalanced = -1;
        string rotation = "No rotation required";

        root = insert(root, score,
                      firstUnbalanced, rotation);

        if (firstUnbalanced != -1) {
            cout << "First Unbalanced Node: "
                 << firstUnbalanced << "\n";
            cout << "Rotation Applied: "
                 << rotation << "\n";
        }
        else {
            cout << "First Unbalanced Node: None\n";
            cout << "Rotation Applied: None\n";
        }

        cout << "Leaderboard (Highest to Lowest): ";
        displayLeaderboard(root);
        cout << "\n";
    }

    // Final Leaderboard
    cout << "\n===== FINAL LEADERBOARD =====\n";
    cout << "Rank\tScore\n";

    vector<int> scores;
    collectScores(root, scores);

    for (int i = 0; i < (int)scores.size(); i++) {
        cout << i + 1 << "\t"
             << scores[i] << "\n";
    }

    return 0;
}
