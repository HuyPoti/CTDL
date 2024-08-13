#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
using namespace std;

bool bCheckNhap = false;
class LinkedList;

class Node {
    friend LinkedList;
private:
    string _strMssv;
    string _strHoten;
    string _strLop;
    string _strDatetime;
    double _dDtb;
    Node* _pNext;
public:
    Node();
    Node(string, string, string, string, double);
    void nhap();
    void display();
};

Node::Node() {
    _strMssv = "";
    _strHoten = "";
    _strLop = "";
    _strDatetime = "";
    _dDtb = 0;
    _pNext = NULL;
}

Node::Node(string strMssv, string strHoten, string strLop, string strDatetime, double dDtb) {
    _strMssv = strMssv;
    _strHoten = strHoten;
    _strLop = strLop;
    _strDatetime = strDatetime;
    _dDtb = dDtb;
    _pNext = NULL;
}

void Node::nhap() {
    do {
        cout << "\nNhap ma so sinh vien co dung 11 ki tu, sai phai nhap lai: ";
        cin >> _strMssv;
    } while (_strMssv.length() != 11);

    cout << "\nNhap ho ten: ";
    cin.ignore();
    getline(cin, _strHoten);

    cout << "\nNhap ten lop: ";
    cin >> _strLop;

    bool bCheckDate;
    do {
        cout << "\nNhap ngay sinh theo kieu datetime (yyyy/mm/dd), sai phai nhap lai: ";
        cin.ignore();
        getline(cin, _strDatetime);

        if (_strDatetime.length() != 10 || _strDatetime[4] != '/' || _strDatetime[7] != '/') {
            bCheckDate = false;
            continue;
        }

        string strYear = _strDatetime.substr(0, 4);
        string strMonth = _strDatetime.substr(5, 2);
        string strDay = _strDatetime.substr(8, 2);

        int year = stoi(strYear);
        int month = stoi(strMonth);
        int day = stoi(strDay);

        bCheckDate = true;

        if (month < 1 || month > 12) {
            bCheckDate = false;
            continue;
        }

        if (day < 1 || day > 31) {
            bCheckDate = false;
            continue;
        }

        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
            bCheckDate = false;
            continue;
        }

        if (month == 2) {
            bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (day > (isLeap ? 29 : 28)) {
                bCheckDate = false;
                continue;
            }
        }

    } while (!bCheckDate);

    do {
        cout << "\nNhap diem trung binh trong khoang 0 - 10, sai phai nhap lai: ";
        cin >> _dDtb;
    } while (_dDtb < 0 || _dDtb > 10);
}


   

void Node::display() {
    cout << "\nMa so sinh vien: " << _strMssv << endl;
    cout << "Ho ten: " << _strHoten << endl;
    cout << "Lop: " << _strLop << endl;
    cout << "Ngay sinh: " << _strDatetime << endl;
    cout << "Diem trung binh: " << _dDtb << endl;
}

class LinkedList {
private:
    Node* _pHead;
public:
    LinkedList() {
        _pHead = NULL;
    }
    ~LinkedList();

    void display();
    void inLinkedList();
    void outLinkedList();
    void printAverageScore();
    void linearSearch();
    void sortDanhSach();
    void binarySearch();
    void searchDelete();
    void updateScore();

    // Hàm bổ trợ
    void swapp(Node*, Node*);
    void clear();
};

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::display() {
    system("cls");
    cout << "----------------------------Bai5--------------------------" << endl;
    cout << "Cac chuc nang cua chuong trinh" << endl;
    cout << "a. Nhap danh sach sinh vien" << endl;
    cout << "b. Hien thi danh sach sinh vien" << endl;
    cout << "c. Hien thi sinh vien co diem trung binh >= 5" << endl;
    cout << "d. Tim sinh vien theo ma so" << endl;
    cout << "e. Sap xep danh sach theo ma so sinh vien" << endl;
    cout << "f. Tim kiem nhi phan theo ma so sinh vien " << endl;
    cout << "g. Xoa sinh vien theo ma so sinh vien" << endl;
    cout << "h. Cap nhat diem trung binh theo ma so sinh vien" << endl;
    cout << "----------------------------Bai5--------------------------" << endl;
    cout << "Ban chon (a->h)? : ";
    char cChoice;
    cin >> cChoice;
    if (cChoice < 'a' || cChoice > 'h') {
        cout << "\nBan nhap sai, vui long nhap lai";
        this_thread::sleep_for(chrono::seconds(1));
        display();
    }
    if (cChoice != 'a' && !bCheckNhap) {
        cout << "Danh sach dang rong!!!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        inLinkedList();
    }
    switch (cChoice) {
    case 'a':
        inLinkedList();
        break;
    case 'b':
        outLinkedList();
        break;
    case 'c':
        printAverageScore();
        break;
    case 'd':
        linearSearch();
        break;
    case 'e':
        sortDanhSach();
        break;
    case 'f':
        binarySearch();
        break;
    case 'g':
        searchDelete();
        break;
    case 'h':
        updateScore();
        break;
    }
}

void LinkedList::inLinkedList() {
    system("cls");
    clear();
    bCheckNhap = true;
    cout << "Nhap danh sach sinh vien:" << endl;
    string strChecked;
    Node* pTemp = _pHead;
    do {
        Node* p = new Node;
        p->nhap();
        if (_pHead == NULL) {
            _pHead = p;
            pTemp = _pHead;
        }
        else {
            pTemp->_pNext = p;
            pTemp = p;
        }
        cout << "Ban muon nhap tiep (Yes/No)? : ";
        cin >> strChecked;
        for (int i = 0; i < strChecked.length(); i++) {
            strChecked[i] = tolower(strChecked[i]);
        }

    } while (strChecked == "yes");
    display();
}

void LinkedList::outLinkedList() {
    system("cls");
    cout << "Day la danh sach sinh vien: " << endl;
    Node* p = _pHead;
    while (p != NULL) {
        p->display();
        p = p->_pNext;
    }
    int iChecked;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iChecked;
    } while (iChecked != 1);
    display();
}

void LinkedList::printAverageScore() {
    system("cls");
    cout << "Danh sach sinh vien nhan hoc bong:" << endl;
    Node* p = _pHead;
    while (p != NULL) {
        if (p->_dDtb >= 5) {
            p->display();
        }
        p = p->_pNext;
    }
    int iChecked;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iChecked;
    } while (iChecked != 1);
    display();
}

void LinkedList::linearSearch() {
    system("cls");
    cout << "Nhap ma sinh vien: ";
    string strMssv;
    cin >> strMssv;
    Node* p = _pHead;
    while (p != NULL) {
        if (p->_strMssv == strMssv) {
            p->display();
            break;
        }
        p = p->_pNext;
    }
    int iChecked;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iChecked;
    } while (iChecked != 1);
    display();
}

void LinkedList::sortDanhSach() {
    system("cls");
    if (_pHead == NULL || _pHead->_pNext == NULL) {
        cout << "Danh sach trong hoac chi co mot phan tu." << endl;
    }
    else {
        for (Node* p = _pHead; p->_pNext != NULL; p = p->_pNext) {
            Node* pMin = p;
            for (Node* q = p->_pNext; q != NULL; q = q->_pNext) {
                if (pMin->_strMssv > q->_strMssv) {
                    pMin = q;
                }
            }
            if (pMin != p) {
                swapp(pMin, p);
            }
        }
        cout << "Danh sach da duoc sap xep." << endl;
    }
    int iChecked;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iChecked;
    } while (iChecked != 1);
    display();
}

void LinkedList::binarySearch() {
    system("cls");
    cout << "Nhap ma so sinh vien cua sinh vien can tim: ";
    string strMssv;
    cin >> strMssv;
    for (Node* p = _pHead; p->_pNext != NULL; p = p->_pNext) {
        Node* pMin = p;
        for (Node* q = p->_pNext; q != NULL; q = q->_pNext) {
            if (pMin->_strMssv > q->_strMssv) {
                pMin = q;
            }
        }
        if (pMin != p) {
            swapp(pMin, p);
        }
    }
    Node* pLeft = _pHead;
    Node* pRight = NULL;
    bool found = false;

    while (pLeft != pRight) {
        Node* pMid = pLeft;
        Node* pStep = pLeft;

        // Tìm phần tử giữa
        while (pStep != pRight && pStep->_pNext != pRight) {
            pMid = pMid->_pNext;
            pStep = pStep->_pNext->_pNext;
        }

        if (pMid->_strMssv == strMssv) {
            pMid->display();
            found = true;
            break;
        }
        else if (pMid->_strMssv > strMssv) {
            pRight = pMid;
        }
        else {
            pLeft = pMid->_pNext;
        }
    }

    if (!found) {
        cout << "Khong tim thay sinh vien can tim" << endl;
    }

    int iChecked;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iChecked;
    } while (iChecked != 1);
    display();
}

void LinkedList::searchDelete() {
    system("cls");
    cout << "Nhap ma so sinh vien can xoa: ";
    string strMssv;
    cin >> strMssv;
    Node* p = _pHead;
    Node* q = NULL;
    while (p != NULL) {
        if (p->_strMssv == strMssv) {
            break;
        }
        q = p;
        p = p->_pNext;
    }
    if (p == NULL) {
        cout << "Khong co sinh vien nao co ma so sinh vien: " << strMssv;
    }
    else {
        if (q == NULL) {
            _pHead = p->_pNext;
        }
        else {
            q->_pNext = p->_pNext;
        }
        delete p;
        cout << "Da xoa sinh vien ra khoi danh sach";
    }
    int iChecked;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iChecked;
    } while (iChecked != 1);
    display();
}

void LinkedList::updateScore() {
    system("cls");
    cout << "Nhap ma so sinh vien muon cap nhat lai diem trung binh: ";
    string strMssv;
    cin >> strMssv;
    Node* p = _pHead;
    while (p != NULL) {
        if (p->_strMssv == strMssv) {
            cout << "Nhap diem trung binh moi: ";
            cin >> p->_dDtb;
            cout << "Cap nhat thanh cong!" << endl;
            break;
        }
        p = p->_pNext;
    }
    if (p == NULL) {
        cout << "Khong tim thay sinh vien voi ma so " << strMssv << endl;
    }
    int iChecked;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iChecked;
    } while (iChecked != 1);
    display();
}

void LinkedList::swapp(Node* a, Node* b) {
    swap(a->_dDtb, b->_dDtb);
    swap(a->_strDatetime, b->_strDatetime);
    swap(a->_strHoten, b->_strHoten);
    swap(a->_strLop, b->_strLop);
    swap(a->_strMssv, b->_strMssv);
}

void LinkedList::clear(){
    while (_pHead != NULL) {
        Node* pTemp = _pHead;
        _pHead = _pHead->_pNext;
        delete pTemp;
    }
}

int main() {
    LinkedList L;
    L.display();
}