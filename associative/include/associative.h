#include <stdio.h>
#include <string.h>
#include <cctype>
#include <iostream>

using namespace std;

class KeyValue {
    public :
    string key;
    string value;
    KeyValue * left;
    KeyValue * right;

    KeyValue () {
        key = "";
        value = "";
        left = nullptr;
        right = nullptr;
    }

    KeyValue (string k, string v) {
        key = k;
        value = v;
        left = nullptr;
        right = nullptr;
    }

    void operator = (string k) {
        this->value = k;
    }
};

//щас будем делать бинарное дерево
class AssociativeArray {

    int amount = 0;

    public:
    //конструктор
    //оператор добавления элемента << и удаления >>
    KeyValue * root = nullptr;

    KeyValue* insert_string(KeyValue * x, string z) {// x — корень поддерева, z — вставляемый ключ
        if (x == nullptr) {
            KeyValue *a = new KeyValue(z, "");
            return a;
        } // подвесим Node с key = z

        else if (z < x->key) {
            x->left = insert_string(x->left, z);
        }

        else if (z > x->key) {
            x->right = insert_string(x->right, z);
        }

        return x;
    }

    //вывод

    void output(KeyValue * x, int level) {
        if(!(x == nullptr)) {
            output(x->left,level + 1);
            for(int i = 0;i< level;i++) cout << "   ";
            cout << x->key << endl;
            output(x->right,level + 1);
        }
    }

    //оператор доступа []

    KeyValue* search (KeyValue * x, string k) {

        if (x == nullptr || k == x->key) {
            return x;
        }

        if (k < x->key) {
            return search(x->left, k);
        }

        else  {
            return search(x->right, k);
        }
    }

    string& operator[] (string k) {
        return search(this->root, k)->value;
    }

    void operator<< (string k) {
        this->root = insert_string(this->root, k);
    }

    void operator<< (KeyValue second) {
        this->root = insert_node(this->root, second);
    }

    void operator>> (string k) {
        this->root = takeOut(this->root, k);
    }

    KeyValue* minimum (KeyValue* x) {
        if (x->left == nullptr) {
            return x;
        }
        return minimum(x->left);
    }

    KeyValue* takeOut(KeyValue * root, string z) {
        if (root == nullptr) return root;

        if (z < root->key) root->left = takeOut(root->left, z);

        else if (z > root->key) {
            root->right = takeOut(root->right, z);
        }

        else if (root->left != nullptr && root->right != nullptr) {
            root->key = minimum(root->right)->key;
            root->right = takeOut(root->right, root->key);
        }

        else {
            if (root->left != nullptr) root = root->left;
            else root = root -> right;
        }
        return root;
    }


    //оператор + и +=

    KeyValue* concat (KeyValue *first, KeyValue *second) {
        if (second != nullptr) {
            concat(first, second->left);
            concat(first, second->right);
            first = insert_node(first, *second);
        }
        return first;
    }

    KeyValue* operator+=(const AssociativeArray A) {
        AssociativeArray tmp(*this);
        return concat(tmp.root, A.root);
    }

    KeyValue* operator+(const AssociativeArray A) {
        AssociativeArray tmp(*this);
        return concat(tmp.root, A.root);
    }

    void operator = (KeyValue* R) {
       this->root = R;
       /*this->amount = A.amount;
       this->root = A.root;*/
    }


    KeyValue* insert_node(KeyValue * x, KeyValue y) {// x — корень поддерева, z — вставляемый ключ
        if (x == nullptr) {
            KeyValue *a = new KeyValue(y.key, y.value);
            return a;
        } // подвесим Node с key = z

        else if (y.key == x->key) {
            cout << "Key '" << y.key << "' is already taken.\n";
            return x;
        }

        else if (y.key < x->key) {
            x->left = insert_node(x->left, y);
        }

        else if (y.key > x->key) {
            x->right = insert_node(x->right, y);
        }
        return x;
    }
};
