#include<iostream>
using namespace std;
int FastSum(int n) {
	if (n == 1) return 1;
	if (n % 2 == 1) return n + FastSum(n - 1);
	return n * n / 4 + 2 * FastSum(n / 2);
}
int RecursiveSum(int n) {
	if (n == 1) {
		return 1;
	}
	return RecursiveSum(n - 1) + n;
}

/*int main(void) {
	while (true) {
		cout << "n������ ���� ���Ҷ� n:";
		int n;
		cin >> n;
		//cout << "��� �Լ���:" << ReculsiveSum(n) << endl;
		cout << "�������� ��:" << FastSum(n) << endl;
		cout << endl;
	}
}*/