#include <iostream>
#include <vector>
#include <stack>

template<class T>
struct DefaultComparator {
    bool operator()(const T &l, const T &r) const {
        if (l < r)
            return true;
        else
            return false;
    }
};

template<class Key, class Comparator = DefaultComparator<Key>>
class BinaryTree {
    struct Node {
        Node(Key val) :
                val(val),
                left(nullptr),
                right(nullptr) {}

        Key val;
        Node *left;
        Node *right;
    };

public:
    BinaryTree() {
        comp = Comparator();
        root = nullptr;
    }

    ~BinaryTree(){
        if (root == nullptr) {
            return;
        }
        std::stack<Node*> q1;
        std::stack<Node*> q2;
        Node *temp = root;
        while (temp != nullptr || !q1.empty())
        {
            while (temp != nullptr){
                q1.push(temp);
                temp = temp->left;
            }
            temp = q1.top();
            q1.pop();
            q2.push(temp);
            temp = temp->right;
        }
        while (!q2.empty()) {
            delete q2.top();
            q2.pop();
        }
    }

    Node *add(const Key &key) {
        if (root == nullptr) {
            root = new Node(key);
            return root;
        }
        Node *temp = root;
        while (true) {
            if (comp(key, temp->val)) {
                if (temp->left == nullptr) {
                    temp->left = new Node(key);
                    break;
                }
                temp = temp->left;
            } else {
                if (temp->right == nullptr) {
                    temp->right = new Node(key);
                    break;
                }
                temp = temp->right;
            }
        }
        return root;
    }

    void in_order() {
        if (root == nullptr) {
            return;
        }
        std::stack<Node*> q;
        Node *temp = this->root;
        while (temp != nullptr || !q.empty())
        {
            while (temp != nullptr){
                q.push(temp);
                temp = temp->left;
            }
            temp = q.top();
            q.pop();
            std::cout << temp->val << " ";
            temp = temp->right;
        }
    }

private:
    Node *root;
    Comparator comp;
};

int main() {
    BinaryTree<int> a;
    int n, temp;
    std::cin >> n;
    for (int i = 0; i < n; i++){
        std::cin >> temp;
        a.add(temp);
    }
    a.in_order();
    return 0;
}