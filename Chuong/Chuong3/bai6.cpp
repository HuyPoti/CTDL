#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

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
    MyData(const MyData& other);  // Copy constructor
    ~MyData();                   // Destructor

    MyData& operator=(const MyData& other); // Assignment operator

    void display() const;

    // Toán tử so sánh
    bool operator<(const MyData& other) const;
    bool operator>(const MyData& other) const;
    bool operator==(const MyData& other) const;

    friend istream& operator>>(istream& in, MyData& data);
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

MyData::~MyData() {
    // Không cần phải gọi destructor của string
}

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

void MyData::display() const {
    if (type == INT) {
        cout << i << " ";
    }
    else if (type == DOUBLE) {
        cout << d << " ";
    }
    else if (type == CHAR) {
        cout << c << " ";
    }
    else if (type == STRING) {
        cout << s << " ";
    }
}

bool MyData::operator<(const MyData& other) const {
    if (type != other.type) return type < other.type;
    if (type == INT) return i < other.i;
    if (type == DOUBLE) return d < other.d;
    if (type == CHAR) return c < other.c;
    if (type == STRING) return s < other.s;
    return false;
}

bool MyData::operator>(const MyData& other) const {
    if (type != other.type) return type > other.type;
    if (type == INT) return i > other.i;
    if (type == DOUBLE) return d > other.d;
    if (type == CHAR) return c > other.c;
    if (type == STRING) return s > other.s;
    return false;
}

bool MyData::operator==(const MyData& other) const {
    if (type != other.type) return false;
    if (type == INT) return i == other.i;
    if (type == DOUBLE) return d == other.d;
    if (type == CHAR) return c == other.c;
    if (type == STRING) return s == other.s;
    return false;
}

istream& operator>>(istream& is, MyData& data) {
    string typeStr;
    is >> typeStr;
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
        throw invalid_argument("Invalid data type");
    }
    return is;
}

template<class DataType>
class LinkedList;

template<class DataType>
class Node {
    friend class LinkedList<DataType>;
private:
    DataType _data;
    Node* _pNext;
public:
    Node(DataType);
    void display();
};

template<class DataType>
Node<DataType>::Node(DataType value) : _data(value), _pNext(nullptr) {}

template<class DataType>
void Node<DataType>::display() {
    _data.display();
}

template<class DataType>
class LinkedList {
private:
    Node<DataType>* _pHead;
    Node<DataType>* _pTail;
    int _iSize;
public:
    LinkedList() : _pHead(nullptr), _pTail(nullptr), _iSize(0) {};
    ~LinkedList() { clear(); };
    void addHead(DataType);
    void addTail(DataType);
    void addAfter(Node<DataType>*, DataType);
    Node<DataType>* search(DataType);
    Node<DataType>* searchPre(Node<DataType>*);
    void remove(DataType);
    void removeHead();
    void removeTail();
    void removeAfter(Node<DataType>*);
    void selectionSort();
    int getSize();
    void display();
    void clear();
    void app();
};

template<class DataType>
void LinkedList<DataType>::addHead(DataType value) {
    Node<DataType>* pAdd = new Node<DataType>(value);
    if (_pHead == nullptr) {
        _pHead = _pTail = pAdd;
    }
    else {
        pAdd->_pNext = _pHead;
        _pHead = pAdd;
    }
    _iSize++;
}

template<class DataType>
void LinkedList<DataType>::addTail(DataType value) {
    Node<DataType>* pAdd = new Node<DataType>(value);
    if (_pHead == nullptr) {
        _pHead = _pTail = pAdd;
    }
    else {
        _pTail->_pNext = pAdd;
        _pTail = pAdd;
    }
    _iSize++;
}

template<class DataType>
void LinkedList<DataType>::addAfter(Node<DataType>* node, DataType value) {
    Node<DataType>* pAdd = new Node<DataType>(value);
    if (_pHead != nullptr) {
        pAdd->_pNext = node->_pNext;
        node->_pNext = pAdd;
        if (node == _pTail) {
            _pTail = pAdd;
        }
    }
    else {
        addHead(value);
    }
    _iSize++;
}

template<class DataType>
Node<DataType>* LinkedList<DataType>::search(DataType data) {
    Node<DataType>* p = _pHead;
    while (p != nullptr && !(p->_data == data)) {
        p = p->_pNext;
    }
    return p;
}

template<class DataType>
Node<DataType>* LinkedList<DataType>::searchPre(Node<DataType>* node) {
    Node<DataType>* p = _pHead;
    if (p == node) return nullptr;
    while (p != nullptr && p->_pNext != node) {
        p = p->_pNext;
    }
    return p;
}

template<class DataType>
void LinkedList<DataType>::remove(DataType data) {
    Node<DataType>* pWalker = _pHead, * pTemp = nullptr;
    while (pWalker != nullptr && !(pWalker->_data == data)) {
        pTemp = pWalker;
        pWalker = pWalker->_pNext;
    }
    if (pWalker == nullptr) return;
    if (pTemp != nullptr) {
        if (pWalker == _pTail) {
            _pTail = pTemp;
            _pTail->_pNext = nullptr;
        }
        pTemp->_pNext = pWalker->_pNext;
        delete pWalker;
        _iSize--;
    }
}

template<class DataType>
void LinkedList<DataType>::removeHead() {
    if (_pHead != nullptr) {
        Node<DataType>* pTemp = _pHead;
        _pHead = _pHead->_pNext;
        delete pTemp;
        if (_pHead == nullptr) {
            _pTail = nullptr;
        }
        _iSize--;
    }
}

template<class DataType>
void LinkedList<DataType>::removeTail() {
    if (_pHead != nullptr) {
        Node<DataType>* pTemp = _pTail;
        _pTail = searchPre(_pTail);
        delete pTemp;
        if (_pTail == nullptr) {
            _pHead = nullptr;
        }
        else {
            _pTail->_pNext = nullptr;
        }
        _iSize--;
    }
}

template<class DataType>
void LinkedList<DataType>::removeAfter(Node<DataType>* node) {
    Node<DataType>* pTemp;
    if (node != nullptr) {
        pTemp = node->_pNext;
        if (pTemp != nullptr) {
            if (pTemp == _pTail) {
                _pTail = node;
            }
            node->_pNext = pTemp->_pNext;
            delete pTemp;
        }
    }
    else {
        removeHead();
    }
    _iSize--;
}

template<class DataType>
void LinkedList<DataType>::selectionSort() {
    Node<DataType>* p, * q;
    Node<DataType>* pMin;
    for (p = _pHead; p != nullptr && p->_pNext != nullptr; p = p->_pNext) {
        pMin = p;
        for (q = p->_pNext; q != nullptr; q = q->_pNext) {
            if (pMin->_data > q->_data) pMin = q;
        }
        swap(pMin->_data, p->_data);
    }
}

template<class DataType>
int LinkedList<DataType>::getSize() {
    return _iSize;
}

template<class DataType>
void LinkedList<DataType>::display() {
    Node<DataType>* pWalker = _pHead;
    while (pWalker != nullptr) {
        pWalker->display();
        pWalker = pWalker->_pNext;
    }
    cout << endl;
}

template<class DataType>
void LinkedList<DataType>::clear() {
    while (_pHead != nullptr) removeHead();
}

template<class DataType>
void LinkedList<DataType>::app() {
    system("cls");
    cout << "Cac thao tac co ban: " << endl;
    cout << "1. Ham addHead" << endl;
    cout << "2. Ham addTail" << endl;
    cout << "3. Ham addAfter" << endl;
    cout << "4. Ham search" << endl;
    cout << "5. Ham searchPre" << endl;
    cout << "6. Ham remove" << endl;
    cout << "7. Ham removeHead" << endl;
    cout << "8. Ham removeTail" << endl;
    cout << "9. Ham removeAfter" << endl;
    cout << "10. Ham selectionSort" << endl;
    cout << "11. Ham getSize" << endl;
    cout << "12. Ham display" << endl;
    cout << "13. Ham clear" << endl;
    cout << "Ban chon (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13)? : ";
    int iChoice;
    cin >> iChoice;
    system("cls");

    MyData input;
    Node<DataType>* p = nullptr;
    MyData before;


    switch (iChoice) {
    case 1:
        cout << "Huong dan cach nhap: 'int 5' nghia la kieu int voi dau vao la 5" << endl;
        cout << "Nhap 1 phan tu vao dau danh sach (kieu int, double, char, string): ";
        cin >> input;
        addHead(input);
        cout << "Da them phan tu" << endl;
        break;
    case 2:
        cout << "Huong dan cach nhap: 'int 5' nghia la kieu int voi dau vao la 5" << endl;
        cout << "Nhap 1 phan tu vao cuoi danh sach (kieu int, double, char, string): ";
        cin >> input;
        addTail(input);
        cout << "Da them phan tu" << endl;
        break;
    case 3:
        cout << "Huong dan cach nhap: 'int 5' nghia la kieu int voi dau vao la 5" << endl;
        cout << "Nhap 1 phan tu can chen vao danh sach (kieu int, double, char, string): ";
        cin >> input;
        cout << "Nhap phan tu dung sau no: ";
        cin >> before;
        p = search(before);
        if (p != nullptr) {
            addAfter(p, input);
            cout << "Da them phan tu" << endl;
        }
        else {
            cout << "Khong tim thay phan tu de chen sau" << endl;
        }
        break;
    case 4:
        cout << "Huong dan cach nhap: 'int 5' nghia la kieu int voi dau vao la 5" << endl;
        cout << "Nhap phan tu can tim kiem: ";
        cin >> input;
        p = search(input);
        if (p != nullptr) {
            cout << "Da tim thay phan tu: ";
            p->display();
            cout << endl;
        }
        else {
            cout << "Khong tim thay" << endl;
        }
        break;
    case 5:
        cout << "Huong dan cach nhap: 'int 5' nghia la kieu int voi dau vao la 5" << endl;
        cout << "Nhap phan tu sau phan tu muon tim kiem: ";
        cin >> input;
        Node<DataType>* pTemp;
        pTemp = search(input);
        if (pTemp == NULL) {
            cout << "Khong tim thay phan tu ban vua nhap nen khong the tiep tuc" << endl;
            break;
        }
        p = searchPre(pTemp);
        if (p != nullptr) {
            cout << "Da tim thay phan tu truoc phan tu vua nhap, do la phan tu co gia tri la: ";
            p->display();
            cout << endl;
        }
        else {
            cout << "Khong tim thay" << endl;
        }
        break;
    case 6:
        cout << "Huong dan cach nhap: 'int 5' nghia la kieu int voi dau vao la 5" << endl;
        cout << "Nhap gia tri can xoa: ";
        cin >> input;
        if (search(input) != nullptr) {
            remove(input);
            cout << "Da xoa phan tu" << endl;
        }
        else {
            cout << "Khong ton tai gia tri do" << endl;
        }
        break;
    case 7:
        if (_pHead != nullptr) {
            removeHead();
            cout << "Da xoa phan tu dau" << endl;
        }
        else {
            cout << "Danh sach khong con phan tu de xoa" << endl;
        }
        break;
    case 8:
        if (_pHead != nullptr) {
            removeTail();
            cout << "Da xoa phan tu cuoi" << endl;
        }
        else {
            cout << "Danh sach khong con phan tu de xoa" << endl;
        }
        break;
    case 9:
        cout << "Huong dan cach nhap: 'int 5' nghia la kieu int voi dau vao la 5" << endl;
        cout << "Nhap phan tu ma ban muon xoa phan tu dung sau no: ";
        cin >> input;
        if (_pHead != nullptr) {
            p = search(input);
            if (p == NULL) {
                cout << "Khong tim thay phan tu ban vua nhap nen khong the tiep tuc" << endl;
            }
            else if (p == _pTail) {
                cout << "Vi phan tu ban nhap la phan tu cuoi cho nen se phai quay vong xoa phan tu dau" << endl;
                removeHead();
            }
            else {
                removeAfter(p);
                cout << "Da xoa phan tu" << endl;
            }
        }
        else {
            cout << "Danh sach khong con phan tu de xoa" << endl;
        }
        break;
    case 10:
        selectionSort();
        cout << "Da sap xep xong" << endl;
        break;
    case 11:
        cout << "So phan tu dang co trong danh sach: " << getSize() << endl;
        break;
    case 12:
        if (_pHead == NULL) {
            cout << "Danh sach dang rong" << endl;
            break;
        }
        cout << "Cac phan tu cua danh sach: " << endl;
        display();
        break;
    case 13:
        clear();
        cout << "Da xoa danh sach" << endl;
        break;
    default:
        cout << "Lua chon khong hop le" << endl;
        break;
    }

    int iEnd;
    do {
        cout << "An phim 1 de quay ve menu: ";
        cin >> iEnd;
    } while (iEnd != 1);
    app();
}

int main() {
    LinkedList<MyData> L;
    L.app();
}
