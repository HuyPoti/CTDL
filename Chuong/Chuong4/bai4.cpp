#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

template<class DataType>
class Stack;

template<class DataType>
class Node {
    friend Stack<DataType>;
private:
    DataType _data;
    Node* _pNext;
public:
    Node(DataType data);
    void display();
};

template<class DataType>
Node<DataType>::Node(DataType data) {
    _data = data;
    _pNext = NULL;
}

template<class DataType>
void Node<DataType>::display() {
    cout << _data << endl;
}

template<class DataType>
class Stack {
private:
    Node<DataType>* _pTop;
    int _iSize;
public:
    Stack();
    ~Stack();

    bool isEmpty();
    void push(DataType data);
    DataType pop();
    DataType peek();
    void display();
    void clear();
    int getSize();
};

template<class DataType>
Stack<DataType>::Stack() {
    _pTop = NULL;
    _iSize = 0;
}

template<class DataType>
Stack<DataType>::~Stack() {
    clear();
}

template<class DataType>
bool Stack<DataType>::isEmpty() {
    return (_pTop == NULL);
}

template<class DataType>
void Stack<DataType>::push(DataType data) {
    Node<DataType>* pTemp = new Node<DataType>(data);
    pTemp->_pNext = _pTop;
    _pTop = pTemp;
    _iSize++;
}

template<class DataType>
DataType Stack<DataType>::pop() {
    if (isEmpty()) {
        exit(1); // Chỉnh sửa cú pháp thoát
    }
    Node<DataType>* pTemp = _pTop;
    DataType temp = pTemp->_data;
    _pTop = pTemp->_pNext;
    delete pTemp;
    _iSize--;
    return temp;
}

template<class DataType>
DataType Stack<DataType>::peek() {
    if (isEmpty()) {
        exit(1); // Chỉnh sửa cú pháp thoát
    }
    return _pTop->_data;
}

template<class DataType>
void Stack<DataType>::display() {
    if (isEmpty()) {
        cout << "Stack is empty." << endl;
    }
    else {
        for (Node<DataType>* p = _pTop; p != NULL; p = p->_pNext) {
            p->display();
        }
    }
}

template<class DataType>
void Stack<DataType>::clear() {
    Node<DataType>* pTemp;
    while (_pTop != NULL) {
        pTemp = _pTop;
        _pTop = pTemp->_pNext;
        delete pTemp;
    }
    _iSize = 0;
}

template<class DataType>
int Stack<DataType>::getSize() {
    return _iSize;
}

int main() {
    int iExit;
    do {
        Stack<int> s;
        system("cls");  // Chỉ dùng trên Windows
        vector<int> v;
        cout << "Nhap day can sap xep: ";
        string strInput;
        getline(cin, strInput);
        stringstream ss(strInput);
        int iInput;
        while (ss >> iInput) {
            v.push_back(iInput);
        }
        s.push(0);
        s.push(v.size() - 1);
        while (!s.isEmpty()) {
            int j = s.pop();
            int i = s.pop();
            int iLeft = i, iRight = j;
            int iX = v[(i + j) / 2];
            while (i < j) {
                while (v[i] < iX) i++;
                while (v[j] > iX) j--;
                if (i <= j) {
                    swap(v[i], v[j]);
                    i++; j--;
                }
            }
            if (iLeft < j) {
                s.push(iLeft);
                s.push(j);
            }
            if (i < iRight) {
                s.push(i);
                s.push(iRight);
            }
        }
        for (int i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
        }
        cout << "\nAn phim 1 de tiep tuc chuong trinh: ";
        cin >> iExit;
        cin.ignore();
    } while (iExit == 1);
}
