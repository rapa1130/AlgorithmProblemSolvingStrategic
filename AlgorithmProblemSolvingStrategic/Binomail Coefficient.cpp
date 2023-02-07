#include<iostream>
#include<utility>
#include<map>

using namespace std;


map<pair<int, int>, unsigned long> cash;

template<typename T>
T bino(int n, int r) {
	if (r == 0 || r == n) {
		return 1;
	}
	if (cash[pair<int,int>(n,r)]!=0) {
		return cash[pair<int, int>(n, r)];
	}
	T result = bino<T>(n - 1, r) + bino<T>(n - 1, r - 1);
	cash[pair<int, int>(n, r)] = result;
	return result;
}


/*int main(void) {
	while (true) {
		int n, r;
		cout << "n입력:";
		cin >> n;
		cout << "r입력:";
		cin >> r;
		cout << n << "C" << r << " : " << bino<unsigned long>(n, r) << endl;
	}
}*/