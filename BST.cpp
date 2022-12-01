#include <iostream>
#include <queue>

using namespace std;

class Node
{
    int val;
    Node *left;
    Node *right;
    Node(int val) : val(val) {}
    friend class BST;
};

class BST
{
    Node *root;
    Node *insert_helper(Node *node, int val)
    {
        if (node == NULL)
        {
            return new Node(val);
        }
        if (val < node->val)
            node->left = insert_helper(node->left, val);
        else
            node->right = insert_helper(node->right, val);
        return node;
    }

    Node *delete_helper(Node *node, int val)
    {
        if (node == NULL)
            return NULL;

        if (node->val == val)
        {
            if (node->left != NULL && node->right != NULL)
            {
                Node *temp = node->left;
                while (temp->right != NULL)
                {
                    temp = temp->right;
                }
                node->val = temp->val;
                node->left = delete_helper(node->left, temp->val);
                return node;
            }

            if (node->left)
                return node->left;
            return node->right;
        }

        if (val < node->val)
            node->left = delete_helper(node->left, val);
        else
            node->right = delete_helper(node->right, val);
        return node;
    }

public:
    BST()
    {
        root = NULL;
    }

    void insert_node(int val)
    {
        root = insert_helper(root, val);
    }

    void delete_node(int val)
    {
        root = delete_helper(root, val);
    }

    bool search(int val)
    {
        Node *node = root;
        while (node != NULL)
        {
            if (val < node->val)
                node = node->left;
            else if (val > node->val)
                node = node->right;
            else
                return true;
        }
        return false;
    }

    void display()
    {
        queue<Node *> deque;
        Node *node;
        deque.push(root);
        while (!deque.empty())
        {
            int n = deque.size();
            for (int i = 0; i < n; i++)
            {
                node = deque.front();
                deque.pop();
                if (node == NULL)
                    continue;
                cout << node->val << " ";
                deque.push(node->left);
                deque.push(node->right);
            }
            cout << endl;
        }
    }
};

int main()
{

    cout << "Example syntax : \n\tinsert 1 2 3 \n\tsearch \n\tdelete 1 2 3 4 \n\texit\n";
    string choice = "";
    string temp = "";
    BST tree;
    while (choice != "exit")
    {
        tree.display();
        getline(cin, temp);
        bool flag = false;
        choice = "";
        for (int i = 0; i < temp.length(); i++)
        {
            if (temp[i] == ' ' && !flag)
                flag = true;

            if (!flag)
            {
                choice += temp[i];
                continue;
            }

            if (temp[i] == ' ')
                continue;

            if (choice == "insert")
            {
                tree.insert_node((int)(temp[i] - '0'));
            }
            else if (choice == "delete")
            {
                tree.delete_node((int)(temp[i] - '0'));
            }
            else if (choice == "search")
            {
                cout << tree.search((int)(temp[i] - '0')) << " ";
            }
        }
        if (choice == "search")
            cout << endl;
    }
}
