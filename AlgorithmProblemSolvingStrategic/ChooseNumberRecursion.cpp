#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;

void PrintNumbers(int* numArr,int size) {
	cout << "[";
	for (int i = 0; i < size; i++) {
		cout << numArr[i];
		if (i != size-1)
			cout << ", ";
	}
	cout << "]" << endl;
}
void PrintNumbers(stack<int> selected) {
	int size= selected.size();
	int* arr = new int[size];
	for (int index = size - 1; index >= 0; index--) {
		arr[index] = selected.top();
		selected.pop();
	}
	PrintNumbers(arr, size);
}
//n���� ���� 4���� ���� ���տ� ���� ��� ����� ���� ����ϴ� �˰���

void SelectNumber(int n, int choose, stack<int> selected) {
	if (selected.size() >= choose) {
		PrintNumbers(selected);
		return;
	}
	int first = selected.empty() ? 0 : selected.top() + 1;
	for (int i = first; i <= n; i++) {
		selected.push(i);
		SelectNumber(n, choose, selected);
		selected.pop();
	}
}

/*int main(void) {
	cout << "[0���� N������ ���� K���� ����ִ� ���α׷�]" << endl;

	int n, k;
	cout << "N�� �Է� :";
	cin >> n;
	cout << "K�� �Է� :";
	cin >> k;
	stack<int> stk = stack<int>();
	SelectNumber(n, k, stk);
}*/