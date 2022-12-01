#include <iostream>

using namespace std;

class Node
{
    int val;
    Node *prev;
    Node *next;
    Node(int val, Node *prev = NULL, Node *next = NULL) : val(val), prev(prev), next(next) {}
    friend class LinkedList;
};

class LinkedList
{
    Node *head;

public:
    LinkedList()
    {
        head = NULL;
    }

    void insert_node(int val)
    {
        if (head == NULL)
        {
            head = new Node(val);
            head->next = head;
            head->prev = head;
            return;
        }

        if (val <= head->val)
        {
            Node *newnode = new Node(val, head->prev, head);
            head->prev->next = newnode;
            head->prev = newnode;
            head = newnode;
            return;
        }

        if (val >= head->prev->val)
        {
            Node *newnode = new Node(val, head->prev, head);
            head->prev->next = newnode;
            head->prev = newnode;
            return;
        }

        if (val >= head->prev->val)
        {
            Node *newnode = new Node(val, head->prev, head);
            head->prev->next = newnode;
            head->prev = newnode;
        }

        Node *currnode = head->next;
        while (currnode != head)
        {
            if (currnode->val >= val)
            {
                Node *newnode = new Node(val, currnode->prev, currnode);
                currnode->prev->next = newnode;
                currnode->prev = newnode;
                return;
            }
            currnode = currnode->next;
        }
    }

    void delete_node(int val)
    {
        if (head == NULL)
            return;

        if (head->val == val && head->next == head)
        {
            delete head;
            head = NULL;
            return;
        }

        if (head->val == val)
        {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            Node *temp = head;
            head = head->next;
            delete temp;
        }

        Node *currnode = head->next;
        while (currnode != head)
        {
            if (currnode->val == val)
            {
                currnode->prev->next = currnode->next;
                currnode->next->prev = currnode->prev;
                delete currnode;
                return;
            }
            currnode = currnode->next;
        }
    }

    void reverse_display()
    {
        if (head == NULL)
        {
            cout << "[]" << endl;
            return;
        }
        cout << "[";
        Node *currnode = head->prev;
        while (currnode != head)
        {
            cout << currnode->val << ", ";
            currnode = currnode->prev;
        }
        cout << currnode->val << "]" << endl;
    }

    void display()
    {
        if (head == NULL)
        {
            cout << "[]" << endl;
            return;
        }
        cout << "[" << head->val;
        Node *currnode = head->next;
        while (currnode != head)
        {
            cout << ", " << currnode->val;
            currnode = currnode->next;
        }
        cout << "]" << endl;
    }

    void destroy()
    {
        Node *currnode = head->next, *temp;
        while (currnode != head)
        {
            temp = currnode;
            currnode = currnode->next;
            delete temp;
        }
        delete head;
        head = NULL;
    }
};

int main()
{
    cout << "Example syntax : \n\tinsert 1 2 3 \n\treverse \n\tdelete 1 2 3 4 \n\texit\n";
    string choice = "";
    string temp = "";
    LinkedList list;
    while (choice != "exit")
    {
        if (choice == "reverse")
        {
            list.reverse_display();
        }
        else
        {
            list.display();
        }
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
                list.insert_node((int)(temp[i] - '0'));
            }
            else if (choice == "delete")
            {
                list.delete_node((int)(temp[i] - '0'));
            }
        }
    }
    list.destroy();
    return 0;
}
