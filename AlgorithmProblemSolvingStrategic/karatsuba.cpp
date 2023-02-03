#include<iostream>
#include<vector>
#include"Karatsuba.h"
using namespace std;

void AddTo(vector<int>& a,const vector<int>& b, int count) {
	//더한다음에 10^count만큼 곱하기
	cout << NumberToStr(a) << "+" << NumberToStr(b) << "*10^" << count << "=";
	for (int i = a.size(); i < b.size(); i++) {
		a.push_back(0);
	}
	for (int i = 0; i < b.size(); i++) {
		a[i] += b[i];
	}
	
	Normalize(a);
	vector<int> reversed = ReverseVector(a);
	for (int i = 0; i < count; i++) {
		reversed.push_back(0);
	}
	a = ReverseVector(reversed);
	cout << NumberToStr(a) << endl;
}

void subFrom(vector<int>& a, const vector<int>& b) {
	for (int i = a.size(); i < b.size(); i++) {
		a.push_back(0);
	}
	for (int i = 0; i < b.size(); i++) {
		a[i] = a[i] - b[i];
	}
	Normalize(a);

}

/*int main(void) {
	while (true) {
		vector<int> num1;
		vector<int> num2;
		cout << "곱할 첫번째 수 입력:";
		num1 = GetNumber();
		cout << "곱할 두번째 수 입력:";
		num2 = GetNumber();
		vector<int> multiplied = Multiply(num1, num2);

		cout << "결과값:" << NumberToStr(multiplied) << endl;
		multiplied = KaratsubaAlgorithm(num1, num2);
		cout << "karatsuba:" << NumberToStr(multiplied) << endl << endl;
	}
}*/

vector<int> ReverseVector(const vector<int>& vec) {
	vector<int> reversed;
	for (int i = vec.size() - 1; i >= 0; i--) {
		reversed.push_back(vec[i]);
	}
	return reversed;

}
vector<int> Multiply(const vector<int>& num1, const vector<int>& num2) {
	vector<int> ret(num1.size() + num2.size(), 0);
	for (int i = 0; i < num1.size(); i++) {
		for (int j = 0; j < num2.size(); j++) {
			ret[i + j] += num1[i] * num2[j];
		}
	}
	Normalize(ret);
	return ret;
}
void Normalize(vector<int>& numbers) {
	numbers.push_back(0);
	for (int i = 0; i < numbers.size() - 1; i++) {
		if (numbers[i] < 0) {
			int borrow = (abs(numbers[i]) + 9) / 10;
			numbers[i + 1] -= borrow;
			numbers[i] += borrow * 10;
		}
		else {
			numbers[i + 1] += numbers[i] / 10;
			numbers[i] %= 10;
		}

	}
	while (numbers.size() > 1 && numbers.back() == 0) {
		numbers.pop_back();
	}
}
vector<int> GetNumber() {
	vector<int> ret;
	char ch;
	while ((ch = getchar()) != '\n') {
		if (ch >= '0' && ch <= '9') {
			ret.push_back(ch - '0');
		}
	}
	return ReverseVector(ret);
}
string NumberToStr(const vector<int>& numbers) {
	vector<int> reversed = ReverseVector(numbers);
	string ret;
	for (int i = 0; i < reversed.size(); i++) {
		ret.push_back('0' + reversed[i]);
	}
	return ret;
}


vector<int> KaratsubaAlgorithm(const vector<int>& a, const vector<int>& b) {
	int an = a.size();
	int bn = b.size();
	if (an < bn)return KaratsubaAlgorithm(b, a);
	if (an == 0 || bn == 0) return vector<int>();
	if (an < 2)return Multiply(a, b);
	int half = an / 2;
	
	vector<int> a0(a.begin(), a.begin()+half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(half, b.size()));
	vector<int> b1(b.begin() + min<int>(half, b.size()), b.end());

	vector<int> z0 = KaratsubaAlgorithm(a0, b0);
	vector<int> z2 = KaratsubaAlgorithm(a1, b1);
	AddTo(a0, a1, 0);
	AddTo(b0, b1, 0);
	vector<int> z1 = KaratsubaAlgorithm(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);

	vector<int> ret;
	AddTo(ret, z0, 0);
	AddTo(ret, z1, half);
	AddTo(ret, z2, half + half);
	return ret;

}