#include <iostream>
#include <string>
#include <sstream>
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
    Stack<int> sContain;
    string strHauTo;
    int iExit;
    do {
        system("cls");
        cout << "Nhap bieu thuc hau to: ";
        getline(cin, strHauTo);
        stringstream ss(strHauTo);
        string strIndex;
        int iIndex;
        while (ss >> strIndex) {
            if (stringstream(strIndex) >> iIndex) {
                sContain.push(iIndex);
            }
            else {
                double iSecond = sContain.pop();
                double iFirst = sContain.pop();
                double dSum = 0;
                if (strIndex == "+") {
                    dSum = iFirst + iSecond;
                }
                else if (strIndex == "-") {
                    dSum = iFirst - iSecond;
                }
                else if(strIndex == "*") {
                    dSum = iFirst * iSecond;
                }
                else if(strIndex == "/") {
                    dSum = iFirst / iSecond;
                }
                else if (strIndex == "^") {
                    dSum = pow(iFirst, iSecond);
                }
                sContain.push(dSum);
            }
        }
        cout << "\nBieu thuc hau to la: " << sContain.pop();
        cout << "\nAn phim 1 de tiep tuc chuong trinh: ";
        cin >> iExit;
        cin.ignore();
    } while (iExit == 1);
}
