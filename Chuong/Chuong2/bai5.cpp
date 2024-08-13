#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

bool bDaNhap = false;

class Sach {
private:
	string _strMaSach;
	string _strTuaSach;
	int _iNam;
	long _lGia;
public:
	Sach() {
		_strMaSach = "";
		_strTuaSach = "";
		_iNam = 1901;
		_lGia = 0;
	}
	~Sach() {}
	void setMaSach(string strMaSach) {
		_strMaSach = strMaSach;
	}
	string getMaSach() {
		return _strMaSach;
	}
	void setTuaSach(string strTuaSach) {
		_strTuaSach = strTuaSach;
	}
	string getTuaSach() {
		return _strTuaSach;
	}
	void setNam(int iNam) {
		_iNam = iNam;
	}
	int getNam() {
		return _iNam;
	}
	void setGia(long lGia) {
		_lGia = lGia;
	}
	long long getGia() {
		return _lGia;
	}
	void nhap() {
		int iCount = 0;
		do {
			if (iCount == 0) {
				cout << "Nhap ma sach: ";
			}
			else {
				cout << "Ban nhap khong dung, vui long nhap lai ma sach: ";
			}
			iCount++;
			cin >> _strMaSach;
			cout << endl;
		} while (_strMaSach.length() > 6);
		iCount = 0;
		cin.ignore();
		do {
			if (iCount == 0) {
				cout << "Nhap tua sach: ";
			}
			else {
				cout << "Ban nhap khong dung, vui long nhap lai tua sach: ";
			}
			iCount++;
			getline(cin, _strTuaSach);
			cout << endl;
		} while (_strTuaSach.length() > 30);
		iCount = 0;
		do {
			if (iCount == 0) {
				cout << "Nhap nam xuat ban sach: ";
			}
			else {
				cout << "Ban nhap khong dung, vui long nhap lai nam xuat ban sach: ";
			}
			cin >> _iNam;
			cout << endl;
			iCount++;
		} while (_iNam <= 1900);
		iCount = 0;
		do {
			if (iCount == 0) {
				cout << "Nhap gia tien cua sach: ";
			}
			else {
				cout << "Ban nhap khong dung, vui long nhap gia tien cua sach: ";
			}
			cin >> _lGia;
			cout << endl;
			iCount++;
		} while (_lGia / 1000000 > 0);
	}
	void xuat() {
		cout << "Ma sach: " << _strMaSach << endl;
		cout << "Tua sach: " << _strTuaSach << endl;
		cout << "Nam xuat ban: " << _iNam << endl;
		cout << "Gia sach: " << _lGia << endl;
		cout << endl;
	}
};

class App {
private:
	int _iSize;
	Sach* _pSach;
public:
	App() {
		_iSize = 0;
		_pSach = new Sach[0];
	}
	~App() { delete[] _pSach; }
	void quickSort(int, int);
	void nhapDanhSach_1();
	void linearSearch_2();
	void binarySearch_3();
	void selectionSort_4();
	void insertionSort_5();
	void bubbleSort_6();
	void quickSort_7();
	void xuatDanhSach_8();
	void display();
};

int main() {
	App app;
	app.display();
}

void App::quickSort(int iLeft, int iRight) {
	Sach x;
	int i, j;
	if (iLeft >= iRight)	return;
	x = _pSach[(iLeft + iRight) / 2];
	i = iLeft; j = iRight;
	while (i < j) {
		while (_pSach[i].getGia() > x.getGia())	i++;
		while (_pSach[j].getGia() < x.getGia())	j--;
		if (i <= j) {
			Sach tmp;
			tmp = _pSach[i];
			_pSach[i] = _pSach[j];
			_pSach[j] = tmp;
			i++; j--;
		}
	}
	quickSort(iLeft, j);
	quickSort(i, iRight);
}
void App::nhapDanhSach_1() {
	system("cls");
	bDaNhap = true;
	cout << "Nhap so luong cuon sach trong thu vien: ";
	cin >> _iSize;
	cout << endl;
	delete[] _pSach;
	_pSach = new Sach[_iSize];
	for (int i = 0; i < _iSize; i++) {
		cout << i + 1 << ". ";
		_pSach[i].nhap();
	}
	int iInput;
	cout << "Da nhap danh sach xong, nhan phim 1 de thoat" << endl;
	while (cin >> iInput) {
		if (iInput == 1)	break;
	}
	display();
}
void App::linearSearch_2() {
	system("cls");
	string strTmp;
	cout << "Nhap tua sach can sua: ";
	cin.ignore();
	getline(cin, strTmp);
	cout << "Nhap gia moi: ";
	long iChange;
	cin >> iChange;
	for (int i = 0; i < _iSize; i++) {
		if (_pSach[i].getTuaSach() == strTmp) {
			_pSach[i].setGia(iChange);
			break;
		}
	}
	int iInput;
	cout << "Da tim kiem va thay doi gia sach xong, nhan phim 1 de thoat" << endl;
	while (cin >> iInput) {
		if (iInput == 1)	break;
	}
	display();
}
void App::binarySearch_3() {
	system("cls");
	cout << "Nhap ma sach cua cuon sach can xoa: ";
	string strMaSach;
	cin >> strMaSach;
	Sach tmp;
	int j;
	for (int i = 1; i < _iSize; i++) {
		tmp = _pSach[i];
		for (j = i; (j > 0) && (_pSach[j - 1].getMaSach() > tmp.getMaSach()); j--) {
			_pSach[j] = _pSach[j - 1];
		}
		_pSach[j] = tmp;
	}
	int iLeft = 0, iRight = _iSize - 1, iMid;
	while (iLeft <= iRight) {
		iMid = (iLeft + iRight) / 2;
		if (_pSach[iMid].getMaSach() == strMaSach) {
			for (int i = iMid; i < _iSize - 1; i++) {
				_pSach[i] = _pSach[i + 1];
			}
			_iSize--;
			break;
		}
		else if (_pSach[iMid].getMaSach() > strMaSach)	iRight = iMid - 1;
		else iLeft = iMid + 1;
	}
	int iInput;
	cout << "Da tim kiem va xoa cuon sach xong, nhan phim 1 de thoat" << endl;
	while (cin >> iInput) {
		if (iInput == 1)	break;
	}
	display();
}
void App::selectionSort_4() {
	system("cls");
	int iMin;
	for (int i = 0; i < _iSize - 1; i++) {
		iMin = i;
		for (int j = i + 1; j < _iSize; j++) {
			if (_pSach[iMin].getMaSach() > _pSach[j].getMaSach()) {
				iMin = j;
			}
		}
		if (iMin != i) {
			Sach tmp = _pSach[iMin];
			_pSach[iMin] = _pSach[i];
			_pSach[i] = tmp;
		}
	}
	int iInput;
	cout << "Da sap xep xong, nhan phim 1 de thoat" << endl;
	while (cin >> iInput) {
		if (iInput == 1)	break;
	}
	display();
}
void App::insertionSort_5() {
	system("cls");
	Sach tmp;
	int j;
	for (int i = 1; i < _iSize; i++) {
		tmp = _pSach[i];
		for (j = i; (j > 0) && (_pSach[j - 1].getNam() < tmp.getNam()); j--) {
			_pSach[j] = _pSach[j - 1];
		}
		_pSach[j] = tmp;
	}
	int iInput;
	cout << "Da sap xep xong, nhan phim 1 de thoat" << endl;
	while (cin >> iInput) {
		if (iInput == 1)	break;
	}
	display();
}
void App::bubbleSort_6() {
	system("cls");
	for (int i = 0; i < _iSize - 1; i++) {
		for (int j = _iSize - 1; j > i; j--) {
			if (_pSach[j].getTuaSach() < _pSach[j - 1].getTuaSach()) {
				Sach tmp = _pSach[j];
				_pSach[j] = _pSach[j - 1];
				_pSach[j - 1] = tmp;
			}
		}
	}
	int iInput;
	cout << "Da sap xep xong, nhan phim 1 de thoat" << endl;
	while (cin >> iInput) {
		if (iInput == 1)	break;
	}
	display();
}
void App::quickSort_7() {
	system("cls");
	quickSort(0, _iSize - 1);
	int iInput;
	cout << "Da sap xep xong, nhan phim 1 de thoat" << endl;
	while (cin >> iInput) {
		if (iInput == 1)	break;
	}
	display();
}
void App::xuatDanhSach_8() {
	system("cls");
	for (int i = 0; i < _iSize; i++) {
		cout << i + 1 << ". ";
		_pSach[i].xuat();
	}
	int iInput;
	cout << "Da in danh sach xong, nhan phim 1 de thoat" << endl;
	while (cin >> iInput) {
		if (iInput == 1)	break;
	}
	display();
}
void App::display() {
	int choice;
	while (true) {
		system("cls");
		cout << "1. Nhap danh sach cac cuon sach trong thu vien" << endl;
		cout << "2. Tim kiem va sua gia cua cuon sach" << endl;
		cout << "3. Tim kiem va xoa cuon sach" << endl;
		cout << "4. Sap xep danh sach tang dan theo ma sach" << endl;
		cout << "5. Sap xep danh sach giam dan theo nam xuat ban" << endl;
		cout << "6. Sap xep danh sach tang dan theo tua sach" << endl;
		cout << "7. Sap xep danh sach tang dan theo gia" << endl;
		cout << "8. In danh sach cac cuon sach trong thu vien" << endl;
		cout << "Ban chon: ";
		cin >> choice;
		if (choice != 1) {
			if (bDaNhap) {
				break;
			}
			else {
				cout << endl;
				cout << "Nhap danh sach truoc";
				this_thread::sleep_for(std::chrono::seconds(1));
				continue;
			}
		}
		else {
			break;
		}
	}
	switch (choice) {
	case 2:
		linearSearch_2();
		break;
	case 3:
		binarySearch_3();
		break;
	case 4:
		selectionSort_4();
		break;
	case 5:
		insertionSort_5();
		break;
	case 6:
		bubbleSort_6();
		break;
	case 7:
		quickSort_7();
		break;
	case 8:
		xuatDanhSach_8();
		break;
	default:
		nhapDanhSach_1();
		break;
	}
}