#include <iostream>
#include <vector>
#include <stack>
#include <tuple>
#include <set>

using namespace std;

template <typename T>
class TreeNode {
public:
    TreeNode(T data_)
        : data(data_), left(nullptr), right(nullptr), parent(nullptr) 
    {}

    TreeNode()
        : left(nullptr), right(nullptr), parent(nullptr)
    {}

    void attach_left(TreeNode *left_)
    {
        left = left_;
        if (left) {
            left->parent = this;
        }
    }

    void attach_right(TreeNode *right_)
    {
        right = right_;
        if (right) {
            right->parent = this;
        }
    }

    void set_data(T data_)
    {
        data = data_;
    }

    tuple<T, T> get_min_max_key()
    {
        stack<TreeNode*> pool;
        T cur_min, cur_max;

        cur_min = data;
        cur_max = data;
        pool.push(this);
        while (!pool.empty()) {
            const TreeNode *node = pool.top();
            pool.pop();

            cur_min = min(cur_min, node->data);
            cur_max = max(cur_max, node->data);

            if (node->right) {
                pool.push(node->right);
            }
            if (node->left) {
                pool.push(node->left);
            }
        }
        
        return make_tuple(cur_min, cur_max);
    }

    bool is_bst()
    {
        stack<tuple<const TreeNode*, T, T>> pool;
        T min_key, max_key;

        tie(min_key, max_key) = get_min_max_key();
        pool.push(make_tuple(this, min_key, ++max_key));
        while(!pool.empty()) {
            const TreeNode *node;
            T lower_bound, upper_bound;
            tie(node, lower_bound, upper_bound) = pool.top();
            pool.pop();

            if (!(node->data >= lower_bound &&
                    node->data < upper_bound)) {
                return false;
            }

            if (node->right) {
                pool.push(make_tuple(node->right, node->data, upper_bound));
            }
            if (node->left) {
                pool.push(make_tuple(node->left, lower_bound, node->data));
            }
        }

        return true;
    }

private:
    TreeNode *left, *right, *parent;
    T data;

    friend ostream &operator<<(ostream &os, const TreeNode &node)
    {
        os << node.data;
        return os;
    }
};


int main(int argc, char *argv[])
{
    unsigned n;
    cin >> n;

    vector<TreeNode<long long>> nodes(n);
    for (int i = 0; i < n; i++) {
        long long key;
        int left, right;

        cin >> key >> left >> right;
        nodes[i].set_data(key);
        if (left != -1) {
            nodes[i].attach_left(&nodes[left]);
        }
        if (right != -1) {
            nodes[i].attach_right(&nodes[right]);
        }
    }

    if (n <= 1) {
        cout << "CORRECT" << endl;
        return 0;
    }
    TreeNode<long long> *root = &nodes[0];
    if (root->is_bst()) {
        cout << "CORRECT" << endl;
    }
    else {
        cout << "INCORRECT" << endl;
    }

    return 0;
}