#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm> // Để dùng std::find và std::swap
using namespace std;

bool bCheckDoc = false;
class LinkedList;

class Node {
    friend class LinkedList;
private:
    string _strTenPhim;
    string _strTheLoai;
    string _strDaoDien;
    string _strNam9;
    string _strNu9;
    string _strNam;
    Node* _pNext;
public:
    Node(string, string, string, string, string, string);
    void xuat();
};

Node::Node(string strTenPhim, string strTheLoai, string strDaoDien, string strNam9, string strNu9, string strNam) {
    _strTenPhim = strTenPhim;
    _strTheLoai = strTheLoai;
    _strDaoDien = strDaoDien;
    _strNam9 = strNam9;
    _strNu9 = strNu9;
    _strNam = strNam;
    _pNext = nullptr;
}

void Node::xuat() {
    cout << "\nTen phim: " << _strTenPhim << endl;
    cout << "The loai: " << _strTheLoai << endl;
    cout << "Ten dao dien: " << _strDaoDien << endl;
    cout << "Ten dien vien nam chinh: " << _strNam9 << endl;
    cout << "Ten dien vien nu chinh: " << _strNu9 << endl;
    cout << "Nam san xuat: " << _strNam << endl;
}

class LinkedList {
private:
    Node* _pHead;
public:
    LinkedList();
    ~LinkedList();

    void aa();
    void bb();
    void ccc();
    void dd();
    void ee();
    void ff();
    void display();

    void clear();
    void swapp(Node*, Node*);
};

LinkedList::LinkedList() {
    _pHead = nullptr;
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::aa() {
    system("cls");
    ifstream fileIn("Input.txt");
    string strTenPhim;
    string strTheLoai;
    string strDaoDien;
    string strNam9;
    string strNu9;
    string strNam;
    string strInput;
    string strIndex;
    Node* pLast = nullptr;
    while (getline(fileIn, strInput)) {
        stringstream ss(strInput);
        getline(ss, strIndex, '#');
        strTenPhim = strIndex;
        getline(ss, strIndex, '#');
        strTheLoai = strIndex;
        getline(ss, strIndex, '#');
        strDaoDien = strIndex;
        getline(ss, strIndex, '#');
        strNam9 = strIndex;
        getline(ss, strIndex, '#');
        strNu9 = strIndex;
        getline(ss, strIndex, '#');
        strNam = strIndex;
        Node* p = new Node(strTenPhim, strTheLoai, strDaoDien, strNam9, strNu9, strNam);
        if (_pHead == nullptr) {
            _pHead = p;
        }
        else {
            pLast->_pNext = p;
        }
        pLast = p;
    }
    fileIn.close();
    bCheckDoc = true;  // Đánh dấu đã đọc dữ liệu
    cout << "Da doc file vao danh sach";
    int iExit;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iExit;
    } while (iExit != 1);
    display();
}

void LinkedList::bb() {
    system("cls");
    if (!bCheckDoc) {
        cout << "Danh sach dang rong!!!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        aa();
    }
    cout << "Nhap ten phim ban muon cap nhat lai the loai: ";
    string strTenPhim;
    cin >> strTenPhim;
    string strTheLoai;
    do {
        cout << "\nNhap the loai can cap nhat (HInhSu | TinhCam | Hai)? : ";
       
        cin >> strTheLoai;
    } while (strTheLoai != "HinSu" && strTheLoai != "TinhCam" && strTheLoai != "Hai");
    Node* p = _pHead;
    while (p != nullptr) {
        if (p->_strTenPhim == strTenPhim) {
            p->_strTheLoai = strTheLoai;
            break;
        }
        p = p->_pNext;
    }
    ofstream fileOut("Input.txt");
    string strLine;
    p = _pHead;
    while (p != nullptr) {
        strLine = p->_strTenPhim + "#" + p->_strTheLoai + "#" + p->_strDaoDien + "#" + p->_strNam9 + "#" + p->_strNu9 + "#" + p->_strNam;
        fileOut << strLine << endl;
        p = p->_pNext;  // Đảm bảo p di chuyển qua các node
    }
    fileOut.close();
    cout << "Da cap nhat file";
    int iExit;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iExit;
    } while (iExit != 1);
    display();
}

void LinkedList::ccc() {
    system("cls");
    if (!bCheckDoc) {
        cout << "Danh sach dang rong!!!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        aa();
    }

    cout << "Danh sach cac bo phim:" << endl;
    Node* p = _pHead;
    while (p != nullptr) {
        p->xuat();
        p = p->_pNext;
    }
    int iExit;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iExit;
    } while (iExit != 1);
    display();
}

void LinkedList::dd() {
    system("cls");
    if (!bCheckDoc) {
        cout << "Danh sach dang rong!!!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        aa();
    }

    cout << "Nhap ten nam dien vien: ";
    string strNam9;
    cin >> strNam9;
    ofstream fileOut(strNam9 + ".txt");
    Node* p = _pHead;
    while (p != nullptr) {
        if (p->_strNam9 == strNam9) {
            fileOut << p->_strTenPhim << endl;
        }
        p = p->_pNext;
    }
    fileOut.close();
    cout << "Da tao file thanh cong";
    int iExit;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iExit;
    } while (iExit != 1);
    display();
}

void LinkedList::ee() {
    system("cls");
    if (!bCheckDoc) {
        cout << "Danh sach dang rong!!!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        aa();
    }

    vector<string> vDaoDien;
    Node* p = _pHead;
    while (p != nullptr) {
        if (find(vDaoDien.begin(), vDaoDien.end(), p->_strDaoDien) == vDaoDien.end()) {
            vDaoDien.push_back(p->_strDaoDien);
        }
        p = p->_pNext;
    }
    for (const string& daoDien : vDaoDien) {
        p = _pHead;
        ofstream fileOut(daoDien + ".txt");
        vector<string> vPhim;
        while (p != nullptr) {
            if (p->_strDaoDien == daoDien) {
                string strUpdate = p->_strTenPhim + "#" + p->_strTheLoai + "#" + p->_strNam9 + "#" + p->_strNu9 + "#" + p->_strNam;
                vPhim.push_back(strUpdate);
            }
            p = p->_pNext;
        }
        fileOut << vPhim.size() << endl;
        for (const string& phim : vPhim) {
            fileOut << phim << endl;
        }
        fileOut.close();
    }
    cout << "Da tao file thanh cong";
    int iExit;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iExit;
    } while (iExit != 1);
    display();
}

void LinkedList::ff() {
    system("cls");
    if (!bCheckDoc) {
        cout << "Danh sach dang rong!!!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        aa();
    }

    Node* pMin;
    for (Node* p = _pHead; p->_pNext != nullptr; p = p->_pNext) {
        pMin = p;
        for (Node* q = p->_pNext; q != nullptr; q = q->_pNext) {
            if (pMin->_strNam < q->_strNam) {
                pMin = q;
            }
        }
        swapp(pMin, p);
    }
    ofstream fileOut("PhimMoi.txt");
    Node* p = _pHead;
    int iSize = 3;
    while (iSize-- && p != nullptr) {
        string strUpdate = p->_strTenPhim + "#" + p->_strDaoDien + "#" + p->_strTheLoai + "#" + p->_strNam9 + "#" + p->_strNu9 + "#" + p->_strNam;
        fileOut << strUpdate << endl;
        p = p->_pNext;
    }
    fileOut.close();
    cout << "Da tao file thanh cong";
    int iExit;
    do {
        cout << "\nAn phim 1 de thoat: ";
        cin >> iExit;
    } while (iExit != 1);
    display();
}

void LinkedList::display() {
    system("cls");
    cout << "--------------------Bai8----------------------" << endl;
    cout << "a. Doc danh sach cac bo phim cung cac thong tin lien qua den bo phim nay tu file Input.txt" << endl;
    cout << "b. Cap nhat the loai phim cho bo phim co ten X. Ghi du lieu lai vao file Input.txt" << endl;
    cout << "c. In ra man hinh danh sach cac bo phim sau khi cap nhat" << endl;
    cout << "d. Tao file danh sach cac bo phim co ten cua dien vien nhap tu ban phim" << endl;
    cout << "e. Xuat file thong ke tong so phim va thong tin cua cac bo phim cho moi dao dien, moi dao dien mot file" << endl;
    cout << "f. Xuat file chua thong tin 3 bo phim moi nhat" << endl;
    cout << "--------------------Bai8----------------------" << endl;
    cout << "Ban chon (a->f)? : ";
    char cChoice;
    cin >> cChoice;
    cin.ignore();
    if (cChoice < 'a' || cChoice > 'f') { // Chỉnh sửa cChoice từ 'h' thành 'f'
        cout << "\nBan nhap sai, vui long nhap lai";
        this_thread::sleep_for(chrono::seconds(1));
        display();
    }
    if (cChoice != 'a' && !bCheckDoc) {
        cout << "Danh sach dang rong!!!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        aa();
    }
    switch (cChoice) {
    case 'a':
        aa();
        break;
    case 'b':
        bb();
        break;
    case 'c':
        ccc();
        break;
    case 'd':
        dd();
        break;
    case 'e':
        ee();
        break;
    case 'f':
        ff();
        break;
    }
}

void LinkedList::clear() {
    while (_pHead != nullptr) {
        Node* pTemp = _pHead;
        _pHead = _pHead->_pNext;
        delete pTemp;
    }
}

void LinkedList::swapp(Node* a, Node* b) {
    swap(a->_strDaoDien, b->_strDaoDien);
    swap(a->_strNam, b->_strNam);
    swap(a->_strNam9, b->_strNam9);
    swap(a->_strNu9, b->_strNu9);
    swap(a->_strTenPhim, b->_strTenPhim);
    swap(a->_strTheLoai, b->_strTheLoai);
}

int main() {
    LinkedList L;
    L.display();
}

