#include <iostream>
#include <vector>
using namespace std;

template<class DataType>
class Array {
private:
    int _iSize;
    DataType* _pArr;
public:
    Array();
    Array(int, DataType*);
    ~Array();
    void display();
    void binarySearch(DataType);
};

template<class DataType>
Array<DataType>::Array() {
    _iSize = 0;
    _pArr = new DataType[0];
}

template<class DataType>
Array<DataType>::Array(int _iSize, DataType* pA) {
    this->_iSize = _iSize;
    _pArr = new DataType[_iSize];
    for (int i = 0; i < _iSize; i++) {
        _pArr[i] = pA[i];
    }
}

template<class DataType>
Array<DataType>::~Array() {
    delete[] _pArr;
}

template<class DataType>
void Array<DataType>::display() {
    bool bCheck = false;
    int iSize;
    while (!bCheck) {
        system("cls");
        cout << "Nhap n: ";
        cin >> iSize;
        if (iSize < 1) {
            cout << "Nhap sai, nhan phim enter de nhap lai";
            cin.clear(); // Xóa trạng thái lỗi của cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa phần nhập lỗi khỏi bộ đệm
            cin.get();
        }
        else {
            this->_iSize = iSize;
            _pArr = new DataType[_iSize];
            int iTmp;
            cout << "Nhap cac phan tu cua mang" << endl;
            for (int i = 0; i < _iSize; i++) {
                cin >> iTmp;
                _pArr[i] = iTmp;
            }
            bCheck = true;
        }
    }
    cout << "Nhap phan tu can tim: ";
    DataType x;
    cin >> x;
    binarySearch(x);
}
template<class DataType>
void Array<DataType>::binarySearch(DataType x) {
    int iLeft = 0, iRight = _iSize - 1, iCount = 0;
    vector<int> v;
    while (iLeft <= iRight) {
        int iMid = (iLeft + iRight) / 2;
        if (_pArr[iMid] == x) {
            break;
        }
        else {
            iCount++;
            if (_pArr[iMid] < x)   iLeft = iMid + 1;
            else iRight = iMid - 1;
            v.push_back(iLeft);
            v.push_back(iRight);
        }
    }
    cout << "So lan chia doi mang la: " << iCount << endl;
    for (int i = 0; i <= iCount; i += 2) {
        cout << "Lan " << i / 2 << " : x = " << x << " nam trong doan[" << v[i] << ".." << v[i + 1] << "]" << endl;
    }
}

int main() {
    Array<int> a;
    a.display();
    return 0;
}