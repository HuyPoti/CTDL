#include <iostream>
using namespace std;

template<class DataType>
class Stack;

template<class DataType>
class Node {
	friend Stack<DataType>;
private:
	DataType _data;
	Node* _pNext;
public:
	Node(DataType data);
	void display();
};

template<class DataType>
Node<DataType>::Node(DataType data) {
	_data = data;
	_pNext = NULL;
}

template<class DataType>
void Node<DataType>::display() {
	cout << _data << endl;
}

template<class DataType>
class Stack {
private:
	Node<DataType>* _pTop;
	int _iSize;
public:
	Stack();
	~Stack();

	bool isEmpty();
	void push(DataType data);
	DataType pop();
	DataType peek();
	void display();
	void clear();
	int getSize();
};

template<class DataType>
Stack<DataType>::Stack() {
	_pTop = NULL;
	_iSize = 0;
}

template<class DataType>
Stack<DataType>::~Stack() {
	clear();
}

template<class DataType>
bool Stack<DataType>::isEmpty() {
	return (_pTop == NULL);
}

template<class DataType>
void Stack<DataType>::push(DataType data) {
	Node<DataType>* pTemp = new Node<DataType>(data);
	pTemp->_pNext = _pTop;
	_pTop = pTemp;
	_iSize++;
}

template<class DataType>
DataType Stack<DataType>::pop() {
	if (isEmpty()) {
		exit;
	}
	Node<DataType>* pTemp = _pTop;
	DataType temp = pTemp->_data;
	_pTop = pTemp->_pNext;
	delete pTemp;
	_iSize--;
	return temp;
}

template<class DataType>
DataType Stack<DataType>::peek() {
	if (isEmpty()) {
		exit;
	}
	return _pTop->_data;
}

template<class DataType>
void Stack<DataType>::display() {
	if (isEmpty()) {
	}
	else {
		for (Node<DataType>* p = _pTop; p != NULL; p = p->_pNext) {
			p->display();
		}
	}
}

template<class DataType>
void Stack<DataType>::clear() {
	Node<DataType>* pTemp;
	while (_pTop != NULL) {
		pTemp = _pTop;
		_pTop = pTemp->_pNext;
		delete pTemp;
	}
	_iSize = 0;
}

template<class DataType>
int Stack<DataType>::getSize() {
	return _iSize;
}

int main() {
	Stack<char> s;
	string strNgoac;
	int iExit;
	do {
		system("cls");
		cout << "Nhap chuoi xau ngoac: ";
		cin >> strNgoac;
		for (char cIndex : strNgoac) {
			if (s.isEmpty())	s.push(cIndex);
			else if ((s.peek() == '[' && cIndex == ']') || (s.peek() == '{' && cIndex == '}') || (s.peek() == '(' && cIndex == ')')) {
				s.pop();
			}
			else s.push(cIndex);
		}
		cout << "\nXau ngoac co phai la xau ngoac dung khong (true /false)? : ";
		if (s.isEmpty())	cout << "true" << endl;
		else cout << "false" << endl;
		cout << "\nAn phim 1 de tiep tuc chuong trinh: ";
		cin >> iExit;
	} while (iExit == 1);
}