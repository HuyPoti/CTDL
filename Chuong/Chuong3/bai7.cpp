#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <chrono>
#include <thread>
using namespace std;

bool bCheckNhap = false;
class App;
class LinkedList;

class Node {
    friend class App;
    friend class LinkedList;
private:
    int _iHeSo;
    int _iMu;
    Node* _pNext;
public:
    Node(int, int);
    void xuat();
};

Node::Node(int iHeSo, int iMu) {
    _iHeSo = iHeSo;
    _iMu = iMu;
    _pNext = NULL;
}

void Node::xuat() {
    if (_iHeSo == 1) {
        if (_iMu == 1) {
            cout << "x";
        }
        else if (_iMu == 0) {
            cout << _iHeSo;
        }
        else {
            cout << "x^" << _iMu;
        }
    }
    else {
        if (_iMu == 1) {
            cout << _iHeSo << "x";
        }
        else if (_iMu == 0) {
            cout << _iHeSo;
        }
        else {
            cout << _iHeSo << "x^" << _iMu;
        }
    }

}

class LinkedList {
    friend class App;
private:
    Node* _pHead;
public:
    LinkedList();
    ~LinkedList();

    void nhap();
    void xuat();
    LinkedList daoHam();
    void giaTri(int);

    void clear();
};

LinkedList::LinkedList() {
    _pHead = NULL;
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::nhap() {
    string strInput, strIndex;
    getline(cin, strInput);
    stringstream ss(strInput);
    int iHeSo, iMu;
    Node* pLast = nullptr;
    while (ss >> strIndex) {
        if (stringstream(strIndex) >> iHeSo) {
            if (iHeSo == 0) continue;
            ss >> strIndex;
            if (stringstream(strIndex) >> iMu) {
                Node* p = new Node(iHeSo, iMu);
                if (_pHead == NULL) {
                    _pHead = p;
                }
                else {
                    pLast->_pNext = p;
                }
                pLast = p;
            }
        }
    }
    cout << "Da nhap xong, nhung cap he so va mu khong hop le se bi loai bo" << endl;
}

void LinkedList::xuat() {
    Node* p = _pHead;
    bool bCheckIndex1 = true;
    while (p != NULL) {
        if (bCheckIndex1) {
            p->xuat();
            bCheckIndex1 = false;
        }
        else {
            if (p->_iHeSo > 0) cout << "+";
            p->xuat();
        }
        p = p->_pNext;
    }
}

LinkedList LinkedList::daoHam() {
    LinkedList F;
    Node* p = _pHead;
    Node* pLast = nullptr;
    while (p != NULL) {
        if (p->_iMu != 0) {
            Node* pInput = new Node(p->_iHeSo * p->_iMu, p->_iMu - 1);
            if (F._pHead == NULL) {
                F._pHead = pInput;
            }
            else {
                pLast->_pNext = pInput;
            }
            pLast = pInput;
        }
        p = p->_pNext;
    }
    return F;
}

void LinkedList::giaTri(int iValue) {
    Node* p = _pHead;
    double iSum = 0;
    while (p != NULL) {
        iSum += p->_iHeSo * pow(iValue, p->_iMu);
        p = p->_pNext;
    }
    cout << iSum;
}

void LinkedList::clear() {
    while (_pHead != NULL) {
        Node* pTemp = _pHead;
        _pHead = _pHead->_pNext;
        delete pTemp;
    }
}

class App {
private:
    LinkedList F1, F2;
public:
    void createLinkedList();
    void printLinkedList();
    void derivative();
    void valueInX();
    void f3IsSumF1F2();
    void f3IsProductF1F2();
    void display();
};

void App::createLinkedList() {
    system("cls");
    bCheckNhap = true;
    F1.clear();
    F2.clear();
    cout << "Luu y nhap tat ca cac cap he so va so mu tren cung mot dong" << endl;
    cout << "Nhap danh sach lien ket F1: " << endl;
    F1.nhap();
    cout << "\nNhap danh sach lien ket F2: " << endl;
    F2.nhap();
    int iExit;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iExit;
    } while (iExit != 1);
    display();
}

void App::printLinkedList() {
    system("cls");
    cout << "Danh sach lien ket F1: ";
    F1.xuat();
    cout << endl;
    cout << "Danh sach lien ket F2: ";
    F2.xuat();
    cout << endl;
    int iExit;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iExit;
    } while (iExit != 1);
    display();
}

void App::derivative() {
    system("cls");
    cout << "Nhap da thuc ban muon dao ham (F1, F2)? : ";
    string strInput;
    cin >> strInput;
    cout << "Dao ham cua " << strInput << " la: ";
    if (strInput == "F1") {
        F1.daoHam().xuat();
    }
    else if (strInput == "F2") {
        F2.daoHam().xuat();
    }
    else cout << "Ban khong nhap dung ten danh sach";

    int iExit;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iExit;
    } while (iExit != 1);
    display();
}

void App::valueInX() {
    system("cls");
    int iExit;
    cout << "Nhap gia tri x: ";
    int iEle;
    cin >> iEle;
    cout << "\nNhap da thuc ban muon tinh gia tri (F1, F2)? : ";
    string strInput;
    cin >> strInput;
    cout << "Gia tri cua " << strInput << " theo " << iEle << " la: ";
    if (strInput == "F1") {
        F1.giaTri(iEle);
    }
    else if (strInput == "F2") {
        F2.giaTri(iEle);
    }
    else cout<<"Ban khong nhap dung ten danh sach";
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iExit;
    } while (iExit != 1);
    display();
}

void App::f3IsSumF1F2() {
    system("cls");
    Node* pF1 = F1._pHead;
    Node* pF2 = F2._pHead;
    LinkedList L;
    Node* pLast = NULL;
    Node* p = NULL;

    while (pF1 != NULL && pF2 != NULL) {
        if (pF1->_iMu > pF2->_iMu) {
            p = new Node(pF1->_iHeSo, pF1->_iMu);
            pF1 = pF1->_pNext;
        }
        else if (pF1->_iMu < pF2->_iMu) {
            p = new Node(pF2->_iHeSo, pF2->_iMu);
            pF2 = pF2->_pNext;
        }
        else {
            p = new Node(pF1->_iHeSo + pF2->_iHeSo, pF1->_iMu);
            pF1 = pF1->_pNext;
            pF2 = pF2->_pNext;
        }
        if (L._pHead == NULL) {
            L._pHead = p;
        }
        else {
            pLast->_pNext = p;
        }
        pLast = p;
    }

    while (pF1 != NULL) {
        p = new Node(pF1->_iHeSo, pF1->_iMu);
        pF1 = pF1->_pNext;
        if (L._pHead == NULL) {
            L._pHead = p;
        }
        else {
            pLast->_pNext = p;
        }
        pLast = p;
    }

    while (pF2 != NULL) {
        p = new Node(pF2->_iHeSo, pF2->_iMu);
        pF2 = pF2->_pNext;
        if (L._pHead == NULL) {
            L._pHead = p;
        }
        else {
            pLast->_pNext = p;
        }
        pLast = p;
    }
    cout << "Danh sach F3: ";
    L.xuat();
    int iExit;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iExit;
    } while (iExit != 1);
    display();
}


void App::f3IsProductF1F2() {
    system("cls");
    int iSize = F1._pHead->_iMu + F2._pHead->_iMu;
    int iLow = iSize;
    int* pArr = new int[iSize + 1]();

    for (Node* p = F1._pHead; p != NULL; p = p->_pNext) {
        for (Node* q = F2._pHead; q != NULL; q = q->_pNext) {
            int index = p->_iMu + q->_iMu;
            pArr[index] += p->_iHeSo * q->_iHeSo;
            if (index < iLow) {
                iLow = index;
            }
        }
    }

    LinkedList L;
    Node* pLast = NULL;

    for (int i = iSize; i >= iLow; i--) {
        if (pArr[i] != 0) {  // Chỉ thêm các phần tử không bằng 0
            Node* p = new Node(pArr[i], i);
            if (L._pHead == NULL) {
                L._pHead = p;
            }
            else {
                pLast->_pNext = p;
            }
            pLast = p;
        }
    }
    cout << "Danh sach F3: ";
    L.xuat();

    // Giải phóng bộ nhớ
    delete[] pArr;

    // Chờ người dùng thoát
    int iExit;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iExit;
    } while (iExit != 1);

    display();
}

void App::display() {
    system("cls");
    cout << "--------------------Bai7----------------------" << endl;
    cout << "a. Tao 2 danh sach lien ket F1 va F2" << endl;
    cout << "b. In 2 da thuc ra man hinh" << endl;
    cout << "c. Tinh dao ham cua da thuc" << endl;
    cout << "d. Tinh gia tri cua da thuc theo x" << endl;
    cout << "e. Tao danh sach F3 la tong cua 2 da thuc F1 va F2" << endl;
    cout << "f. Tao danh sach F3 la tich cua 2 da thuc F1 va F2" << endl;
    cout << "--------------------Bai7----------------------" << endl;
    cout << "Ban chon (a->f)? : ";
    char cChoice;
    cin >> cChoice;
    cin.ignore();
    if (cChoice < 'a' || cChoice > 'h') {
        cout << "\nBan nhap sai, vui long nhap lai";
        this_thread::sleep_for(chrono::seconds(1));
        display();
    }
    if (cChoice != 'a' && !bCheckNhap) {
        cout << "Danh sach dang rong!!!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        createLinkedList();
    }
    switch (cChoice) {
    case 'a':
        createLinkedList();
        break;
    case 'b':
        printLinkedList();
        break;
    case 'c':
        derivative();
        break;
    case 'd':
        valueInX();
        break;
    case 'e':
        f3IsSumF1F2();
        break;
    case 'f':
        f3IsProductF1F2();
        break;
    }
}

int main() {
    App a;
    a.display();
    return 0;
}
