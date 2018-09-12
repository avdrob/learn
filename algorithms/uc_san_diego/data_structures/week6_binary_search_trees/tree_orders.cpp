#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <tuple>

using namespace std;

template <typename T>
class TreeNode {
public:
    TreeNode(T data_)
        : data(data_), left(nullptr), right(nullptr),
          parent(nullptr), root(this)
    {}

    TreeNode()
        : left(nullptr), right(nullptr), parent(nullptr),
          root(this)
    {}

    void attach_left(TreeNode *left_)
    {
        left = left_;
        if (left) {
            left->parent = this;
            left->root = root;
        }
    }

    void attach_right(TreeNode *right_)
    {
        right = right_;
        if (right) {
            right->parent = this;
            right->root = root;
        }
    }

    void set_data(T data_)
    {
        data = data_;
    }

    TreeNode *get_root()
    {
        return root;
    }

    enum class NodeState {
        PROCESSED = 0,
        NOT_PROCESSED
    };

    void inorder(ostream &os)
    {
        stack<pair<const TreeNode*, NodeState>> pool;

        pool.push(make_pair(this, NodeState::NOT_PROCESSED));
        while (!pool.empty()) {
            const TreeNode *node;
            NodeState state;
            tie(node, state) = pool.top();
            pool.pop();

            switch(state) {
            case NodeState::NOT_PROCESSED:
                if (node->right) {
                    pool.push(make_pair(node->right, NodeState::NOT_PROCESSED));
                }
                pool.push(make_pair(node, NodeState::PROCESSED));
                if (node->left) {
                    pool.push(make_pair(node->left, NodeState::NOT_PROCESSED));
                }
                break;

            case NodeState::PROCESSED:
                os << *node << " ";
            }
        }
        os << endl;
    }

    void postorder(ostream &os)
    {
        stack<const TreeNode*> pool;

        pool.push(this);
        while(!pool.empty()) {
            const TreeNode *node = pool.top();
            pool.pop();
            os << *node << " ";

            if (node->right) {
                pool.push(node->right);
            }
            if (node->left) {
                pool.push(node->left);
            }
        }
        os << endl;
    }

    void preorder(ostream &os)
    {
        stack<pair<const TreeNode*, NodeState>> pool;

        pool.push(make_pair(this, NodeState::NOT_PROCESSED));
        while (!pool.empty()) {
            const TreeNode *node;
            NodeState state;
            tie(node, state) = pool.top();
            pool.pop();

            switch(state) {
            case NodeState::NOT_PROCESSED:
                pool.push(make_pair(node, NodeState::PROCESSED));
                if (node->right) {
                    pool.push(make_pair(node->right, NodeState::NOT_PROCESSED));
                }
                if (node->left) {
                    pool.push(make_pair(node->left, NodeState::NOT_PROCESSED));
                }
                break;

            case NodeState::PROCESSED:
                os << *node << " ";
            }
        }
        os << endl;
    }

private:
    TreeNode *left, *right, *parent, *root;
    T data;

    friend ostream &operator<<(ostream &os, const TreeNode &node)
    {
        os << node.data;
        return os;
    }
};


int main(int argc, char *argv[])
{
    int n;
    cin >> n;

    vector<TreeNode<unsigned>> nodes(n);
    for (int i = 0; i < n; i++) {
        unsigned key;
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

    TreeNode<unsigned> *root = nodes[0].get_root();
    root->inorder(cout);
    root->postorder(cout);
    root->preorder(cout);

    return 0;
}