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
//n개의 수중 4가지 수의 조합에 대한 모든 경우의 수를 출력하는 알고리즘

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
	cout << "[0부터 N까지의 수중 K개를 골라주는 프로그램]" << endl;

	int n, k;
	cout << "N을 입력 :";
	cin >> n;
	cout << "K를 입력 :";
	cin >> k;
	stack<int> stk = stack<int>();
	SelectNumber(n, k, stk);
}*/