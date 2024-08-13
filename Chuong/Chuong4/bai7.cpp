#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

bool bCheck = true;
enum DataType {
    INT,
    DOUBLE,
    STRING,
    CHAR
};

class MyData {
private:
    DataType type;
    union {
        int i;
        double d;
        char c;
    };
    string s;
public:
    MyData() : type(STRING), i(0) {}
    MyData(int value) : type(INT), i(value) {}
    MyData(double value) : type(DOUBLE), d(value) {}
    MyData(char value) : type(CHAR), c(value) {}
    MyData(const string& value) : type(STRING), s(value) {}
    MyData(const MyData& other);
    ~MyData();                   

    MyData& operator=(const MyData& other);

    friend istream& operator>>(istream& in, MyData& data);
    friend ostream& operator<<(ostream& out, MyData data);
};

MyData::MyData(const MyData& other) : type(other.type), s(other.s) {
    if (type == INT) {
        i = other.i;
    }
    else if (type == DOUBLE) {
        d = other.d;
    }
    else if (type == CHAR) {
        c = other.c;
    }
}

MyData::~MyData() {}

MyData& MyData::operator=(const MyData& other) {
    if (this != &other) {
        if (type == STRING) {
            s = string(); // Reset string trước khi gán
        }
        type = other.type;
        if (type == INT) {
            i = other.i;
        }
        else if (type == DOUBLE) {
            d = other.d;
        }
        else if (type == CHAR) {
            c = other.c;
        }
        else if (type == STRING) {
            s = other.s;
        }
    }
    return *this;
}

ostream& operator<<(ostream& out, MyData data) {
    if (data.type == INT) {
        cout << data.i << " ";
    }
    else if (data.type == DOUBLE) {
        cout << data.d << " ";
    }
    else if (data.type == CHAR) {
        cout << data.c << " ";
    }
    else if (data.type == STRING) {
        cout << data.s << " ";
    }
    return out;
}

istream& operator>>(istream& is, MyData& data) {
    string typeStr;
    is >> typeStr;
    bCheck = true;
    if (typeStr == "int") {
        data.type = INT;
        is >> data.i;
    }
    else if (typeStr == "double") {
        data.type = DOUBLE;
        is >> data.d;
    }
    else if (typeStr == "char") {
        data.type = CHAR;
        is >> data.c;
    }
    else if (typeStr == "string") {
        data.type = STRING;
        is.ignore(); // Bỏ qua ký tự newline còn lại
        getline(is, data.s); // Đọc chuỗi đầy đủ
    }
    else {
        cout << "Ban da nhap sai";
        bCheck = false;
    }
    return is;
}

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
    cout << _data ;
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

    void app();
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
        exit;
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
        exit;
    }
    return _pTop->_data;
}

template<class DataType>
void Stack<DataType>::display() {
    if (isEmpty()) {
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

template<class DataType>
void Stack<DataType>::app() {
    system("cls");
    cout << "Cac thao tac tren Stack" << endl;
    cout << "1. Kiem tra Stack rong" << endl;
    cout << "2. Them phan tu vao dinh Stack" << endl;
    cout << "3. Lay phan tu o dinh Stack" << endl;
    cout << "4. Xem gia tri phan tu o dinh Stack" << endl;
    cout << "5. Hien thi Stack" << endl;
    cout << "6. Huy bo Stack" << endl;
    cout << "0. Thoat chuong trinh" << endl;
    cout << "Ban chon thao tac nao (0->6)? : ";
    int iChoice;
    cin >> iChoice;
    int iExit;
    MyData data;
    switch (iChoice) {
    case 1:
        system("cls");
        if (isEmpty()) {
            cout << "Stack rong!";
        }
        else cout << "Stack khac rong!";
        do {
            cout << "\nAn phim 1 de thoat: ";
            cin >> iExit;
        } while (iExit != 1);
        app();
        break;
    case 2:
        system("cls");
        cout << "Nhap phan tu can them theo dang sau 'kiedulieu giatri', vi du: 'int 7': ";
        cin >> data;
        push(data);
        if (bCheck) cout << "\nDa them phan tu";
        do {
            cout << "\nAn phim 1 de thoat: ";
            cin >> iExit;
        } while (iExit != 1);
        app();
        break;
    case 3:
        system("cls");
        if (isEmpty()) {
            cout << "Stack rong!";
        }
        else {
            cout << "Phan tu o dinh stack duoc lay ra la " << pop();
        }
        do {
            cout << "\nAn phim 1 de thoat: ";
            cin >> iExit;
        } while (iExit != 1);
        app();
        break;
    case 4:
        system("cls");
        if (isEmpty()) {
            cout << "Stack rong!";
        }
        else {
            cout << "Gia tri phan tu o dinh stack la " << peek();
        }
        do {
            cout << "\nAn phim 1 de thoat: ";
            cin >> iExit;
        } while (iExit != 1);
        app();
        break;
    case 5:
        system("cls");
        display();
        do {
            cout << "\nAn phim 1 de thoat: ";
            cin >> iExit;
        } while (iExit != 1);
        app();
        break;
    case 6:
        system("cls");
        cout << "Da huy bo stack";
        clear();
        do {
            cout << "\nAn phim 1 de thoat: ";
            cin >> iExit;
        } while (iExit != 1);
        app();
        break;
    case 0:
        return;
    default:
        cout << "Ban nhap sai, vui long nhap lai";
        this_thread::sleep_for(chrono::seconds(1));
        app();
        break;
    }
}

int main() {
    Stack<MyData> s;
    s.app();
}

