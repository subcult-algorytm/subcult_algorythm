#include <iostream>
#include <list>
#include <vector>

using namespace std;

int N, M;

struct Node
{
    char root;
    Node *left;
    Node *right;
};

Node tree[26];
vector<char> preorder_list;
vector<char> inorder_list;
vector<char> postorder_list;

void pre_order(Node *idx)
{
    preorder_list.push_back(idx->root);
    if (idx->left != nullptr) pre_order(idx->left);
    if (idx->right != nullptr) pre_order(idx->right);
}
void in_order(Node *idx)
{
    if (idx->left != nullptr) in_order(idx->left);
    inorder_list.push_back(idx->root);
    if (idx->right != nullptr) in_order(idx->right);
}
void post_order(Node *idx)
{
    if (idx->left != nullptr) post_order(idx->left);
    if (idx->right != nullptr) post_order(idx->right);
    postorder_list.push_back(idx->root);
}

int main()
{
    cin >> N;

    for (int i = 0; i < N; ++i)
    {
        char a, b, c;
        cin >> a >> b >> c;

        Node *left = b == '.' ? nullptr : (tree + (b - 'A'));
        Node *right = c == '.' ? nullptr : (tree + (c - 'A'));

        tree[a - 'A'] = Node{a, left, right};
    }

    pre_order(&tree[0]);
    in_order(&tree[0]);
    post_order(&tree[0]);

    for (const auto &iter : preorder_list) cout << iter;
    cout << "\n";
    for (const auto &iter : inorder_list) cout << iter;
    cout << "\n";
    for (const auto &iter : postorder_list) cout << iter;
}
