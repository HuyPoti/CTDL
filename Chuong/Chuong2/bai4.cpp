#include <iostream>
#include <chrono>
#include <thread>
#include <string>
using namespace std;

const int MAX_MONHOC = 100;
bool bDaNhap = false;

struct MONHOC {
	string strMaMon;
	string strTenMon;
	int iSoTinChi;
	double dDiem;
};
class SV {
private:
	string _strMssv;
	string _strHoTen;
	string _strNgaySinh;
	int _iSoMonHoc;
	MONHOC _pMh[MAX_MONHOC];
public:
	SV() {
		_strMssv = "";
		_strHoTen = "";
		_strNgaySinh = "";
		_iSoMonHoc = 0;
	}
	~SV() {};
	void setMssv(string strMssv) {
		_strMssv = strMssv;
	}
	string getMssv() {
		return _strMssv;
	}
	void setHoTen(string strHoTen) {
		_strHoTen = strHoTen;
	}
	string getHoTen() {
		return _strHoTen;
	}
	void setNgaySinh(string strNgaySinh) {
		_strNgaySinh = strNgaySinh;
	}
	string getNgaySinh() {
		return _strNgaySinh;
	}
	void setSoMonHoc(int iSoMonHoc) {
		_iSoMonHoc = iSoMonHoc;
	}
	int getSoMonHoc() {
		return _iSoMonHoc;
	}
	void setMonHoc(string strMaMon, string strTenMon, int iSoTinChi, double dDiem, int i) {
		_pMh[i].strMaMon = strMaMon;
		_pMh[i].strTenMon = strTenMon;
		_pMh[i].iSoTinChi = iSoTinChi;
		_pMh[i].dDiem = dDiem;
	}
	string getMaMon(int i) {
		return _pMh[i].strMaMon;
	}
	string getTenMon(int i) {
		return _pMh[i].strTenMon;
	}
	int getSoTinChi(int i) {
		return _pMh[i].iSoTinChi;
	}
	double getDiem(int i) {
		return _pMh[i].dDiem;
	}
};
class App {
private:
	int _iSize;
	SV* _pSv;
public:
	App() {
		_iSize = 0;
		_pSv = new SV[0];
	}
	~App() {
		delete[] _pSv;
	}

	void quickSort(int, int);

	void nhapDanhSach();
	void display();
	void linearSearch_2();
	void insertionSort_3();
	void binarySearch_4();
	void selectionSort_5();
	void scholar_6();
	void quickSort_7();
	void print_8();
};
int main() {
	App app;
	app.display();
}
void App::quickSort(int iLeft, int iRight) {
	SV x;
	int i, j;
	if (iLeft >= iRight)	return;
	x = _pSv[(iLeft + iRight) / 2];
	i = iLeft; j = iRight;
	while (i < j) {
		while (_pSv[i].getNgaySinh().substr(_pSv[i].getNgaySinh().length() - 4) < x.getNgaySinh().substr(x.getNgaySinh().length() - 4))	i++;
		while (_pSv[j].getNgaySinh().substr(_pSv[j].getNgaySinh().length() - 4) > x.getNgaySinh().substr(x.getNgaySinh().length() - 4))	j--;
		while (_pSv[i].getNgaySinh().substr(_pSv[i].getNgaySinh().length() - 4) < x.getNgaySinh().substr(x.getNgaySinh().length() - 4))	i++;
		while (_pSv[j].getNgaySinh().substr(_pSv[j].getNgaySinh().length() - 4) > x.getNgaySinh().substr(x.getNgaySinh().length() - 4))	j--;
		if (i <= j) {
			SV tmp;
			tmp = _pSv[i];
			_pSv[i] = _pSv[j];
			_pSv[j] = tmp;
			i++; j--;
		}
	}
	quickSort(iLeft, j);
	quickSort(i, iRight);
}
void App::nhapDanhSach() {
	system("cls");
	bDaNhap = true;
	string strTmp;
	int iInput;
	int iSize;
	delete[] _pSv;
	cout << "Nhap so luong sinh vien: ";
	cin >> iSize;
	_iSize = iSize;
	_pSv = new SV[_iSize];
	for (int i = 0; i < _iSize; i++) {
		do {
			cout << "Nhap ma so sinh vien: ";
			cin >> strTmp;
			cout << endl;
		} while (strTmp.length() != 11);
		_pSv[i].setMssv(strTmp);
		cout << "Nhap ho ten: ";
		cin.ignore();
		getline(cin, strTmp);
		_pSv[i].setHoTen(strTmp);
		cout << endl;
		cout << "Nhap ngay sinh: ";
		cin >> strTmp;
		_pSv[i].setNgaySinh(strTmp);
		cout << endl;
		cout << "Nhap so mon hoc: ";
		cin >> iInput;
		_pSv[i].setSoMonHoc(iInput);
		cout << endl;
		cout << "Nhap danh sach cac mon hoc:" << endl;
		for (int j = 0; j < _pSv[i].getSoMonHoc(); j++) {
			string strMaMon, strTenMon;
			int iSoTinChi;
			double dDiem;
			cout << "Nhap ma mon: ";
			cin >> strMaMon;
			cout << endl;
			cout << "Nhap ten mon: ";
			cin.ignore();
			getline(cin, strTenMon);
			cout << endl;
			do {
				cout << "Nhap so tin chi: ";
				cin >> iSoTinChi;
				cout << endl;
			} while (iSoTinChi > 5 || iSoTinChi < 0);
			do {
				cout << "Nhap diem: ";
				cin >> dDiem;
				cout << endl;
			} while (dDiem < 0 || dDiem > 10);
			_pSv[i].setMonHoc(strMaMon, strTenMon, iSoTinChi, dDiem, j);
		}
	}
	cout << "Ban da nhap xong, nhan phim 1 de thoat" << endl;
	while (cin >> iInput) {
		if (iInput == 1)	break;
	}
	display();
}
void App::linearSearch_2() {
	system("cls");
	cout << "Nhap ma so sinh vien: ";
	string strMssv;
	cin >> strMssv;
	cout << endl << "Nhap ho ten se thay the: ";
	string strChangeht;
	cin.ignore();
	getline(cin, strChangeht);
	for (int i = 0; i < _iSize; i++) {
		if (_pSv[i].getMssv() == strMssv) {
			_pSv[i].setHoTen(strChangeht);
			break;
		}
	}
	int iInput;
	cout << "Da tim kiem va thay doi ten xong, nhan phim 1 de thoat" << endl;
	while (cin >> iInput) {
		if (iInput == 1)	break;
	}
	display();
}
void App::insertionSort_3() {
	system("cls");
	SV tmp;
	int j;
	for (int i = 1; i < _iSize; i++) {
		tmp = _pSv[i];
		for (j = i; (j > 0) && (_pSv[j - 1].getHoTen() < tmp.getHoTen()); j--) {
			_pSv[j] = _pSv[j - 1];
		}
		_pSv[j] = tmp;
	}
	print_8();
}
void App::binarySearch_4() {
	system("cls");
	SV tmp;
	int j;
	string strHoTen;
	cout << "Nhap ho ten sinh vien can tim: ";
	cin.ignore();
	getline(cin, strHoTen);
	for (int i = 1; i < _iSize; i++) {
		tmp = _pSv[i];
		for (j = i; (j > 0) && (_pSv[j - 1].getHoTen() > tmp.getHoTen()); j--) {
			_pSv[j] = _pSv[j - 1];
		}
		_pSv[j] = tmp;
	}
	int iLeft = 0, iRight = _iSize - 1, iMid;
	while (iLeft <= iRight) {
		iMid = (iLeft + iRight) / 2;
		if (_pSv[iMid].getHoTen() == strHoTen) {
			break;
		}
		if (_pSv[iMid].getHoTen() < strHoTen) {
			iLeft = iMid + 1;
		}
		else {
			iRight = iMid - 1;
		}
	}
	for (int i = iMid; i < _iSize - 1; i++) {
		_pSv[i] = _pSv[i + 1];
	}
	_iSize--;
	int iInput;
	cout << "Da tim kiem va xoa ten sinh vien khoi danh sach, nhan phim 1 de thoat" << endl;
	while (cin >> iInput) {
		if (iInput == 1)	break;
	}
	display();
}
void App::selectionSort_5() {
	system("cls");
	double* pDiem = new double[_iSize];
	for (int i = 0; i < _iSize; i++) {
		double sum = 0;
		int iSum = 0;
		for (int j = 0; j < _pSv[i].getSoMonHoc(); j++) {
			sum += _pSv[i].getDiem(j) * _pSv[i].getSoTinChi(j);
			iSum += _pSv[i].getSoTinChi(j);
		}
		sum = sum / iSum;
		pDiem[i] = sum;
	}
	int iMin;
	for (int i = 0; i < _iSize - 1; i++) {
		iMin = i;
		for (int j = i + 1; j < _iSize; j++) {
			if (pDiem[iMin] > pDiem[j]) {
				iMin = j;
			}
		}
		if (iMin != i) {
			swap(pDiem[iMin], pDiem[i]);
			SV tmp = _pSv[iMin];
			_pSv[iMin] = _pSv[i];
			_pSv[i] = tmp;
		}
	}
	int iInput;
	cout << "Da sap xep xong, nhan phim 1 de thoat" << endl;
	while (cin >> iInput) {
		if (iInput == 1)	break;
	}
	display();
}
void App::scholar_6() {
	system("cls");
	double* pDiem = new double[_iSize];
	for (int i = 0; i < _iSize; i++) {
		double sum = 0;
		bool bCheck = true;
		int iSum = 0;
		for (int j = 0; j < _pSv[i].getSoMonHoc(); j++) {
			if (_pSv[i].getDiem(j) < 5) {
				bCheck = false;
			}
			sum += _pSv[i].getDiem(j) * _pSv[i].getSoTinChi(j);
			iSum += _pSv[i].getSoTinChi(j);
		}
		sum = sum / iSum;
		if (!bCheck)	sum = 0;
		pDiem[i] = sum;
	}
	for (int i = 0; i < _iSize; i++) {
		if (pDiem[i] >= 7) {
			cout << _pSv[i].getHoTen() << endl;
		}
	}
	int iInput;
	cout << "Da in danh sach, nhan phim 1 de thoat" << endl;
	while (cin >> iInput) {
		if (iInput == 1)	break;
	}
	display();
}
void App::quickSort_7() {
	system("cls");
	quickSort(0, _iSize - 1);
	int iInput;
	cout << "Da tim kiem va thay doi ten xong, nhan phim 1 de thoat" << endl;
	while (cin >> iInput) {
		if (iInput == 1)	break;
	}
	display();
}
void App::print_8() {
	system("cls");
	for (int i = 0; i < _iSize; i++) {
		cout << i + 1 << "." << endl;
		cout << "MSSV: " << _pSv[i].getMssv() << endl;
		cout << "Ho ten: " << _pSv[i].getHoTen() << endl;
		cout << "Ngay sinh: " << _pSv[i].getNgaySinh() << endl;
		cout << "Danh sach cac mon hoc" << endl;
		cout << endl;
		for (int j = 0; j < _pSv[i].getSoMonHoc(); j++) {
			cout << "	Ma mon: " << _pSv[i].getMaMon(j) << endl;
			cout << "	Ten mon: " << _pSv[i].getTenMon(j) << endl;
			cout << "	So tin chi: " << _pSv[i].getSoTinChi(j) << endl;
			cout << "	Diem: " << _pSv[i].getDiem(j) << endl;
			cout << endl;
		}
	}
	int iInput;
	cout << "Da xuat xong danh sach, nhan phim 1 de thoat" << endl;
	while (cin >> iInput) {
		if (iInput == 1)	break;
	}
	display();
}
void App::display() {
	int choice;
	while (true) {
		system("cls");
		cout << "1. Nhap danh sach sinh vien" << endl;
		cout << "2. Tim kiem va sua ho ten" << endl;
		cout << "3. Sap xep danh sach sinh vien giam dan theo ho ten" << endl;
		cout << "4. Tim va xoa sinh vien khoi danh sach" << endl;
		cout << "5. Sap xep danh sach sinh vien tang dan theo diem trung binh" << endl;
		cout << "6. In danh sach hoc bong" << endl;
		cout << "7. Sap xep danh sach sinh vien tang dan theo nam sinh" << endl;
		cout << "8. In danh sach" << endl;
		cout << "Ban chon: ";
		cin >> choice;
		if (choice != 1) {
			if (bDaNhap) {
				break;
			}
			else {
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
		insertionSort_3();
		break;
	case 4:
		binarySearch_4();
		break;
	case 5:
		selectionSort_5();
		break;
	case 6:
		scholar_6();
		break;
	case 7:
		quickSort_7();
		break;
	case 8:
		print_8();
		break;
	default:
		nhapDanhSach();
		break;
	}
}