#include <iostream>
#include <string>

struct Node {
    std::string name;
    int id;
    Node* left;
    Node* right;

    Node(const std::string& n, int i) : name(n), id(i), left(nullptr), right(nullptr) {}
};

class SplayTree {
private:
    Node* root;

    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    Node* splay(Node* root, const std::string& name) {
        if (root == nullptr || root->name == name)
            return root;

        if (root->name > name) {
            if (root->left == nullptr) return root;
            if (root->left->name > name) {
                root->left->left = splay(root->left->left, name);
                root = rightRotate(root);
            } else if (root->left->name < name) {
                root->left->right = splay(root->left->right, name);
                if (root->left->right != nullptr)
                    root->left = leftRotate(root->left);
            }
            return (root->left == nullptr) ? root : rightRotate(root);
        } else {
            if (root->right == nullptr) return root;
            if (root->right->name > name) {
                root->right->left = splay(root->right->left, name);
                if (root->right->left != nullptr)
                    root->right = rightRotate(root->right);
            } else if (root->right->name < name) {
                root->right->right = splay(root->right->right, name);
                root = leftRotate(root);
            }
            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }

    Node* join(Node* leftTree, Node* rightTree) {
        if (!leftTree) return rightTree;
        if (!rightTree) return leftTree;

        leftTree = splay(leftTree, rightTree->name);
        leftTree->right = rightTree;
        return leftTree;
    }

public:
    SplayTree() : root(nullptr) {}

    void insert(const std::string& name, int id) {
        if (root == nullptr) {
            root = new Node(name, id);
            return;
        }
        root = splay(root, name);
        if (root->name == name) return;

        Node* newNode = new Node(name, id);
        if (root->name > name) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        } else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }
        root = newNode;
    }

    void remove(const std::string& name) {
        if (root == nullptr) return;

        root = splay(root, name);
        if (root->name != name) return;

        Node* temp = root;
        root = join(root->left, root->right);
        delete temp;
    }

    int search(const std::string& name) {
        root = splay(root, name);
        if (root && root->name == name) {
            return root->id;
        }
        return -1; // Повертає -1, якщо елемент не знайдено
    }

    void inorder(Node* root) {
        if (root == nullptr) return;
        inorder(root->left);
        std::cout << root->name << " (" << root->id << ") ";
        inorder(root->right);
    }

    void printInOrder() {
        inorder(root);
        std::cout << std::endl;
    }

    ~SplayTree() {
        while (root != nullptr) {
            remove(root->name);
        }
    }
};

void displayMenu() {
    std::cout << "1. Додати елемент\n";
    std::cout << "2. Видалити елемент\n";
    std::cout << "3. Пошук елемента\n";
    std::cout << "4. Вивести всі елементи\n";
    std::cout << "5. Вихід\n";
}

void initializeTree(SplayTree& tree) {
    tree.insert("Alice", 1);
    tree.insert("Bob", 2);
    tree.insert("Charlie", 3);
    tree.insert("David", 4);
    tree.insert("Eve", 5);
}

int main() {
    SplayTree tree;
    initializeTree(tree);

    int choice;
    std::string name;
    int id;

    while (true) {
        displayMenu();
        std::cout << "Виберіть опцію: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Введіть назву: ";
                std::cin >> name;
                std::cout << "Введіть ідентифікатор: ";
                std::cin >> id;
                tree.insert(name, id);
                std::cout << "Елемент додано.\n";
                break;
            case 2:
                std::cout << "Введіть назву для видалення: ";
                std::cin >> name;
                tree.remove(name);
                std::cout << "Елемент видалено (якщо існував).\n";
                break;
            case 3:
                std::cout << "Введіть назву для пошуку: ";
                std::cin >> name;
                id = tree.search(name);
                if (id != -1)
                    std::cout << "Ідентифікатор елемента: " << id << std::endl;
                else
                    std::cout << "Елемент не знайдено.\n";
                break;
            case 4:
                tree.printInOrder();
                break;
            case 5:
                std::cout << "Вихід...\n";
                return 0;
            default:
                std::cout << "Неправильний вибір. Спробуйте ще раз.\n";
        }
    }
}
