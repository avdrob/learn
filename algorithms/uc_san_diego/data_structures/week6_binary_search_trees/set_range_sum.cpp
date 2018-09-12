#include <iostream>
#include <stack>
#include <set>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

template <typename TKey>
class splay_tree {
private:
    unsigned long tree_size;

    struct node {
        node *left, *right, *parent;
        TKey key;
        TKey subtree_sum;

        node(const TKey &init = TKey())
            : left(nullptr), right(nullptr), parent(nullptr), key(init),
              subtree_sum(key)
        {}

        ~node()
        {
            if (left) {
                delete left;
            }
            if (right) {
                delete right;
            }
        }
    } *root;

    void left_rotate(node *x)
    {
        node *y = x->right;
        if (!y) {
            return;
        }

        TKey a = 0, c = 0;
        if (x->left) {
            a = x->left->subtree_sum;
        }
        if (y->right) {
            c = y->right->subtree_sum;
        }
        x->subtree_sum -= y->key + c;
        y->subtree_sum += x->key + a;

        x->right = y->left;
        if (y->left) {
            y->left->parent = x;
        }

        if (!x->parent) {
            /* x was root */
            root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }

        y->parent = x->parent;
        x->parent = y;
        y->left = x;
    }

    void right_rotate(node *y)
    {
        node *x = y->left;
        if (!x) {
            return;
        }

        TKey a = 0, c = 0;
        if (x->left) {
            a = x->left->subtree_sum;
        }
        if (y->right) {
            c = y->right->subtree_sum;
        }
        y->subtree_sum -= x->key + a;
        x->subtree_sum += y->key + c;

        y->left = x->right;
        if (x->right) {
            x->right->parent = y;
        }

        if (!y->parent) {
            /* y was root */
            root = x;
        }
        else if (y == y->parent->left) {
            y->parent->left = x;
        }
        else {
            y->parent->right = x;
        }

        x->parent = y->parent;
        y->parent = x;
        x->right = y;
    }

    void splay(node *splay_node)
    {
        if (!splay_node) {
            /* oops */
            return;
        }
        else if (root == splay_node) {
            /* splay_node is already a root, nothing to do */
            return;
        }

        while (splay_node->parent) {
            node *parent = splay_node->parent;
            node *grandparent = parent->parent;

            if (grandparent == nullptr) {
                /* Zig case: parent is root */
                if (splay_node == parent->left) {
                    right_rotate(parent);
                }
                else {
                    left_rotate(parent);
                }
            }
            else if (splay_node == parent->left &&
                    parent == grandparent->left) {
                /* left Zig-Zig case */
                right_rotate(parent);
                right_rotate(grandparent);
                right_rotate(grandparent);
            }
            else if (splay_node == parent->right &&
                    parent == grandparent->right) {
                /* right Zig-ZIg case */
                left_rotate(parent);
                left_rotate(grandparent);
                left_rotate(grandparent);
            }
            else if (splay_node == parent->left) {
                /* Zig-Zag case */
                right_rotate(parent);
                left_rotate(grandparent);
            }
            else {
                /* Another Zig-Zag case */
                left_rotate(parent);
                right_rotate(grandparent);
            }
        }
    }

    node *find_(const TKey &key)
    {
        node *res = root;
        while (res) {
            if (key < res->key && res->left) {
                res = res->left;
            }
            else if (key > res->key && res->right) {
                res = res->right;
            }
            else {
                break;
            }
        }

        splay(res);
        return res;
    }

    void remove_(node *n)
    {
        if (!n) {
            return;
        }

        node *succ, *pred;
        node *left_subtree, *right_subtree;
        if (succ = next_node(n)) {
            splay(succ);
            splay(n);

            succ->left = n->left;
            succ->parent = nullptr;
            root = succ;

            if (succ->left) {
                succ->left->parent = succ;
                succ->subtree_sum += succ->left->subtree_sum;
            }
        }
        else if (pred = prev_node(n)) {
            splay(pred);
            splay(n);

            pred->right = n->right;
            pred->parent = nullptr;
            root = pred;

            if (pred->right) {
                pred->right->parent = pred;
                pred->subtree_sum += pred->right->subtree_sum;
            }
        }
        else {
            /* We're actually removing the root */
            root = nullptr;
        }

        n->left = nullptr;
        n->right = nullptr;
        n->parent = nullptr;
        tree_size--;
        delete n;
    }

    node *subtree_min(node *n)
    {
        while (n->left) {
            n = n->left;
        }
        return n;
    }

    node *subtree_max(node *n)
    {
        while (n->right) {
            n = n->right;
        }
        return n;
    }

    node *next_node(node *n)
    {
        if (n->right) {
            return subtree_min(n->right);
        }

        node *p = n->parent;
        while (p && n == p->right) {
            n = p;
            p = p->parent;
        }
        return p;
    }

    node *prev_node(node *n)
    {
        if (n->left) {
            return subtree_max(n->left);
        }

        node *p = n->parent;
        while (p && n == p->left) {
            n = p;
            p = p->parent;
        }
        return p;
    }


public:
    splay_tree() : root(nullptr), tree_size(0) {}
    virtual ~splay_tree() { delete root; }

    bool find(const TKey &key)
    {
        node *n = find_(key);
        if (n && n->key == key) {
            return true;
        }
        return false;
    }

    void insert(const TKey &key)
    {
        node *new_node = root;
        node *parent = nullptr;

        while (new_node) {
            parent = new_node;
            if (key < new_node->key) {
                new_node = new_node->left;
            }
            else if (key > new_node->key) {
                new_node = new_node->right;
            }
            else {
                /* key is already present in set */
                return;
            }
        }
        new_node = new node(key);
        new_node->parent = parent;

        if (!parent) {
            root = new_node;
        }
        else if (key < parent->key) {
            parent->left = new_node;
        }
        else {
            parent->right = new_node;
        }

        while (parent) {
            parent->subtree_sum += key;
            parent = parent->parent;
        }

        splay(new_node);
        tree_size++;
    }
    
    void remove(const TKey &key)
    {
        node *n = find_(key);
        if (n && n->key == key) {
            remove_(n);
        }
    }

    TKey sum_ge(const TKey &key)
    {
        TKey res = 0;

        find_(key);
        if (root && root->key >= key) {
            res += root->key;
        }
        if (root && root->right) {
            res += root->right->subtree_sum;
        }

        return res;
    } 

    TKey sum_lt(const TKey &key)
    {
        TKey res = 0;

        find_(key);
        if (root && root->key < key) {
            res += root->key;
        }
        if (root && root->left) {
            res += root->left->subtree_sum;
        }

        return res;
    }

    bool empty() const { return tree_size == 0; }
    unsigned long size() const {return tree_size; }
};

class set_range_tree : public splay_tree<unsigned long> {
private:
    unsigned long last_sum;
    const unsigned long M = 1000000001;

public:
    set_range_tree() : last_sum(0) {}

    void add(unsigned long i)
    {
        insert((i + last_sum) % M);
    }

    void del(unsigned long i)
    {
        remove((i + last_sum) % M);
    }

    bool find(unsigned long i)
    {
        return splay_tree::find((i + last_sum) % M);
    }

    unsigned long sum(unsigned long l, unsigned long r)
    {
        last_sum = sum_ge((l + last_sum) % M) -\
                    sum_ge((r + last_sum) % M + 1);
        return last_sum;
    }
};

void stress_test()
{
    int n = 10;
    unsigned long m = 100;
    unsigned long x = 0;

    const unsigned long M = 53;

    while (true) {
        set<unsigned long> range_set;
        set_range_tree range_tree;
        stringstream ss;
        x = 0;

        srand(time(NULL));
        for (int j = 0; j < n; j++) {
            int cmd = rand() % 4;
            unsigned long i = rand() % (m + 1);
            unsigned long l;
            unsigned long r;

            do {
                l = rand() % (m + 1);
                r = rand() % (m + 1);
            } while ((l + x) % M > (r + x) % M);

            switch(cmd) {
            case 0:     /* add */
                ss << "add " << i << endl;
                range_tree.add(i);
                range_set.insert((i + x) % M);
                break;
            case 1:     /* del */
                ss << "del " << i << endl;
                range_tree.del((i + x) % M);
                range_set.erase((i + x) % M);
                break;
            case 2:     /* find */
                ss << "find " << i << endl;
                bool res_set_find, res_tree_find;
                res_set_find = range_set.find((i + x) % M) != range_set.end();
                res_tree_find = range_tree.find(i);
                if (res_set_find != res_tree_find) {
                    cerr << "WRONG ANSWER: find" << endl;
                    cerr << "Got: " << bool(res_tree_find) <<
                        "; Expected: " << bool(res_set_find) << endl;
                    for (auto it : range_set) {
                        cerr << it << " ";
                    }
                    cerr << endl;
                    cerr << ss.str();
                    return;
                }
                break;
            case 3:     /* sum */
                ss << "sum " << l << " " << r << endl;
                unsigned long res_set_sum = 0, res_tree_sum = 0;
                for (auto it : range_set) {
                    if (it >= ((l + x) % M) && it <= ((r + x) % M)) {
                        res_set_sum += it;
                    }
                }
                res_tree_sum = range_tree.sum(l, r);
                if (res_set_sum != res_tree_sum) {
                    cerr << "WRONG ANSWER: sum" << endl;
                    cerr << "Got: " << res_tree_sum << "; Expected: "
                        << res_set_sum << endl;
                    for (auto it : range_set) {
                        cerr << it << " ";
                    }
                    cerr << endl;
                    cerr << ss.str();
                    return;
                }
                x = res_set_sum;
                break;
            }
        }

    }
}

int main(int argc, char *argv[])
{
    // stress_test();
    // return 0;

    unsigned n;
    cin >> n;

    set_range_tree srt;
    for (int i = 0; i < n; i++) {
        char cmd;
        cin >> cmd;

        if (cmd == '+') {
            unsigned long i;
            cin >> i;
            srt.add(i);
        }
        else if (cmd == '-') {
            unsigned long i;
            cin >> i;
            srt.del(i);
        }
        else if (cmd == '?') {
            unsigned long i;
            cin >> i;
            if (srt.find(i)) {
                cout << "Found" << endl;
            }
            else {
                cout << "Not found" << endl;
            }
        }
        else if (cmd == 's') {
            unsigned long l, r;
            cin >> l >> r;
            cout << srt.sum(l, r) << endl;
        }
        else {
            continue;
        }
    }

    return 0;
}