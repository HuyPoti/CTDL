#include <iostream>
#include <thread>
#include <chrono>
#include <string>
using namespace std;

class A;
class B;
class C;

class NodeA {
    friend A;
private:
    int _iSoGhe;
    NodeA* _pNext;
public:
    NodeA(int);
    void display();
};

NodeA::NodeA(int iSoGhe) {
    _iSoGhe = iSoGhe;
    _pNext = nullptr;
}

void NodeA::display() {
    cout << _iSoGhe << " ";
}

class A {
private:
    NodeA* _pHead;
public:
    A();
    ~A();
    bool isEmpty();
    NodeA* search(int);
    void loaiNode(int);
    void addNodeIsDeleted(int);
    void display();
};

A::A() : _pHead(nullptr) {
    NodeA* pTemp = nullptr;
    for (int i = 1; i <= 100; i++) {
        NodeA* p = new NodeA(i);
        if (_pHead == nullptr) {
            _pHead = p;
        }
        else {
            pTemp->_pNext = p;
        }
        pTemp = p;
    }
}

A::~A() {
    NodeA* pTemp;
    while (_pHead != nullptr) {
        pTemp = _pHead;
        _pHead = pTemp->_pNext;
        delete pTemp;
    }
}

bool A::isEmpty() {
    return (_pHead == nullptr);
}

NodeA* A::search(int iSoGhe) {
    NodeA* p = _pHead;
    while (p != nullptr) {
        if (p->_iSoGhe == iSoGhe) break;
        p = p->_pNext;
    }
    return p;
}

void A::loaiNode(int iSoGhe) {
    NodeA* p = _pHead;
    if (p == nullptr) return;

    if (p->_iSoGhe == iSoGhe) {
        _pHead = p->_pNext;
        delete p;
        return;
    }

    NodeA* pSearch = search(iSoGhe);
    while (p->_pNext != pSearch && p->_pNext != nullptr) {
        p = p->_pNext;
    }
    if (p->_pNext != nullptr) {
        p->_pNext = pSearch->_pNext;
        delete pSearch;
    }
}

void A::addNodeIsDeleted(int iSoGhe) {
    NodeA* pTemp = new NodeA(iSoGhe);

    if (_pHead == nullptr || _pHead->_iSoGhe > iSoGhe) {
        pTemp->_pNext = _pHead;
        _pHead = pTemp;
    }
    else {
        NodeA* p = _pHead;
        while (p->_pNext != nullptr && p->_pNext->_iSoGhe < iSoGhe) {
            p = p->_pNext;
        }
        pTemp->_pNext = p->_pNext;
        p->_pNext = pTemp;
    }
}

void A::display() {
    NodeA* p = _pHead;
    for (int i = 1; i <= 100; i++) {
        if (p->_iSoGhe == i) {
            cout << i << " ";
            p = p->_pNext;
        }
        else {
            cout << "-1 ";
        }
        if (i % 10 == 0)    cout << endl;
    }
}

class NodeB {
    friend B;
private:
    int _iStt;
    NodeB* _pNext;
public:
    NodeB(int);
    void display();
};

NodeB::NodeB(int data) {
    _iStt = data;
    _pNext = nullptr;
}

void NodeB::display() {
    cout << _iStt;
}

class B {
    friend A;
    friend C;
private:
    NodeB* _pFront;
    NodeB* _pRear;
    int _iSize;
public:
    B();
    ~B();

    void laySo();
    int getSize();
    bool coKhach();
    void deleteNode();
};

B::B() {
    NodeB* p = new NodeB(1);
    _pFront = _pRear = p;
    _iSize = 1;
}

B::~B() {
    NodeB* pTemp;
    while (_pFront != nullptr) {
        pTemp = _pFront;
        _pFront = pTemp->_pNext;
        delete pTemp;
    }
    _iSize = 0;
    _pRear = nullptr;
}

void B::laySo() {
    NodeB* p = new NodeB(_pRear->_iStt + 1);
    _pRear->_pNext = p;
    _pRear = p;
    _iSize++;
}

int B::getSize() {
    return _iSize;
}

bool B::coKhach() {
    return (_pFront!=_pRear);
}

void B::deleteNode() {
    NodeB* pTemp = _pFront;
    _pFront = _pFront->_pNext;
    delete pTemp;
}

class NodeC {
    friend C;
private:
    int _iSoGhe;
    string _strTen;
    NodeC* _pNext;
public:
    NodeC(int, string);
    void display();
};

NodeC::NodeC(int iSoGhe, string strTen) {
    _iSoGhe = iSoGhe;
    _strTen = strTen;
    _pNext = nullptr;
}

void NodeC::display() {
    cout << "So ghe: " << _iSoGhe << endl;
    cout << "Ten khach hang da mua: " << _strTen << endl;
}

class C {
    friend A;
private:
    NodeC* _pHead;
public:
    C();
    ~C();

    void huyVe(int);
    void hienThi();
    bool isEmpty();
    void addNode(NodeC*);
    NodeC* search(int);
};

C::C() : _pHead(nullptr) {}

C::~C() {
    NodeC* pTemp;
    while (_pHead != nullptr) {
        pTemp = _pHead;
        _pHead = pTemp->_pNext;
        delete pTemp;
    }
}

void C::huyVe(int iSoGhe) {
    NodeC* p = _pHead;
    if (p == nullptr) return;

    if (p->_iSoGhe == iSoGhe) {
        _pHead = p->_pNext;
        delete p;
        return;
    }

    NodeC* pSearch = search(iSoGhe);
    while (p->_pNext != pSearch && p->_pNext != nullptr) {
        p = p->_pNext;
    }
    if (p->_pNext != nullptr) {
        p->_pNext = pSearch->_pNext;
        delete pSearch;
    }
}

void C::hienThi() {
    NodeC* p = _pHead;
    while (p != nullptr) {
        p->display();
        p = p->_pNext;
    }
}

bool C::isEmpty() {
    return (_pHead == nullptr);
}

void C::addNode(NodeC* p) {
    if (isEmpty()) {
        _pHead = p;
    }
    else {
        NodeC* pTemp = _pHead;
        while (pTemp->_pNext != nullptr) {
            pTemp = pTemp->_pNext;
        }
        pTemp->_pNext = p;
    }
}

NodeC* C::search(int iSoGhe) {
    NodeC* p = _pHead;
    while (p != nullptr) {
        if (p->_iSoGhe == iSoGhe) break;
        p = p->_pNext;
    }
    return p;
}

class App {
    friend A;
    friend B;
    friend C;
private:
    A _a;
    B _b;
    C _c;
public:
    void display();
    void thoat();
};

void App::display() {
    system("cls");
    cout << "-----------Rap chieu phim 'Vao la Me'----------" << endl;
    cout << "1. Lay so xep hang" << endl;
    cout << "2. Mua ve" << endl;
    cout << "3. Huy ve" << endl;
    cout << "4. Hien thi thong tin ve da ban" << endl;
    cout << "5. Ra ve (Thoat)" << endl;
    cout << "Ban chon (1->5)? : ";
    int iChoice;
    cin >> iChoice;
    system("cls");
    switch (iChoice) {
    case 1:
        _b.laySo();
        cout << "So thu tu cua ban la: " << _b.getSize();
        thoat();
        break;
    case 2:
        if (!_a.isEmpty() && _b.coKhach()) {
            _b.deleteNode();
            int iSoGhe;
            string strTen;
            cout << "Cac ghe con lai trong rap (-1 nghia la da ban): " << endl;
            _a.display();
            cout << "\nNhap so ghe ban mua: ";
            cin >> iSoGhe;
            while (_a.search(iSoGhe) == nullptr) {
                cout << "\nGhe ban dinh mua da co nguoi mua roi, vui long chon ghe khac: ";
                cin >> iSoGhe;
            }
            cout << "Nhap ho ten cua ban: ";
            cin.ignore();
            getline(cin, strTen);
            NodeC* p = new NodeC(iSoGhe, strTen);
            _c.addNode(p);
            _a.loaiNode(iSoGhe);
        }
        else {
            cout << "Da het ghe hoac la ban chua lay so";
        }
        thoat();
        break;
    case 3:
        if (_c.isEmpty()) {
            cout << "Khong co ve nao duoc ban";
        }
        else {
            int iSoGhe;
            cout << "Nhap so ghe ma ban da dat de huy ve: ";
            cin >> iSoGhe;
            if (_c.search(iSoGhe) == nullptr)   cout << "Khong co ve dat tai so ghe " << iSoGhe;
            else {
                cout << "Ban co chac huy ve (yes/no)? : ";
                string strHuy;
                cin >> strHuy;
                if (strHuy == "yes") {
                    _c.huyVe(iSoGhe);
                    _a.addNodeIsDeleted(iSoGhe);
                    cout << "Da huy ve";
                }

            }
        }
        thoat();
        break;
    case 4:
        if (_c.isEmpty()) {
            cout << "Chua ban duoc ve nao!";
        }
        else {
            cout << "Minh hoa ghe chua ban: " << endl;
            _a.display();
            cout << endl;
            cout << "Ca ve da ban la: " << endl;
            _c.hienThi();
        }
        thoat();
        break;
    case 5:
        cout << "Thoat chuong trinh";
        return;
    default:
        cout << "Ban nhap sai, vui long nhap lai";
        this_thread::sleep_for(chrono::seconds(1));
        display();
        break;
    }
}

void App::thoat() {
    int iExit;
    do {
        cout << "\nAn phim 1 de ket thuc: ";
        cin >> iExit;
    } while (iExit != 1);
    display();
}

int main() {
    App a;
    a.display();
    return 0;
}
