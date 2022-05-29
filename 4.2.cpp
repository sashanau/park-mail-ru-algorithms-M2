#include <iostream>
#include <vector>

template<class T>
struct DefaultComparator {
    int operator()(const T &l, const T &r) const {
        if (l < r)
            return 1;
        else if (l > r)
            return -1;
        else
            return 0;
    }
};

template<class Key, class Comparator = DefaultComparator<Key>>
class AvlTree {
    struct Node {
        Key key;

        Node *left;
        Node *right;
        int height;
        int count;

        Node(const Key &key) :
                left(nullptr),
                right(nullptr),
                key(key),
                height(1),
                count(1) {
        }
    };

public:
    AvlTree(Comparator comp = Comparator()) : root(nullptr), comp(comp) {

    }

    ~AvlTree() {
        free_all(root);
    }

    bool has(const Key &key) const {
        return hasInternal(key, root);
    }

    void insert(const Key &key) {
        root = insertInternal(key, root);
    }

    void erase(const Key &key) {
        root = eraseInternal(findKeyInternal(key), root);
    }

    int findNum(const Key &key) const {
        return findNumInternal(key, root);
    }

private:
    void free_all(Node *node){
        if (node->left)
            free_all(node->left);
        if (node->right)
            free_all(node->right);
        delete node;
    }

    int findKeyInternal(int k){
        Node* node = root;
        while (node) {
            int temp = node->left ? node->left->count : 0;
            if (temp == k)
                return node->key;
            if (temp > k)
                node = node->left;
            else {
                node = node->right;
                k = k - 1 - temp;
            }
        }
        return -1;
    }

    int findNumInternal(const Key &key, Node *node) const {
        if (!node)
            return -1;
        Node *tmp = node;
        int cmp_res;
        int i = 0;
        while (tmp != nullptr){
            cmp_res = comp(key, tmp->key);
            if (cmp_res == 1){
                if (tmp->left) {
                    i += tmp->left->count + 1;
                    tmp = tmp->right;
                } else{
                    tmp = tmp->right;
                    i += 1;
                }
            } else if (cmp_res == -1){
                tmp = tmp->left;
            } else{
                if (tmp->left) {
                    return i + tmp->left->count;
                } else{
                    return i;
                }
            }
        }
        return -1;
    }

    bool hasInternal(const Key &key, Node *node) const {
        if (!node)
            return false;
        int cmp_res = comp(key, node->key);
        if (cmp_res == 0)
            return true;
        if (cmp_res == -1)
            return hasInternal(key, node->left);
        if (cmp_res == 1)
            return hasInternal(key, node->right);
        return false;
    }

    Node *eraseInternal(const Key &key, Node *node) {
        if (!node)
            return nullptr;
        int cmp_res = comp(key, node->key);
        if (cmp_res == -1)
            node->left = eraseInternal(key, node->left);
        else if (cmp_res == 1)
            node->right = eraseInternal(key, node->right);
        else {
            Node *left = node->left;
            Node *right = node->right;

            delete node;

            if (!right)
                return left;

            Node *min_node = find_min(right);
            min_node->right = remove_min(right);
            min_node->left = left;

            return balance(min_node);
        }
        return balance(node);
    }


    Node *find_min(Node *node) {
        return node->left?find_min(node->left):node;
    }

    Node *remove_min(Node *node) {
        if (node->left == nullptr)
            return node->right;
        node->left = remove_min(node->left);
        return balance(node);
    }

    Node *insertInternal(const Key &key, Node *node) {
        Node *tmp = node;
        if (!node)
            return new Node(key);
        int cmp_res = comp(key, node->key);
        if (cmp_res == -1)
            node->left = insertInternal(key, node->left);
        else if (cmp_res == 1)
            node->right = insertInternal(key, node->right);
        else
            return tmp;
        return balance(node);
    }

    int height(Node *node) {
        if (!node)
            return 0;
        return node->height;
    }

    int count(Node *node) {
        if (!node)
            return 0;
        return node->count;
    }

    int bfactor(Node *node) {
        return height(node->right) - height(node->left);
    }

    void fix_height(Node *node) {
        if (!node)
            return;
        if (height(node->left) > height(node->right))
            node->height = std::max(height(node->left) + 1, height(node->right));
        else
            node->height = std::max(height(node->left), height(node->right) + 1);
        node->count = count(node->left) + count(node->right) + 1;
    }

    Node *rotate_left(Node *node) {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;

        fix_height(node);
        fix_height(tmp);

        return tmp;
    }

    Node *rotate_right(Node *node) {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;

        fix_height(node);
        fix_height(tmp);

        return tmp;
    }

    Node *balance(Node *node) {
        fix_height(node);

        int bf = bfactor(node);
        if (bf == 2) {
            if (bfactor(node->right) < 0) {
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);
        } else if (bf == -2) {
            if (bfactor(node->left) > 0) {
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }
        return node;
    }

    Node *root;
    Comparator comp;
};

int main() {
    AvlTree<int> avlTree;
    int n, com, val;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> com >> val;
        if (com == 1) {
            avlTree.insert(val);
            std::cout << avlTree.findNum(val) << std::endl;
        } else if (com == 2){
            avlTree.erase(val);
        } else
            return 0;
    }
    return 0;
}
