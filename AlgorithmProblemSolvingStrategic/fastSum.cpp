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
		cout << "n까지의 합을 구할때 n:";
		int n;
		cin >> n;
		//cout << "재귀 함수합:" << ReculsiveSum(n) << endl;
		cout << "분할정복 합:" << FastSum(n) << endl;
		cout << endl;
	}
}*/