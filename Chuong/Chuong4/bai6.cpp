#include <iostream>
#include <thread>
#include <chrono>
#include <string>
using namespace std;
 
class QuanLi;

class HangHoa {
	friend QuanLi;
private:
	string _strMaHang;
	string _strTenHang;
	string _strSoLuong;
	string _strDonGia;
	HangHoa* _pNext;
public:
	HangHoa(string, string, string, string);
	void display();
};

HangHoa::HangHoa(string strMaHang, string strTenHang, string strSoLuong, string strDonGia) {
	_strMaHang = strMaHang;
	_strTenHang = strTenHang;
	_strSoLuong = strSoLuong;
	_strDonGia = strDonGia;
	_pNext = NULL;
}

void HangHoa::display() {
	cout << "Ma hang: " << _strMaHang << endl;
	cout << "Ten Hang: " << _strTenHang << endl;
	cout << "So luong: " << _strSoLuong << endl;
	cout << "Don gia: " << _strDonGia << endl;
}

class QuanLi {
private:
	HangHoa* _pFront;
	HangHoa* _pRear;
public:
	QuanLi();
	~QuanLi();

	void xemTatCaHH();
	void xemHangSapXuatKho();
	void themHang();
	void xuat1Hang();

	void app();
	void thoat();
};

QuanLi::QuanLi() {
	_pFront = NULL;
	_pRear = NULL;
}

QuanLi::~QuanLi() {
	HangHoa* pTemp;
	while (_pFront != NULL) {
		pTemp = _pFront;
		_pFront = _pFront->_pNext;
		delete pTemp;
	}
	_pRear = NULL;
}

void QuanLi::xemTatCaHH() {
	HangHoa* p = _pFront;
	while (p != NULL) {
		cout << endl;
		p->display();
		p = p->_pNext;
	}
}
void QuanLi::xemHangSapXuatKho() {
	_pFront->display();
}
void QuanLi::themHang() {
	string strMaHang;
	string strTenHang;
	string strSoLuong;
	string strDonGia;
	cout << "Nhap mat hang can them: " << endl;
	cout << "Nhap ma hang: " ;
	cin >> strMaHang;
	cout << "Nhap ten hang: " ;
	cin.ignore();
	getline(cin, strTenHang);
	cout << "Nhap so luong: " ;
	cin >> strSoLuong;
	cout << "Nhap don gia: " ;
	cin >> strDonGia;
	HangHoa* p = new HangHoa(strMaHang, strTenHang, strSoLuong, strDonGia);
	if (_pRear == NULL) {
		_pFront = _pRear = p;
	}
	else {
		_pRear->_pNext = p;
		_pRear = p;
	}
	cout << "\nDa them hang vao kho";
}
void QuanLi::xuat1Hang() {
	HangHoa* pTemp = _pFront;
	pTemp->display();
	_pFront = _pFront->_pNext;
	delete pTemp;
	if (_pFront == NULL)	_pRear = NULL;
}

void QuanLi::app() {
	system("cls");
	cout << "Cac thao tac quan li kho" << endl;
	cout << "1. Xem tat ca cac hang hoa trong kho" << endl;
	cout << "2. Xem mat hang sap duoc xuat kho" << endl;
	cout << "3. Them mat hang vao kho" << endl;
	cout << "4. Xuat mot mat hang ra khoi kho" << endl;
	cout << "5. Thoat" << endl;
	cout << "Ban hay chon mot thao tac (1->5) : ";
	int iChoice;
	cin >> iChoice;
	system("cls");
	switch (iChoice) {
	case 1:
		if (_pFront == NULL)	cout << "Kho khong co hang";
		else {
			cout << "Cac mat hang trong kho:" << endl;
			xemTatCaHH();
		}
		thoat();
		break;
	case 2:
		if (_pFront == NULL)	cout << "Kho khong co hang";
		else xemHangSapXuatKho();
		thoat();
		break;
	case 3:
		themHang();
		thoat();
		break;
	case 4:
		if (_pFront == NULL)	cout << "Kho khong co hang";
		else xuat1Hang();
		thoat();
		break;
	case 5:
		cout << "Da thoat chuong trinh";
		return;
	default:
		cout << "Ban nhap sai, vui long nhap lai";
		this_thread::sleep_for(chrono::seconds(1));
		app();
		break;
	}
}

void QuanLi::thoat() {
	int iExit;
	do {
		cout << "\nAn phim 1 de ket thuc: ";
		cin >> iExit;
	} while (iExit != 1);
	app();
}

int main() {
	QuanLi khoHang;
	khoHang.app();
	return 0;
}