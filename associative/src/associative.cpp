#include "associative.h"
#include "Exception.h"

/*  Спроектировать класс «Associative_array», который содержит массив пар ключ-значение строкового типа. Для элементов массива при необходимости можно разработать собственный класс. Для него определить: операцию добавления элемента «<<», операцию удаления элемента «>>», операцию доступа по ключу «[]» с возможностью присвоения, операцию объединения «+» двух массивов, ее же в сокращенной форме. При необходимости разрешается определять другие операции (например «=») и методы (например, getter, setter и прочее). Продемонстрировать каждую операцию. */

using namespace std;

KeyValue::KeyValue () {
    key = "";
    value = "";
    left = nullptr;
    right = nullptr;

}

KeyValue::KeyValue (string k, string v) {
    key = k;
    value = v;
    left = nullptr;
    right = nullptr;
}

void KeyValue::operator = (string k) {
    this->value = k;
}

AssociativeArray::AssociativeArray() {
    amount = 0;
    root = nullptr;
}


KeyValue* AssociativeArray::insert_string(KeyValue * x, string z) {// x — корень поддерева, z — вставляемый ключ
    try {
            if (x == nullptr) {
                KeyValue *a = new KeyValue(z, "");
                return a;
            } // подвесим Node с key = z

            else if (z == x->key) {
                throw Exception("Key is already taken!!!");
            }

            else if (z < x->key) {
                x->left = insert_string(x->left, z);
            }

            else if (z > x->key) {
                x->right = insert_string(x->right, z);
            }
    }
    catch (Exception& excection) {
		excection.show();
		return x;
	}

    return x;
}




void AssociativeArray::output(KeyValue * x) {
        if(!(x == nullptr)) {
            output(x->left);
            cout << x->key << " : " << x->value << endl;
            output(x->right);
        }
}

bool AssociativeArray::checkExist(KeyValue * x, string k) {
        if(!(x == nullptr)) {
            checkExist(x->left, k);
            if (x->key == k) {
                return true;
            }
            checkExist(x->right, k);
        }
        else {
            return false;
        }
}

    //оператор доступа []

KeyValue* AssociativeArray::search (KeyValue * x, string k) {

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

string& AssociativeArray::operator[] (string k) {
    return search(this->root, k)->value;
}

    void AssociativeArray::operator<< (string k) {
        this->root = insert_string(this->root, k);
    }

    void AssociativeArray::operator<< (KeyValue second) {
        this->root = insert_node(this->root, second);
    }

    void AssociativeArray::operator >> (string k) {
        this->root = takeOut(this->root, k);
    }

    KeyValue* AssociativeArray::minimum (KeyValue* x) {
        if (x->left == nullptr) {
            return x;
        }
        return minimum(x->left);
    }

    KeyValue* AssociativeArray::takeOut(KeyValue * root, string z) {
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

    KeyValue* AssociativeArray::concat (KeyValue *first, KeyValue *second) {
        if (second != nullptr) {
            concat(first, second->left);
            concat(first, second->right);
            first = insert_node(first, *second);
        }
        return first;
    }

    KeyValue* AssociativeArray::operator+=(const AssociativeArray A) {
        AssociativeArray tmp(*this);
        return concat(tmp.root, A.root);
    }

    KeyValue* AssociativeArray::operator+(const AssociativeArray A) {
        AssociativeArray tmp(*this);
        return concat(tmp.root, A.root);
    }

    void AssociativeArray::operator = (KeyValue* R) {
        this->root = R;
        /*this->amount = A.amount;
         this->root = A.root;*/
    }


    KeyValue* AssociativeArray::insert_node(KeyValue * x, KeyValue y) {// x — корень поддерева, z — вставляемый ключ

        try {
            if (x == nullptr) {
                KeyValue *a = new KeyValue(y.key, y.value);
                return a;
            } // подвесим Node с key = z

            else if (y.key == x->key) {
                throw Exception("Key is already taken!!!");
            }

            else if (y.key < x->key) {
                x->left = insert_node(x->left, y);
            }

            else if (y.key > x->key) {
                x->right = insert_node(x->right, y);
            }
        }
        catch (Exception& excection) {
            excection.show();
            return x;
        }

        return x;
    }
