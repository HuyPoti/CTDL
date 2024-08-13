#include <iostream>
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
    void linearSearch(DataType);
    void print();
};

template<class DataType>
Array<DataType>::Array() {}

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
    linearSearch(x);
}
template<class DataType>
void Array<DataType>::linearSearch(DataType data) {
    cout << "Vi tri cua phan tu trong mang:" << endl;
    for (int i = 0; i < _iSize; i++) {
        if (_pArr[i] == data)  cout << i << " ";
    }
}

template<class DataType>
void Array<DataType>::print() {
    cout << "Cac phan tu trong mang:" << endl;
    for (int i = 0; i < _iSize; i++) {
        cout << _pArr[i] << " ";
    }
    cout << endl;
}

int main() {
    Array<int> a;
    a.display();
    return 0;
}