#include <iostream>
#include <algorithm>

using namespace std;
long long int INF = 1e8;

template<typename T>
class Node {
public:
    T value;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;

    Node(const Node<T> &other) : value(other.value) {
        if (other.left != nullptr) {
            left = new Node<T>(*other.left);
            left->parent = this;
        }
        if (other.right != nullptr) {
            right = new Node<T>(*other.right);
            right->parent = this;
        }
    }

    Node(const T &item, Node<T> *lptr = nullptr,
         Node<T> *rptr = nullptr, Node<T> *pptr = nullptr) :
            value(item), left(lptr), right(rptr), parent(pptr) {}

    ~Node() {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
    }
};

template<typename T>
class Iterator {
public:
    Iterator(Node<T> *p) : nodePtr(p) {}

    bool operator==(const Iterator &item) const {
        return item.nodePtr == this->nodePtr;
    }

    bool operator!=(const Iterator &item) const {
        return item.nodePtr != this->nodePtr;
    }

    T &operator*() const {
        return this->nodePtr->value;
    }

    Iterator &operator++() {
        if (nodePtr->value == INF) {
            while (nodePtr->left != nullptr) {
                nodePtr = nodePtr->left;
            }
        } else if (nodePtr->right != nullptr) {
            nodePtr = nodePtr->right;
            while (nodePtr->left != nullptr) {
                nodePtr = nodePtr->left;
            }
        } else {
            Node<T> *p = nodePtr->parent;
            while (p != nullptr && nodePtr == p->right) {
                nodePtr = p;
                p = p->parent;
            }
            nodePtr = p;
        }

        return *this;
    };

    Iterator operator++(int) {
        if (nodePtr->value == INF) {
            while (nodePtr->left != nullptr) {
                nodePtr = nodePtr->left;
            }
        } else if (nodePtr->right != nullptr) {
            nodePtr = nodePtr->right;
            while (nodePtr->left != nullptr) {
                nodePtr = nodePtr->left;
            }
        } else {
            Node<T> *p = nodePtr->parent;
            while (p != nullptr && nodePtr == p->right) {
                nodePtr = p;
                p = p->parent;
            }
            nodePtr = p;
        }

        return *this;
    };

    Iterator &operator--() {
        if (nodePtr->left != nullptr) {
            nodePtr = nodePtr->left;

            while (nodePtr->right != nullptr) {
                nodePtr = nodePtr->right;
            }
        } else {
            Node<T> *p = p = nodePtr->parent;
            while (p != nullptr && nodePtr == p->left) {
                nodePtr = p;
                p = p->parent;
            }
            nodePtr = p;
        }
        return *this;
    };

    Iterator operator--(int) {
        if (nodePtr->left != nullptr) {
            nodePtr = nodePtr->left;

            while (nodePtr->right != nullptr) {
                nodePtr = nodePtr->right;
            }
        } else {
            Node<T> *p = p = nodePtr->parent;
            while (p != nullptr && nodePtr == p->left) {
                nodePtr = p;
                p = p->parent;
            }
            nodePtr = p;
        }
        return *this;
    };

private:
    Node<T> *nodePtr;
};

template<typename T, class Compare = std::less<T>>
class BST {
    typedef Iterator<T> iterator;
    typedef Iterator<T> const_iterator;
public:
    BST() {
        root = new Node<T>(INF);
    }

    BST(const BST &bst) {
        root = new Node<T>(INF);
        root->left = new Node<T>(*bst.root->left);
        root->left->parent = root;
    }

    BST(Node<T> *r) {
        root = r;
    }

    ~BST() {
        delete root;
    }

    BST &operator=(const BST &bst) {
        size_ = bst.size_;
        root = new Node<T>(INF);
        root->left = new Node<T>(*bst.root->left);
        root->left->parent = root;
        return *this;
    }

    template<class InputIt>
    void assign(InputIt first, InputIt last) {
        if (root->left != nullptr)
            delete root->left;

        for (InputIt i = first; i != last; i++) {
            insert(*(i));
        }
    }

    iterator begin() {
        Node<T> *n = root;
        while (n->left != nullptr) {
            n = n->left;
        }
        return iterator(n);
    }

    const_iterator cbegin() {
        Node<T> *n = root;
        while (n->left != nullptr) {
            n = n->left;
        }
        return iterator(n);
    };

    iterator end() {
        Node<T> *n = root;
        while (n->right != nullptr) {
            n = n->right;
        }
        return iterator(n);
    };

    const_iterator cend() {
        Node<T> *n = root;
        while (n->right != nullptr) {
            n = n->right;
        }
        return iterator(n);
    };

    iterator insert(const T &value) {
        size_++;
        Node<T> *n = root;
        while (n->left != nullptr || n->right != nullptr) {
            if (value < n->value)
                n = n->left;
            else if (value > n->value)
                n = n->right;
        }
        if (value > n->value) {
            n->right = new Node<T>(value, nullptr, nullptr, n);
            return iterator(n->right);
        } else {
            n->left = new Node<T>(value, nullptr, nullptr, n);
            return iterator(n->left);
        }
    };

    void remove(const T &value) {
        removeNode(nullptr, false, root, value);
    }

    iterator find(const T &value) {
        Node<T> *n = root;
        while (n->left != nullptr || n->right != nullptr) {
            if (value < n->value)
                n = n->left;
            else if (value > n->value)
                n = n->right;
            else break;
        }
        if (value == n->value)
            return iterator(n);
        else return iterator(root);
    };

    const_iterator cfind(const T &value) {
        Node<T> *n = root;
        while (n->left != nullptr || n->right != nullptr) {
            if (value < n->value)
                n = n->left;
            else if (value > n->value)
                n = n->right;
            else break;
        }
        if (value == n->value)
            return iterator(n);
        else return iterator(root);
    };

    size_t size() const {
        return size_;
    };

    bool empty() const {
        return root->left == nullptr;
    };
private:
    Node<T> *root;
    int size_ = 0;

    void removeNode(Node<T> *p, bool direction, Node<T> *node, const T &value) {
        if (value == node->value) {
            if ((node->left == nullptr) || (node->right == nullptr)) {
                Node<T> *temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    if (direction)
                        p->right = nullptr;
                    else p->left = nullptr;
                    node = nullptr;
                } else
                    *node = *temp;
                delete temp;
            } else {
                Node<T> *temp = next(node);

                node->value = temp->value;

                return removeNode(node, true, node->right, temp->value);
            }
        }
        if (node != nullptr && value < node->value)
            removeNode(node, false, node->left, value);
        else if (node != nullptr)
            removeNode(node, true, node->right, value);
    };
};

int main() {
    BST<int> Tree;
    int n, a;
    cout << Tree.empty() << endl;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a;
        Tree.insert(a);
    }
    cout << "first: " << *(Tree.begin()) << endl;
    cout << "last:" << *(Tree.end()--) << endl;
    cout << "find last: " << *(Tree.find(a)) << endl;
    for (Iterator<int> i = Tree.begin(); i != Tree.end(); i++) {
        cout << (*i) << " ";
    }
    cout << endl << "empty: " << Tree.empty() << endl;
    cout << "size: " << Tree.size() << endl;
    Tree.remove(a);
    BST<int> Tree2;
    Tree2 = Tree;
    for (Iterator<int> i = Tree2.begin(); i != Tree2.end(); i++) {
        cout << (*i) << " ";
    }
    cout << endl;
    BST<int> Tree3;
    Tree3.assign(Tree.begin(), Tree.end()--);
    for (Iterator<int> i = Tree3.begin(); i != Tree3.end(); i++) {
        cout << (*i) << " ";
    }
    return 0;
}
