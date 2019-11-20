/*
 Солдаты. В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.
Вариант HW_7_2.  Требуемая скорость выполнения команды - O(log n) амортизировано. Для решения задачи реализуйте сплей дерево.

 */

#include <iostream>
#include <stack>

struct TreeNode {
    explicit TreeNode(int _value) : value(_value) {}

    int value = 0;
    int nodesRight = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

class Tree {
public:
    ~Tree();

    void Add(int value);
    bool Find(int value);
    int CountNodesRight();
    TreeNode* FindStat(int k);
    void Delete(int k);

private:
    TreeNode* root = nullptr;
    void Splay(TreeNode* _root, TreeNode* cur);
    TreeNode* RotateRight(TreeNode* root);
    TreeNode* RotateLeft(TreeNode* root);
    void Merge(TreeNode* left, TreeNode* right, int nodesRight);
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

TreeNode* Tree::RotateRight(TreeNode* _root) {
    if (!_root) {
        return nullptr;
    }
    if (!_root->left) {
        return _root;
    }
    TreeNode* new_root = _root->left;
    _root->left = new_root->right;
    new_root->right = _root;
    new_root->nodesRight += _root->nodesRight + 1;
    return new_root;
}

TreeNode* Tree::RotateLeft(TreeNode* _root) {
    if (!_root) {
        return nullptr;
    }
    if (!_root->right) {
        return _root;
    }
    TreeNode* new_root = _root->right;
    _root->right = new_root->left;
    new_root->left = _root;
    _root->nodesRight -= new_root->nodesRight + 1;
    return new_root;
}

void Tree::Splay(TreeNode* _root, TreeNode* cur) {
    while (true) {
        TreeNode** r = &root;
        TreeNode** gp = nullptr;
        TreeNode** p = nullptr;
        while ((*r)->value != cur->value) {
            gp = p;
            p = r;
            if (cur->value < (*r)->value) {
                r = &(*r)->left;
            } else {
                r = &(*r)->right;
            }
        }
        if (p == nullptr) {
            return;
        }
        if (gp == nullptr) {
            if ((*p)->right == *r) {
                *p = RotateLeft(*p);
            } else {
                *p = RotateRight(*p);
            }
            return;
        }
        if (((*gp)->right == *p) && ((*p)->right == *r)) {
            *gp = RotateLeft(*gp);
            *gp = RotateLeft(*gp);
        } else if (((*gp)->left == *p) && ((*p)->left == *r)) {
            *gp = RotateRight(*gp);
            *gp = RotateRight(*gp);
        } else if (((*gp)->right == *p) && ((*p)->left == *r)) {
            *p = RotateRight(*p);
            *gp = RotateLeft(*gp);
        } else if (((*gp)->left == *p) && ((*p)->right == *r)) {
            *p = RotateLeft(*p);
            *gp = RotateRight(*gp);
        }
    }
}

int Tree::CountNodesRight() {
    return root->nodesRight;
}

void Tree::Add(int value) {
    TreeNode** cur = &root;
    while (*cur) {
        if (value < (*cur)->value) {
            cur = &((*cur)->left);
        } else {
            (*cur) -> nodesRight += 1;
            cur = &((*cur)->right);
        }
    }
    *cur = new TreeNode(value);
    Splay(root, *cur);
}

TreeNode* Tree::FindStat(int k) {
    k += 1;
    TreeNode* cur = root;
    while (true) {
        if (k == cur->nodesRight + 1) {
            return cur;
        } else if (k > cur->nodesRight) {
            k = k - (cur->nodesRight + 1);
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
}

void Tree::Merge(TreeNode* left, TreeNode* right, int nodesRight) {
    if (left == nullptr) {
        root = right;
        return;
    }
    if (right == nullptr) {
        root = left;
        return;
    }

    // find max left
    TreeNode* leftMax = left;
    while (leftMax->right) leftMax = leftMax->right;

    Splay(left, leftMax);
    root = leftMax;
    root->right = right;
    root->nodesRight = nodesRight;
}

void Tree::Delete(int k) {
    TreeNode* new_root = FindStat(k);
    Splay(root, new_root);
    Merge(root->left, root->right, root->nodesRight);
}

int main() {
    Tree tree;

    int n;
    std::cin >> n;
    while (n--) {
        int inp1 = 0;
        int inp2 = 0;

        std::cin >> inp1 >> inp2;
        if (inp1 == 1) {
            tree.Add(inp2);
            std::cout << tree.CountNodesRight() << std::endl;
        } else {
            tree.Delete(inp2);
        }
    }

    return 0;
}
