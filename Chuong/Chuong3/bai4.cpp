#include <iostream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

bool bCheckNhap = false;

class App;

class Node {
	friend class LinkedList;
	friend class App;
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
	friend class App;
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

	// Hàm bổ trợ
	void nhap();
	void selectionSort();
};

// Các hàm chính trong LinkedList
LinkedList::LinkedList() {
	_pHead = NULL;
	_pTail = NULL;
	_iSize = 0;
}

LinkedList::~LinkedList() {
	clear();
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


void LinkedList::nhap() {
	cout << "Nhap danh sach nguyen: ";
	string strInput;
	getline(cin, strInput);
	stringstream ss(strInput);
	string temp;
	int iTemp;

	while (ss >> temp) {
		if (stringstream(temp) >> iTemp) {
			addTail(iTemp);
		}
	}
}

void LinkedList::selectionSort() {
	Node* p, * q;
	Node* pMin;
	for (p = _pHead; p->_pNext != NULL; p = p->_pNext) {
		pMin = p;
		for (q = p->_pNext; q != NULL; q = q->_pNext) {
			if (pMin->_data > q->_data)	pMin = q;
		}
		swap(pMin->_data, p->_data);
	}
}

class App {
private:
	LinkedList L1, L2, L3;
public:
	// Hàm chính
	void display();
	void hieuTapHop_a();
	void giaoTapHop_b();
	void hopTapHop_c();
	void nhapDanhSach();
};

void App::display() {
	system("cls");
	L3.clear();
	cout << "a. Tao danh sach L3 la ket qua cua tap hop L1 hieu tap hop L2 va L3 co thu tu tang dan" << endl;
	cout << "b. Tao danh sach L3 la ket qua cua tap hop L1 giao tap hop L2 va L3 co thu tu tang dan" << endl;
	cout << "c. Tao danh sach L3 la ket qua cua tap hop L1 hop tap hop L2 va L3 co thu tu tang dan" << endl;
	cout << "d. Thoat chuong trinh" << endl;
	cout << "Ban chon (a, b, c, d)? :" << endl;
	char cChoice;
	cin >> cChoice;
	switch (cChoice) {
	case 'a':
		hieuTapHop_a();
		break;
	case 'b':
		giaoTapHop_b();
		break;
	case 'c':
		hopTapHop_c();
		break;
	case 'd':
		cout << "Thoat chuong trinh";
		return;
	default:
		display();
		break;
	}
}

void App::hieuTapHop_a() {
	system("cls");
	Node* pL1 = L1._pHead;
	while (pL1 != NULL) {
		if (L2.search(pL1->_data) == NULL) L3.addTail(pL1->_data);
		pL1 = pL1->_pNext;
	}
	if (L3._pHead == NULL) {
		cout << "Khong tao duoc L3" << endl;
		cout << "Danh sach L1: ";
		L1.xuat();
		cout << "\nDanh sach L2: ";
		L2.xuat();
	}
	else {
		L3.selectionSort();
		cout << "Danh sach L1: ";
		L1.xuat();
		cout << "\nDanh sach L2: ";
		L2.xuat();
		cout << "\nDanh sach L3 : ";
		L3.xuat();
	}
	cout << endl;
	int iInput;
	do {
		cout << "An phim 1 de thoat: ";
		cin >> iInput;
		cout << endl;
	} while (iInput != 1);
	display();
}
void App::giaoTapHop_b() {
	system("cls");
	Node* pL1 = L1._pHead;

	while (pL1 != NULL) {
		// Kiểm tra xem phần tử pL1->_data có xuất hiện trong L2
		if (L2.search(pL1->_data) != NULL) {
			// Kiểm tra xem phần tử đã có trong danh sách kết quả chưa
			if (L3.search(pL1->_data) == NULL) {
				L3.addTail(pL1->_data);
			}
		}
		pL1 = pL1->_pNext;
	}
	if (L3._pHead == NULL) {
		cout << "Khong tao duoc L3" << endl;
		cout << "Danh sach L1: ";
		L1.xuat();
		cout << "\nDanh sach L2: ";
		L2.xuat();
	}
	else {
		L3.selectionSort();
		cout << "Danh sach L1: ";
		L1.xuat();
		cout << "\nDanh sach L2: ";
		L2.xuat();
		cout << "\nDanh sach L3 : ";
		L3.xuat();
	}
	cout << endl;
	int iInput;
	do {
		cout << "An phim 1 de thoat: ";
		cin >> iInput;
		cout << endl;
	} while (iInput != 1);
	display();
}
void App::hopTapHop_c() {
	system("cls");
	Node* pL1 = L1._pHead;
	while (pL1 != NULL) {
		L3.addTail(pL1->_data);
		pL1 = pL1->_pNext;
	}
	Node* pL2 = L2._pHead;
	while (pL2 != NULL) {
		if (L1.search(pL2->_data) == NULL) L3.addTail(pL2->_data);
		pL2 = pL2->_pNext;
	}
	if (L3._pHead == NULL) {
		cout << "Khong tao duoc L3" << endl;
		cout << "Danh sach L1: ";
		L1.xuat();
		cout << "\nDanh sach L2: ";
		L2.xuat();
	}
	else {
		L3.selectionSort();
		cout << "Danh sach L1: ";
		L1.xuat();
		cout << "\nDanh sach L2: ";
		L2.xuat();
		cout << "\nDanh sach L3 : ";
		L3.xuat();
	}
	cout << endl;
	int iInput;
	do {
		cout << "An phim 1 de thoat: ";
		cin >> iInput;
		cout << endl;
	} while (iInput != 1);
	display();
}
void App::nhapDanhSach() {
	system("cls");
	cout << "Luu y: de ket thuc 1 lan nhap, ban vui long nhan Enter" << endl;
	cout << "Nhap L1:" << endl;
	L1.nhap();
	cout << endl;
	cout << "Nhap L2:" << endl;
	L2.nhap();
	cout << endl;
	int iInput;
	do {
		cout << "An phim 1 de thoat: ";
		cin >> iInput;
		cout << endl;
	} while (iInput != 1);
	display();
}
int main() {
	App a;
	a.nhapDanhSach();
}