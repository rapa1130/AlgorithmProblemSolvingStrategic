#include<iostream>
#include<vector>
using namespace std;

namespace ex {
	void Normalize(vector<int>& numbers);
	vector<int> Multiply(vector<int>& num1, vector<int>& num2);
	vector<int> ReverseVector(const vector<int>& vec);
	vector<int> GetNumber();
	string NumberToStr(const vector<int>& numbers);

	/*int main(void) {
		while (true) {
			vector<int> num1;
			vector<int> num2;
			cout << "곱할 첫번째 수 입력:";
			num1 = GetNumber();
			cout << "곱할 두번째 수 입력:";
			num2 = GetNumber();
			vector<int> multiplied = Multiply(num1, num2);

			cout << "결과값:" << NumberToStr(multiplied) << endl << endl;
		}
	}*/

	vector<int> ReverseVector(const vector<int>& vec) {
		vector<int> reversed;
		for (int i = vec.size() - 1; i >= 0; i--) {
			reversed.push_back(vec[i]);
		}
		return reversed;

	}
	vector<int> Multiply(vector<int>& num1, vector<int>& num2) {
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
			numbers[i + 1] += numbers[i] / 10;
			numbers[i] %= 10;
		}
		while (numbers.back() == 0) {
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
}