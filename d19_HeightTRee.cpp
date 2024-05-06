#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Structure for a node in the AVL tree
struct Node
{
    string keyword;
    string meaning;
    int height;
    Node *left;
    Node *right;

    Node(string key, string val) : keyword(key), meaning(val), height(1), left(nullptr), right(nullptr) {}
};

// Function to get the height of a node
int getHeight(Node *node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

// Function to update the height of a node
void updateHeight(Node *node)
{
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// Function to perform left rotation
Node *rotateLeft(Node *y)
{
    Node *x = y->right;
    Node *T2 = x->left;

    x->left = y;
    y->right = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Function to perform right rotation
Node *rotateRight(Node *x)
{
    Node *y = x->left;
    Node *T2 = y->right;

    y->right = x;
    x->left = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Function to get the balance factor of a node
int getBalance(Node *node)
{
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to insert a new node into the AVL tree
Node *insert(Node *root, string key, string val)
{
    if (root == nullptr)
        return new Node(key, val);

    if (key < root->keyword)
        root->left = insert(root->left, key, val);
    else if (key > root->keyword)
        root->right = insert(root->right, key, val);
    else
    { // Key already exists, update the value
        root->meaning = val;
        return root;
    }

    updateHeight(root);

    // Rebalance the tree
    int balance = getBalance(root);

    if (balance > 1 && key < root->left->keyword) // Left Left Case
        return rotateRight(root);

    if (balance < -1 && key > root->right->keyword) // Right Right Case
        return rotateLeft(root);

    if (balance > 1 && key > root->left->keyword)
    { // Left Right Case
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && key < root->right->keyword)
    { // Right Left Case
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Function to find a node with given key
Node *find(Node *root, string key, int &comparisons)
{
    if (root == nullptr)
        return nullptr;

    comparisons++;

    if (root->keyword == key)
        return root;
    else if (key < root->keyword)
        return find(root->left, key, comparisons);
    else
        return find(root->right, key, comparisons);
}

// Function to print the tree in inorder traversal (sorted order)
void inorder(Node *root)
{
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << root->keyword << ": " << root->meaning << endl;
    inorder(root->right);
}

// Function to print the tree in reverse inorder traversal (sorted order, descending)
void reverseInorder(Node *root)
{
    if (root == nullptr)
        return;
    reverseInorder(root->right);
    cout << root->keyword << ": " << root->meaning << endl;
    reverseInorder(root->left);
}

// Function to delete a node with given key
Node *deleteNode(Node *root, string key)
{
    if (root == nullptr)
        return root;

    if (key < root->keyword)
        root->left = deleteNode(root->left, key);
    else if (key > root->keyword)
        root->right = deleteNode(root->right, key);
    else
    {
        if (root->left == nullptr || root->right == nullptr)
        {
            Node *temp = root->left ? root->left : root->right;
            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp; // Copy the contents of non-empty child
            delete temp;
        }
        else
        {
            Node *temp = root->right;
            while (temp->left != nullptr)
                temp = temp->left;

            root->keyword = temp->keyword;
            root->meaning = temp->meaning;

            root->right = deleteNode(root->right, temp->keyword);
        }
    }

    if (root == nullptr)
        return root;

    updateHeight(root);

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) // Left Left Case
        return rotateRight(root);

    if (balance > 1 && getBalance(root->left) < 0)
    { // Left Right Case
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) // Right Right Case
        return rotateLeft(root);

    if (balance < -1 && getBalance(root->right) > 0)
    { // Right Left Case
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Function to delete the entire AVL tree
void deleteTree(Node *root)
{
    if (root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Function to display the menu
void displayMenu()
{
    cout << "\nMenu:\n";
    cout << "1. Add Keyword\n";
    cout << "2. Delete Keyword\n";
    cout << "3. Update Meaning\n";
    cout << "4. Display Sorted Data (Ascending)\n";
    cout << "5. Display Sorted Data (Descending)\n";
    cout << "6. Find Maximum Comparisons\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    Node *root = nullptr;
    int choice;
    string key, meaning;

    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nEnter Keyword: ";
            cin >> key;
            cout << "Enter Meaning: ";
            cin.ignore();
            getline(cin, meaning);
            root = insert(root, key, meaning);
            cout << "Keyword added successfully!" << endl;
            break;
        case 2:
            cout << "\nEnter Keyword to delete: ";
            cin >> key;
            root = deleteNode(root, key);
            cout << "Keyword deleted successfully!" << endl;
            break;
        case 3:
            cout << "\nEnter Keyword to update: ";
            cin >> key;
            cout << "Enter New Meaning: ";
            cin.ignore();
            getline(cin, meaning);
            root = deleteNode(root, key);
            root = insert(root, key, meaning);
            cout << "Meaning updated successfully!" << endl;
            break;
        case 4:
            cout << "\nSorted Data (Ascending):\n";
            inorder(root);
            break;
        case 5:
            cout << "\nSorted Data (Descending):\n";
            reverseInorder(root);
            break;
        case 6:
            cout << "\nEnter Keyword to find: ";
            cin >> key;
            {
                int comparisons = 0;
                find(root, key, comparisons);
                cout << "Maximum comparisons required: " << comparisons << endl;
            }
            break;
        case 7:
            cout << "\nExiting program...\n";
            break;
        default:
            cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 7);

    // Clean up memory
    deleteTree(root);

    return 0;
}

