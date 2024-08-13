#include <iostream>
#include <string>
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

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int main() {
    Stack<char> sToanTu;
    string strTrungTo;
    int iExit;
    do {
        system("cls");
        cout << "Nhap bieu thuc trung to: ";
        getline(cin, strTrungTo);
        string strHauTo;
        for (int i = 0; i < strTrungTo.length(); i++) {
            if (strTrungTo[i] == ' ') continue;

            if (isalnum(strTrungTo[i])) {
                strHauTo += strTrungTo[i];
            }
            else if (strTrungTo[i] == '(') {
                sToanTu.push(strTrungTo[i]);
            }
            else if (strTrungTo[i] == ')') {
                strHauTo += " ";
                while (!sToanTu.isEmpty() && sToanTu.peek() != '(') {
                    strHauTo += sToanTu.pop();
                    strHauTo += " ";
                }
                if (!sToanTu.isEmpty() && sToanTu.peek() == '(') {
                    sToanTu.pop();
                }
            }
            else if (isOperator(strTrungTo[i])) {
                strHauTo += " ";
                while (!sToanTu.isEmpty() && precedence(sToanTu.peek()) >= precedence(strTrungTo[i])) {
                    strHauTo += sToanTu.pop();
                    strHauTo += " ";
                }
                sToanTu.push(strTrungTo[i]);
            }
        }
        while (!sToanTu.isEmpty()) {
            strHauTo += sToanTu.pop();
            strHauTo += " ";
        }
        cout << "\nBieu thuc hau to la: " << strHauTo;
        cout << "\nAn phim 1 de tiep tuc chuong trinh: ";
        cin >> iExit;
        cin.ignore();
    } while (iExit == 1);
}
