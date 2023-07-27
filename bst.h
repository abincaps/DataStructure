#include <cstddef>
namespace ds {

template <typename Key>
class bst {
private:
    template <typename K>
    struct BstNode {
        BstNode<K>* left;
        BstNode<K>* right;
        K key;
        size_t count;
        BstNode(K key) : left(nullptr), right(nullptr), key(key), count(1) {}
        void get_value(const BstNode<K>& other) {
            key = other.key;
            count = other.count;
        }
    };
    using type = BstNode<Key>;
    using pointer = BstNode<Key>*;
    pointer root = nullptr;
    size_t size_of_elements = 0;

private:
    size_t count(const pointer p, const Key& key) const {
        if (nullptr == p) {
            return 0;
        }

        if (key < p->key) {
            return count(p->left, key);
        } else if (key > p->key) {
            return count(p->right, key);
        }

        return p->count;
    }
    pointer insert(pointer p, const Key& key) {
        if (nullptr == p) {
            size_of_elements++;
            return new type(key);
        }

        if (key < p->key) {
            p->left = insert(p->left, key);
        } else if (key > p->key) {
            p->right = insert(p->right, key);
        } else {
            p->count++;
        }

        return p;
    }

    pointer erase(pointer p, const Key& key) {
        if (nullptr == p) {
            return p;
        }

        if (key < p->key) {
            p->left = erase(p->left, key);
        } else if (key > p->key) {
            p->right = erase(p->right, key);
        } else {
            if (p->left == nullptr && p->right == nullptr) {
                delete p;
                size_of_elements--;
                p = nullptr;
            } else if (p->left && p->right) {
                // 找前驱结点或后继结点替换
                // 前驱：比要删除的关键字小的中最大的
                // 先往左再一直往右
                // 后继：比要删除的关键字大的中最小的
                // 先往右再一直往左
                // 这里选择替换后继结点
                pointer cur = p->right;
                while (cur->left) {
                    cur = cur->left;
                }
                p->get_value(*cur);
                p->right = erase(p->right, cur->key);
            } else {
                pointer temp = p;
                p = p->left ? p->left : p->right;
                delete temp;
                size_of_elements--;
            }
        }
        return p;
    }

public:
    void insert(const Key& key) { root = insert(root, key); }
    size_t count(const Key& key) const { return count(root, key); }

    void erase(const Key& key) { root = erase(root, key); }
    size_t size() const { return size_of_elements; }
};

}  // namespace ds