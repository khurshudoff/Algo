/*
 Дано число N < 10^6 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево поиска, заданное наивным порядком вставки. Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Выведите элементы в порядке level-order (по слоям, “в ширину”).
 */
#include <iostream>
#include <queue>
#include <stack>

// Узел бинарного дерева
struct TreeNode {
    explicit TreeNode(int _value) : value(_value) {}

    int value = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

class Tree {
public:
    ~Tree();

    void Print() const;

    void Add(int value);

private:
    TreeNode* root = nullptr;

    void print_subtree(TreeNode* node) const;

    void delete_subtree(TreeNode* node);
};

Tree::~Tree() {
    if (!root) return;
    std::stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();
        if (node->left) st.push(node->left);
        if (node->right) st.push(node->right);
        delete node;
    }
}

void Tree::Print() const {
    std::queue<TreeNode*> q;
    if (root) q.push(root);
    while (!q.empty()) {
        TreeNode* cur = q.front();
        q.pop();

        std::cout << cur->value << " ";

        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

void Tree::Add(int value) {
    TreeNode** cur = &root;
    while (*cur) {
        if (value < (*cur)->value) {
            cur = &((*cur)->left);
        } else {
            cur = &((*cur)->right);
        }
    }
    *cur = new TreeNode(value);
}

int main() {

    Tree tree;

    int n;
    std::cin >> n;

    while(n--) {
        int v;
        std::cin >> v;
        tree.Add(v);
    }
    tree.Print();
    return 0;
}
