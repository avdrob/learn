#include <iostream>
#include <vector>
#include <deque>
#include <utility>

using namespace std;

struct TreeNode {
public:
    int key;
    vector<TreeNode*> children;

    TreeNode(int key_=0)
        : key(key_)
    {}

    void add_child(TreeNode *node)
    {
        children.push_back(node);
    }

    int height()
    {
        deque<pair<TreeNode*, int>> queue;
        int res = 0;

        queue.push_back(make_pair(this, 1));
        while (!queue.empty()) {
            const auto it = queue.front(); queue.pop_front();
            const TreeNode *node = it.first;
            const int height = it.second;

            res = max(res, height);
            for (const auto ch : node->children) {
                queue.push_back(make_pair(ch, height + 1));
            }
        }

        return res;
    }
};


int main(int argc, char *argv[])
{
    int n;
    cin >> n;

    TreeNode *nodes = new TreeNode[n];
    TreeNode *root = NULL;
    for (int i = 0; i < n; i++) {
        nodes[i] = TreeNode(i);
    }
    for (int i = 0; i < n; i++) {
        int par;
        cin >> par;

        if (par == -1) {
            root = &nodes[i];
            continue;
        }

        nodes[par].add_child(&nodes[i]);
    }

    cout << root->height() << endl;

    delete [] nodes;
    return 0;
}