#include<iostream>
#include<vector>
#include<algorithm>
#include"karatsuba2.h"

using namespace std;

void normalize(vector<int>& num) {
	num.push_back(0);
	num.push_back(0);
	for (int i = 0; i < num.size() - 1; i++) {
		int value = num[i];
		if (num[i] < 0) {
			int borrow = (abs(num[i]) + 9) / 10;
			num[i + 1] -= borrow;
			num[i] += borrow * 10;
		}
		else {
			num[i + 1] += num[i] / 10;
			num[i] %= 10;
		}
	}

	while (num.size()>0&& num.at(num.size() - 1) == 0) {
		num.pop_back();
	}
}

void SubFrom(vector<int>& to, vector<int>& from) {
	/*for (int i = to.size(); i < from.size(); i++) {
		to.push_back(0);
	}*/
	for (int i = 0; i < from.size(); i++) {
		to[i] -= from[i];
	}
	//normalize(to);
	/*while (to.size() > 0 && to.at(to.size() - 1) == 0) {
		to.pop_back();
	}*/
}

void AddTo(vector<int>& to, vector<int> from, int digit) {
	reverse(from.begin(), from.end());
	while (digit-->0) {
		from.push_back(0);
	}
	reverse(from.begin(), from.end());

	for (int i = to.size(); i < from.size(); i++) {
		to.push_back(0);
	}	
	for (int i = 0; i < from.size(); i++) {
		to[i] += from[i];
	}
	//normalize(to);
	/*while (to.size() > 0&& to.at(to.size() - 1) == 0) {
		to.pop_back();
	}*/
}

vector<int> karatsuba(vector<int>& a,vector<int>& b) {
	if (a.size() < b.size()) {
		return karatsuba(b, a);
	}
	if (a.size() == 1 ) {
		vector<int> ret;
		ret.push_back(a[0] * b[0]);
		return ret;
	}
	int half = a.size() / 2;
	vector<int> a1(a.begin(), a.begin() + half);
	vector<int> a0(a.begin() + half, a.end());
	vector<int> b1(b.begin(), b.begin() + min<int>(half,b.size()));
	vector<int> b0(b.begin() + min<int>(half, b.size()), b.end());

	vector<int> z0 = karatsuba(a0, b0);
	vector<int> z2 = karatsuba(a1, b1);

	AddTo(a0, a1, 0);
	AddTo(b0, b1, 0);
	vector<int> z1 = karatsuba(a0, b0);
	SubFrom(z1, z0);
	SubFrom(z1, z2);

	vector<int> ret;
	AddTo(ret, z0, half + half);
	AddTo(ret, z1, half);
	AddTo(ret, z2, 0);
	return ret;
}
void PrintVector(const vector<int>& num) {
	cout << "[";
	for (auto iter = num.begin(); iter != num.end(); iter++) {
		cout << *iter;
		if (iter != num.end()-1) {
			cout << ", ";

		}
	}
	cout << "]";
	cout << endl;
}

/*int main(void) {
	vector<int> num1 = { 1,2,3,4};
	vector<int> num2 = { 1,2 ,3,4};
	vector<int> ret = karatsuba(num1, num2);
	PrintVector(ret);
}*/