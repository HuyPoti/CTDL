#include <iostream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;

template<class DataType>
class App;

template<class DataType>
class LinkedList;

template<class DataType>
class Node {
    friend class LinkedList<DataType>;
    friend class App<DataType>;
private:
    DataType _data;
    Node* _pNext;
public:
    Node(DataType value);
    void xuat();
};

template<class DataType>
Node<DataType>::Node(DataType data) {
    _data = data;
    _pNext = NULL;
}

template<class DataType>
void Node<DataType>::xuat() {
    cout << _data;
}

template<class DataType>
class LinkedList {
    friend class App<DataType>;
public:
    // Các thao tác chính
    LinkedList();
    ~LinkedList();
    void addHead(DataType);
    void addTail(DataType);
    void addAfter(Node<DataType>*, DataType);
    Node<DataType>* search(DataType);
    Node<DataType>* searchPre(Node<DataType>*);
    void removeHead();
    void removeTail();
    void removeAfter(Node<DataType>*);
    void remove(DataType);
    void xuat();
    void clear();

private:
    Node<DataType>* _pHead;
    Node<DataType>* _pTail;
    int _iSize;
};

template<class DataType>
LinkedList<DataType>::LinkedList() {
    _pHead = NULL;
    _pTail = NULL;
    _iSize = 0;
}

template<class DataType>
LinkedList<DataType>::~LinkedList() {
    clear();
}

template<class DataType>
void LinkedList<DataType>::addHead(DataType data) {
    Node<DataType>* pAdd = new Node<DataType>(data);
    if (_pHead == NULL) {
        _pHead = _pTail = pAdd;
    }
    else {
        pAdd->_pNext = _pHead;
        _pHead = pAdd;
    }
    _iSize++;
}

template<class DataType>
void LinkedList<DataType>::addTail(DataType data) {
    Node<DataType>* pAdd = new Node<DataType>(data);
    if (_pHead == NULL) {
        _pHead = _pTail = pAdd;
    }
    else {
        _pTail->_pNext = pAdd;
        _pTail = pAdd;
    }
    _iSize++;
}

template<class DataType>
void LinkedList<DataType>::addAfter(Node<DataType>* node, DataType data) {
    Node<DataType>* pAdd = new Node<DataType>(data);
    if (node != NULL) {
        pAdd->_pNext = node->_pNext;
        node->_pNext = pAdd;
        if (node == _pTail) {
            _pTail = pAdd;
        }
    }
    else {
        addHead(data);
    }
    _iSize++;
}

template<class DataType>
Node<DataType>* LinkedList<DataType>::search(DataType data) {
    Node<DataType>* pSe = _pHead;
    while ((pSe != NULL) && (pSe->_data != data)) {
        pSe = pSe->_pNext;
    }
    return pSe;
}

template<class DataType>
Node<DataType>* LinkedList<DataType>::searchPre(Node<DataType>* node) {
    Node<DataType>* pSe = _pHead;
    if (pSe == node) {
        return NULL;
    }
    while ((pSe != NULL) && (pSe->_pNext != node)) {
        pSe = pSe->_pNext;
    }
    return pSe;
}

template<class DataType>
void LinkedList<DataType>::removeHead() {
    if (_pHead != NULL) {
        Node<DataType>* pRe = _pHead;
        _pHead = _pHead->_pNext;
        delete pRe;
        if (_pHead == NULL) {
            _pTail = NULL;
        }
        _iSize--;
    }
}

template<class DataType>
void LinkedList<DataType>::removeTail() {
    if (_pHead != NULL) {
        Node<DataType>* pRe = _pTail;
        _pTail = searchPre(_pTail);
        delete pRe;
        if (_pTail == NULL) {
            _pHead = NULL;
        }
        else {
            _pTail->_pNext = NULL;
        }
        _iSize--;
    }
}

template<class DataType>
void LinkedList<DataType>::removeAfter(Node<DataType>* node) {
    Node<DataType>* pTemp;
    if (node != NULL) {
        pTemp = node->_pNext;
        if (pTemp != NULL) {
            if (pTemp == _pTail)
                _pTail = node;
            node->_pNext = pTemp->_pNext;
            delete pTemp;
        }
    }
    else {
        removeHead();
    }
}

template<class DataType>
void LinkedList<DataType>::remove(DataType data) {
    Node<DataType>* pWalker = _pHead;
    Node<DataType>* pPrev = NULL;

    while (pWalker != NULL && pWalker->_data != data) {
        pPrev = pWalker;
        pWalker = pWalker->_pNext;
    }

    if (pWalker == NULL) return;

    if (pPrev != NULL) {
        pPrev->_pNext = pWalker->_pNext;
        if (pWalker == _pTail) {
            _pTail = pPrev;
        }
    }
    else {
        _pHead = pWalker->_pNext;
        if (_pHead == NULL) {
            _pTail = NULL;
        }
    }

    delete pWalker;
    _iSize--;
}

template<class DataType>
void LinkedList<DataType>::xuat() {
    Node<DataType>* pWalker = _pHead;
    while (pWalker != NULL) {
        pWalker->xuat();
        cout << " ";
        pWalker = pWalker->_pNext;
    }
}

template<class DataType>
void LinkedList<DataType>::clear() {
    while (_pHead != NULL) {
        removeHead();
    }
}

template<class DataType>
class App {
private:
    LinkedList<DataType> L1, L2;
public:
    App() {};
    ~App() {
        L1.clear();
        L2.clear();
    }
    void nhap();
    void display();
    LinkedList<DataType> noiDanhSach_a();
    LinkedList<DataType> hieuDanhSach_b();
    LinkedList<DataType> giaoDanhSach_c();
    LinkedList<DataType> hopDanhSach_d();
    LinkedList<DataType> ee();
    bool trungGiaTri_f();
    void xoaDau_g();
    void xoaHetEqualMax_h();
};

template<class DataType>
void App<DataType>::nhap() {
    int iSize;
    cout << "Nhap L1: ";
    string strInput;
    getline(cin, strInput);
    stringstream ss1(strInput);
    string strTemp;
    DataType Temp;

    while (ss1 >> strTemp) {
        if (stringstream(strTemp) >> Temp) {
            L1.addTail(Temp);
        }
    }
    cout << "Nhap L2: ";
    getline(cin, strInput);
    stringstream ss2(strInput);
    while (ss2 >> strTemp) {
        if (stringstream(strTemp) >> Temp) {
            L2.addTail(Temp);
        }
    }
    L1.xuat();
    cout << endl;
    L2.xuat();
    cout << endl;
    int iInput;
    do {
        cout << "Nhap phim 1 de quay ve menu: ";
        cin >> iInput;
    } while (iInput != 1);
    display();
}

template<class DataType>
void App<DataType>::display() {
    system("cls");
    cout << "a. Tao danh sach L3 bang cach noi L1 vao sau L2" << endl;
    cout << "b. Tao danh sach L3 bao gom cac phan tu chi co trong L1 ma khong co trong L2 (L3 la hieu cua L1 va L2)" << endl;
    cout << "c. Tao danh sach L3 bao gom cac phan tu vua co trong L1 vua co trong L2 (L3 la giao cua L1 va L2)" << endl;
    cout << "d. Tao danh sach L3 bao gom cac phan tu hoac co trong L1 hoac co trong L2 (L3 la hop cua L1 va L2) " << endl;
    cout << "e. Tao danh sach tong L3 co do dai lon nhat giua L1 va L2 va gia tri bang tong cua cac phan tu tuong ung trong L1 va L2" << endl;
    cout << "f. Kiem tra danh sach L1 va L2 co trung gia tri hay khong" << endl;
    cout << "g. Xoa 1 phan tu dau tien duoc tim thay trong L1 thoa man dieu kien: gia tri cua no lon hon tong gia tri phan tu cua L2" << endl;
    cout << "h. Xoa tat ca cac phan tu trong L1 co gia tri bang gia tri lon nhat trong L2" << endl;
    cout << "x. Thoat chuong trinh" << endl;
    cout << "Ban chon (a,b,c,d,e,f,g,h,x)? : ";
    char cChoice;
    cin >> cChoice;
    system("cls");
    switch (cChoice) {
    case 'a':
        cout << "Cac gia tri trong danh sach L3: ";
        noiDanhSach_a().xuat();
        break;
    case 'b':
        if (hieuDanhSach_b()._pHead == NULL) {
            cout << "Khong the tao L3" << endl;
        }
        else {
            cout << "Cac gia tri trong danh sach L3: ";
            hieuDanhSach_b().xuat();
        }
        break;
    case 'c':
        if (giaoDanhSach_c()._pHead == NULL) {
            cout << "Khong the tao L3" << endl;
        }
        else {
            cout << "Cac gia tri trong danh sach L3: ";
            giaoDanhSach_c().xuat();
        }
        break;
    case 'd':
        if (hopDanhSach_d()._pHead == NULL) {
            cout << "Khong the tao L3" << endl;
        }
        else {
            cout << "Cac gia tri trong danh sach L3: ";
            hopDanhSach_d().xuat();
        }
        break;
    case 'e':
        cout << "Cac gia tri trong danh sach L3: ";
        ee().xuat();
        break;
    case 'f':
        L1.xuat();
        cout << endl;
        L2.xuat();
        cout << endl;
        cout << "Co gia tri bi trung hay khong?: ";
        cout << (trungGiaTri_f() ? "Co" : "Khong") << endl;
        break;
    case 'g':
        cout << "Truoc khi xoa: " << endl;
        L1.xuat();
        cout << endl;
        L2.xuat();
        cout << endl;
        xoaDau_g();
        cout << "Sau khi xoa: " << endl;
        L1.xuat();
        cout << endl;
        L2.xuat();
        cout << endl;
        break;
    case 'h':
        cout << "Truoc khi xoa: " << endl;
        L1.xuat();
        cout << endl;
        L2.xuat();
        cout << endl;
        xoaHetEqualMax_h();
        cout << "Sau khi xoa: " << endl;
        L1.xuat();
        cout << endl;
        L2.xuat();
        cout << endl;
        break;
    case 'x':
        L1.clear();
        L2.clear();
        return;
    default:
        display();
        break;
    }
    cout << endl;
    int iInput;
    do {
        cout << "Nhap phim 1 de quay ve menu: ";
        cin >> iInput;
    } while (iInput != 1);
    display();
}

template<class DataType>
LinkedList<DataType> App<DataType>::noiDanhSach_a() {
    LinkedList<DataType> L;
    Node<DataType>* pL1 = L1._pHead;
    while (pL1 != NULL) {
        L.addTail(pL1->_data);
        pL1 = pL1->_pNext;
    }
    Node<DataType>* pL2 = L2._pHead;
    while (pL2 != NULL) {
        L.addTail(pL2->_data);
        pL2 = pL2->_pNext;
    }
    return L;
}

template<class DataType>
LinkedList<DataType> App<DataType>::hieuDanhSach_b() {
    LinkedList<DataType> L;
    Node<DataType>* pL1 = L1._pHead;
    while (pL1 != NULL) {
        if (L2.search(pL1->_data) == NULL) L.addTail(pL1->_data);
        pL1 = pL1->_pNext;
    }
    return L;
}

template<class DataType>
LinkedList<DataType> App<DataType>::giaoDanhSach_c() {
    LinkedList<DataType> L;
    Node<DataType>* pL1 = L1._pHead;

    while (pL1 != NULL) {
        // Kiểm tra xem phần tử pL1->_data có xuất hiện trong L2
        if (L2.search(pL1->_data) != NULL) {
            // Kiểm tra xem phần tử đã có trong danh sách kết quả chưa
            if (L.search(pL1->_data) == NULL) {
                L.addTail(pL1->_data);
            }
        }
        pL1 = pL1->_pNext;
    }

    return L;
}


template<class DataType>
LinkedList<DataType> App<DataType>::hopDanhSach_d() {
    LinkedList<DataType> L;
    Node<DataType>* pL1 = L1._pHead;
    while (pL1 != NULL) {
        L.addTail(pL1->_data);
        pL1 = pL1->_pNext;
    }
    Node<DataType>* pL2 = L2._pHead;
    while (pL2 != NULL) {
        if (L1.search(pL2->_data) == NULL) L.addTail(pL2->_data);
        pL2 = pL2->_pNext;
    }
    return L;
}

template<class DataType>
LinkedList<DataType> App<DataType>::ee() {
    LinkedList<DataType> L;
    Node<DataType>* pL1 = L1._pHead;
    Node<DataType>* pL2 = L2._pHead;
    while (pL1 != NULL && pL2 != NULL) {
        DataType iSum = pL1->_data + pL2->_data;
        L.addTail(iSum);
        pL1 = pL1->_pNext;
        pL2 = pL2->_pNext;
    }
    while (pL1 != NULL) {
        L.addTail(pL1->_data);
        pL1 = pL1->_pNext;
    }
    while (pL2 != NULL) {
        L.addTail(pL2->_data);
        pL2 = pL2->_pNext;
    }
    return L;
}

template<class DataType>
bool App<DataType>::trungGiaTri_f() {
    Node<DataType>* pWalker = L1._pHead;
    while (pWalker != NULL) {
        if (L2.search(pWalker->_data) != NULL) return true;
        pWalker = pWalker->_pNext;
    }
    return false;
}

template<class DataType>
void App<DataType>::xoaDau_g() {
    Node<DataType>* pWalker2 = L2._pHead;
    DataType iSum = pWalker2->_data;
    pWalker2 = pWalker2->_pNext;
    while (pWalker2 != NULL) {
        iSum += pWalker2->_data;
        pWalker2 = pWalker2->_pNext;
    }
    Node<DataType>* pWalker1 = L1._pHead;
    while (pWalker1 != NULL) {
        if (pWalker1->_data > iSum) {
            L1.remove(pWalker1->_data);
            return;
        }
        pWalker1 = pWalker1->_pNext;
    }
}

template<class DataType>
void App<DataType>::xoaHetEqualMax_h() {
    if (L2._pHead == NULL) return;

    // Tìm giá trị lớn nhất trong L2
    Node<DataType>* pWalker = L2._pHead;
    DataType iMax = pWalker->_data;
    pWalker = pWalker->_pNext;

    while (pWalker != NULL) {
        if (iMax < pWalker->_data) iMax = pWalker->_data;
        pWalker = pWalker->_pNext;
    }

    // Xóa tất cả các phần tử trong L1 có giá trị bằng iMax
    Node<DataType>* pWalkerL1 = L1._pHead;
    while (pWalkerL1 != NULL) {
        if (pWalkerL1->_data == iMax) {
            Node<DataType>* pNext = pWalkerL1->_pNext;  // Lưu trữ phần tử tiếp theo
            L1.remove(pWalkerL1->_data);
            pWalkerL1 = pNext;  // Tiếp tục với phần tử tiếp theo
        }
        else {
            pWalkerL1 = pWalkerL1->_pNext;
        }
    }
}

int main() {
    App<int> a;
    a.nhap();
}