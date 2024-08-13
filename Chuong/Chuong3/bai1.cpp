#include <iostream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cmath> // Để sử dụng hàm sqrt
using namespace std;

bool bCheckNhap = false;

class Node {
	friend class LinkedList;
private:
	int _data;
	Node* _pNext;
public:
	Node(int value);
	void xuat();
};

Node::Node(int data) {
	_data = data;
	_pNext = NULL;
}

void Node::xuat() {
	cout << _data;
}

class LinkedList {
private:
	Node* _pHead;
	Node* _pTail;
	int _iSize;
public:
	// Các thao tác chính
	LinkedList();
	~LinkedList();
	void addHead(int);
	void addTail(int);
	void addAfter(Node*, int);
	Node* search(int);
	Node* searchPre(Node*);
	void removeHead();
	void removeTail();
	void removeAfter(Node*);
	void remove(int);
	void xuat();
	void clear();

	// Hàm triển khai
	void display();
	void nhapDanhSach_a();
	void xuatDanhSach_b();
	void lietKeSnt_c();
	void tbc_d();
	void countN_e();
	void lastScp_f();
	void searchPosK_g();
	void searchMin_h();
	void insertAfterQ_i();
	void insertNotDupj();
	void deleteKFirst_k();
	void DeleteX_l();
	void deleteAfterQ_m();
	void deleteLapLai_n();
	void interchangeSort_o();
	void insertIncreas_p();
	void shtThanh0_q();

	// Hàm bổ trợ
	bool checkSnt(int);
	Node* seachAndReturnK(int);
	bool checkSht(int);
	Node* minNumber();
};

// Các hàm chính trong LinkedList
LinkedList::LinkedList() {
	_pHead = NULL;
	_pTail = NULL;
	_iSize = 0;
}

LinkedList::~LinkedList() {
	clear(); // Xóa tất cả các nút khi hủy đối tượng
}

void LinkedList::addHead(int data) {
	Node* pAdd = new Node(data);
	if (_pHead == NULL) {
		_pHead = _pTail = pAdd;
	}
	else {
		pAdd->_pNext = _pHead;
		_pHead = pAdd;
	}
	_iSize++;
}

void LinkedList::addTail(int data) {
	Node* pAdd = new Node(data);
	if (_pHead == NULL) {
		_pHead = _pTail = pAdd;
	}
	else {
		_pTail->_pNext = pAdd;
		_pTail = pAdd;
	}
	_iSize++;
}

void LinkedList::addAfter(Node* node, int data) {
	Node* pAdd = new Node(data);
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

Node* LinkedList::search(int data) {
	Node* pSe = _pHead;
	while ((pSe != NULL) && (pSe->_data != data)) {
		pSe = pSe->_pNext;
	}
	return pSe;
}

Node* LinkedList::searchPre(Node* node) {
	Node* pSe = _pHead;
	if (pSe == node) {
		return NULL;
	}
	while ((pSe != NULL) && (pSe->_pNext != node)) {
		pSe = pSe->_pNext;
	}
	return pSe;
}

void LinkedList::removeHead() {
	if (_pHead != NULL) {
		Node* pRe = _pHead;
		_pHead = _pHead->_pNext;
		delete pRe;
		if (_pHead == NULL) {
			_pTail = NULL;
		}
	}
}

void LinkedList::removeTail() {
	if (_pHead != NULL) {
		Node* pRe = _pTail;
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

void LinkedList::removeAfter(Node* node) {
	Node* pTemp;
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

void LinkedList::remove(int data) {
	Node* pWalker = _pHead;
    Node* pPrev = NULL;

    while (pWalker != NULL && pWalker->_data != data) {
        pPrev = pWalker;
        pWalker = pWalker->_pNext;
    }

    if (pWalker == NULL) return; // Giá trị không tìm thấy

    if (pPrev != NULL) {
        pPrev->_pNext = pWalker->_pNext;
        if (pWalker == _pTail) {
            _pTail = pPrev;
        }
    } else {
        _pHead = pWalker->_pNext;
        if (_pHead == NULL) {
            _pTail = NULL;
        }
    }

    delete pWalker;
    _iSize--;
}

void LinkedList::xuat() {
	Node* pWalker = _pHead;
	while (pWalker != NULL) {
		pWalker->xuat();
		cout << " ";
		pWalker = pWalker->_pNext;
	}
}

void LinkedList::clear() {
	while (_pHead != NULL) {
		removeHead();
	}
}

// Hàm triển khai
void LinkedList::display() {
	system("cls");
	cout << "a. Nhap danh sach lien ket don cac so nguyen bang cach them tung phan tu vao cuoi danh sach" << endl;
	cout << "b. Xuat danh sach ra man hinh" << endl;
	cout << "c. Liet ke cac so nguyen to trong danh sach" << endl;
	cout << "d. Tinh trung binh cong cua cac phan tu trong danh sach" << endl;
	cout << "e. Dem so lan xuat hien cua mot so nguyen nhap tu ban phim co trong danh sach" << endl;
	cout << "f. Tim so chinh phuong cuoi cung trong danh sach" << endl;
	cout << "g. Tim va tra ve phan tu thu k trong danh sach tinh tu dau danh sach" << endl;
	cout << "h. Tim phan tu co gia tri nho nhat trong danh sach" << endl;
	cout << "i. Them mot phan tu vao sau phan tu q trong danh sach" << endl;
	cout << "j. Them mot phan tu vao danh sach sao cho phan tu them vao khong trung voi cac phan tu da co trong danh sach" << endl;
	cout << "k. Xoa k phan tu o dau danh sach (k nhap tu ban phim) " << endl;
	cout << "l. Xoa phan tu co gia tri bang x co trong danh sach" << endl;
	cout << "m. Xoa mot phan tu sau phan tu q trong danh sach" << endl;
	cout << "n. Xoa tat ca cac phan tu lap lai trong danh sach (chi giu lai duy nhat mot phan tu)" << endl;
	cout << "o. Sap xep danh sach theo thu tu tang dan dung Interchange Sort" << endl;
	cout << "p. Them mot phan tu vao danh sach tang dan (qua trinh them khong lam mat tinh tang dan cua danh sach)" << endl;
	cout << "q. Cap nhat cac so hoan thien trong danh sach thanh so 0" << endl;
	cout << "Ban chon a b c d e f g h i j k l m n o p q ? : ";
	char cChoice;
	cin >> cChoice;
	if (cChoice != 'a') {
		if (bCheckNhap) {
			switch (cChoice) {
			case 'b':
				xuatDanhSach_b();
				break;
			case 'c':
				lietKeSnt_c();
				break;
			case 'd':
				tbc_d();
				break;
			case 'e':
				countN_e();
				break;
			case 'f':
				lastScp_f();
				break;
			case 'g':
				searchPosK_g();
				break;
			case 'h':
				searchMin_h();
				break;
			case 'i':
				insertAfterQ_i();
				break;
			case 'j':
				insertNotDupj();
				break;
			case 'k':
				deleteKFirst_k();
				break;
			case 'l':
				DeleteX_l();
				break;
			case 'm':
				deleteAfterQ_m();
				break;
			case 'n':
				deleteLapLai_n();
				break;
			case 'o':
				interchangeSort_o();
				break;
			case 'p':
				insertIncreas_p();
				break;
			case 'q':
				shtThanh0_q();
				break;
			default:
				display();
				break;
			}
		}
		else {
			nhapDanhSach_a();
		}
	}
	else nhapDanhSach_a();
}

void LinkedList::nhapDanhSach_a() {
	system("cls");
	cout << "Nhap danh sach, nhap ki tu 'e' roi nhan phim enter de ket thuc (cac so sau e se khong tinh vao) : "<<endl;
	string strInput;
	int iInput;
	vector<int> v;
	while (true) {
		cin >> strInput;
		if (strInput == "e") {
			break;
		}
		stringstream ss(strInput);
		ss >> iInput;
		if (ss.fail() || !ss.eof()) {
			continue;
		}
		v.push_back(iInput);
	}
	for (int i = 0; i < v.size(); i++) {
		addTail(v[i]);
	}
	cout << "Ban da nhap xong, nhap phim 1 de ket thuc: ";
	do {
		cin >> iInput;
	} while (iInput != 1);
	bCheckNhap = true;
	display();
}

void LinkedList::xuatDanhSach_b() {
	system("cls");
	cout << "Danh sach:" << endl;
	xuat();
	cout << endl;
	int iInput;
	do {
		cout << "Danh sach da in xong, nhap phim 1 de ket thuc: ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}

void LinkedList::lietKeSnt_c() {
	system("cls");
	Node* pWalker = _pHead;
	while (pWalker != NULL) {
		if (checkSnt(pWalker->_data)) {
			pWalker->xuat();
			cout << " ";
		}
		pWalker = pWalker->_pNext;
	}
	cout << endl;
	int iInput;
	do {
		cout << "Da liet ke xong cac so nguyen to, nhap phim 1 de ket thuc: ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}

void LinkedList::tbc_d() {
	system("cls");
	int sum = 0;
	Node* pWalker = _pHead;
	while (pWalker != NULL) {
		sum += pWalker->_data;
		pWalker = pWalker->_pNext;
	}
	sum /= _iSize;
	cout << "Ket qua: " << sum << endl;
	int iInput;
	do {
		cout << "Da tim ra trung binh cua cac phan tu co strong danh sach, nhap phim 1 de ket thuc: ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}

void LinkedList::countN_e() {
	system("cls");
	cout << "Nhap so nguyen can biet so lan xuat hien: ";
	int iElement, iCount = 0;
	cin >> iElement;
	Node* pWalker = _pHead;
	while (pWalker != NULL) {
		if (pWalker->_data == iElement) {
			iCount++;
		}
		pWalker = pWalker->_pNext;
	}
	cout << "\nKet qua: " << iCount << endl;
	int iInput;
	do {
		cout << "Da dem duoc so lan xuat hien cua so " << iElement << ", nhap phim 1 de ket thuc : ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}

void LinkedList::lastScp_f() {
	system("cls");
	Node* pWalker = _pHead;
	int iElement;
	while (pWalker != NULL) {
		if (sqrt(pWalker->_data)==(int)sqrt(pWalker->_data)) {
			iElement = pWalker->_data;
		}
		pWalker = pWalker->_pNext;
	}
	cout << "Ket qua: " << iElement << endl;
	int iInput;
	do {
		cout << "Da tim duoc so chinh phuong cuoi cung trong danh sach, nhap phim 1 de ket thuc: ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}

void LinkedList::searchPosK_g() {
	system("cls");
	cout << "Nhap vi tri k: ";
	int iElement;
	cin >> iElement;
	Node* p = seachAndReturnK(iElement);
	cout << "\nKet qua: " << p->_data << endl;
	int iInput;
	do {
		cout << "Da tim va tra ve phan tu thu "<<iElement<<", nhap phim 1 de ket thuc : ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}

void LinkedList::searchMin_h() {
	system("cls");
	Node* p = minNumber();
	cout << "Phan tu co gia tri nho nhat trong danh sach co gia tri la " << p->_data << endl;
	int iInput;
	do {
		cout << "Da in ra phan tu co gia tri nho nhat, nhap phim 1 de ket thuc: ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}
void LinkedList::insertAfterQ_i() {
	system("cls");
	cout << "Nhap phan tu muon them vao: ";
	int iElement;
	cin >> iElement;
	cout << "\nNhap phan tu q: ";
	int iAfter;
	cin >> iAfter;
	Node* pInsert = search(iAfter);
	addAfter(pInsert,iElement);
	cout << endl;
	int iInput;
	do {
		cout << "Da them phan tu moi nhap vao sau phan tu q, nhap phim 1 de ket thuc: ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}

void LinkedList::insertNotDupj() {
	system("cls");
	int iAdd;
	bool bOk = true;
	Node* pTest;
	do {
		if (bOk) {
			cout << "Nhap phan tu can them: ";
			bOk = false;
		}
		else cout << "Da co phan tu do tronng mang. Nhap lai phan tu can them: ";
		cin >> iAdd;
		pTest = search(iAdd);
	} while (pTest != NULL);
	addTail(iAdd);
	int iInput;
	do {
		cout << "Da them vao phan tu vao danh sach ma khong bi trung voi cac phan tu con lai, nhap phim 1 de ket thuc: ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}

void LinkedList::deleteKFirst_k() {
	system("cls");
	cout << "Nhap so luong phan tu can xoa (o dau danh sach): ";
	int iDelete;
	cin >> iDelete;
	while (iDelete--) {
		removeHead();
	}
	int iInput;
	do {
		cout << "Da xoa k phan tu o dau danh sach, nhap phim 1 de ket thuc: ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}

void LinkedList::DeleteX_l() {
	system("cls");
	cout << "Nhap gia tri x can xoa: ";
	int iDelete;
	cin >> iDelete;
	while(search(iDelete)!=NULL)	remove(iDelete);
	int iInput;
	do {
		cout << "Da xoa nhung phan tu co gia tri bang x, nhap phim 1 de ket thuc: ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}

void LinkedList::deleteAfterQ_m() {
	system("cls");
	cout << "Nhap phan tu q: ";
	int iBefore;
	cin >> iBefore;
	Node* p = search(iBefore);
	removeAfter(p);
	int iInput;
	do {
		cout << "Da xoa 1 phan tu sau phan tu q, nhap phim 1 de ket thuc: ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}

void LinkedList::deleteLapLai_n() {
	system("cls");
	Node* pWalker = _pHead;
	while (pWalker != NULL) {
		int iElement = pWalker->_data;
		Node* pJoker = pWalker->_pNext;
		Node* pPrev = pWalker;  // Thêm biến này để theo dõi nút trước đó của pJoker
		while (pJoker != NULL) {
			if (pJoker->_data == iElement) {
				Node* pTemp = pJoker;
				pJoker = pJoker->_pNext;
				pPrev->_pNext = pJoker;
				if (pTemp == _pTail) {
					_pTail = pPrev;
				}
				delete pTemp;
				_iSize--;
			}
			else {
				pPrev = pJoker;
				pJoker = pJoker->_pNext;
			}
		}
		pWalker = pWalker->_pNext;
	}

	int iInput;
	do {
		cout << "Da xoa xong, nhap phim 1 de ket thuc: ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}

void LinkedList::interchangeSort_o() {
	system("cls");
	Node* pWalker = _pHead;
	while (pWalker != NULL) {
		Node* pContinue = pWalker->_pNext;
		while (pContinue != NULL) {
			if (pWalker->_data > pContinue->_data)	swap(pWalker->_data, pContinue->_data);
			pContinue = pContinue->_pNext;
		}
		pWalker = pWalker->_pNext;
	}
	int iInput;
	do {
		cout << "Da sap xep danh sach theo thu tu tang dan, nhap phim 1 de ket thuc: ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}

void LinkedList::insertIncreas_p() {
	system("cls");
	cout << "Nhap phan tu can them vao: ";
	int iInsert;
	cin >> iInsert;
	Node* pWalker = _pHead;
	Node* pPrev = NULL;
	while (pWalker != NULL && pWalker->_data < iInsert) {
		pPrev = pWalker;
		pWalker = pWalker->_pNext;
	}
	addAfter(pPrev, iInsert);
	int iInput;
	do {
		cout << "Da cap nhat xong , nhap phim 1 de ket thuc: ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}

void LinkedList::shtThanh0_q() {
	system("cls");
	Node* pWalker = _pHead;
	while (pWalker != NULL) {
		if (checkSht(pWalker->_data)) {
			pWalker->_data = 0;
		}
		pWalker = pWalker->_pNext;
	}
	int iInput;
	do {
		cout << "Da in xong cac so nguyen to, nhap phim 1 de ket thuc: ";
		cin >> iInput;
	} while (iInput != 1);
	display();
}

//Hàm bổ trợ
bool LinkedList::checkSnt(int data) {
	if (data < 2) return false;
	for (int i = 2; i <= sqrt(data); i++) {
		if (data % i == 0) return false;
	}
	return true;
}

Node* LinkedList::seachAndReturnK(int iElement) {
	int iCount = 0;
	Node* pWalker = _pHead;
	while (pWalker != NULL) {
		iCount++;
		if (iCount == iElement) {
			break;
		}
		pWalker = pWalker->_pNext;
	}
	return pWalker;
}

Node* LinkedList::minNumber() {
	Node* pWalker = _pHead;
	int iMin = INT_MAX;
	Node* pMin = NULL;
	while (pWalker != NULL) {
		if (iMin > pWalker->_data) {
			iMin = pWalker->_data;
			pMin = pWalker;
		}
		pWalker = pWalker->_pNext;
	}
	return pMin;
}
bool LinkedList::checkSht(int iValue) {
	int sum = 0;
	for (int i = 1; i <= iValue/2; i++) {
		if (iValue % i == 0)	sum += i;
	}
	return iValue == sum;
}

int main() {
	LinkedList a;
	a.display();
	return 0;
}
