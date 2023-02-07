#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;
namespace FANMEETING {

	void SubFrom(vector<int>& to, vector<int>& from) {
		for (int i = 0; i < from.size(); i++) {
			to[i] -= from[i];
		}
	}
	void addTo(vector<int>& a, vector<int>& b, int k) {
		int newsize = a.size() < b.size() + k ? b.size() + k : a.size();
		while (a.size() != newsize) a.push_back(0);
		for (int i = k; i < newsize; i++) {
			a[i] = a[i] + b[i - k];
		}
	}
	void AddTo(vector<int>& a, const vector<int>& b, int k) {
		int newSize = b.size() + k;
		while (a.size() < newSize)a.push_back(0);
		for (int i = k; i < newSize; i++) {
			a[i] += b[i - k];
		}
	}

	/*void AddTo(vector<int>& to, vector<int>& from, int digit) {
		reverse(from.begin(), from.end());
		while (digit-- > 0) {
			from.push_back(0);
		}
		reverse(from.begin(), from.end());

		for (int i = to.size(); i < from.size(); i++) {
			to.push_back(0);
		}
		for (int i = 0; i < from.size(); i++) {
			to[i] += from[i];
		}
	}*/
	vector<int> Multiply(const vector<int>& a,const vector<int>& b) {
		vector<int> ret;
		ret.resize(a.size() + b.size() + 1);
		for (int i = 0; i < a.size(); i++) {
			for (int j = 0; j < b.size(); j++) {
				ret[i + j] += a[i] * b[j];
			}
		}
		return ret;
	}

	vector<int> karatsuba(vector<int>& a, vector<int>& b) {
		int an = a.size();
		int bn = b.size();
		if (an < bn) {
			return karatsuba(b, a);
		}
		if (an == 0 || bn == 0) return vector<int>();
		if (a.size() < 100) {
			return Multiply(a, b);
		}
		int half = an / 2;
		vector<int> a1(a.begin(), a.begin() + half);
		vector<int> a0(a.begin() + half, a.end());
		vector<int> b1(b.begin(), b.begin() + min<int>(half,bn));
		vector<int> b0(b.begin() + min<int>(half, bn), b.end());

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
	vector<int> StrToVector(const string& str) {
		vector<int> ret;
		for (auto iter = str.begin(); iter != str.end(); iter++) {
			if (*iter == 'M') {
				ret.push_back(1);
			}
			else {
				ret.push_back(0);
			}
		}
		return ret;
	}

	
}
int GetHugCount(const string& idol, const string& fan);
vector<string> RecursiveTestcase(string& now, const int size);
void PrintVector2(const vector<string>& vec);

/*int main(void) {
	for (int i = 4; i < 5; i++) {
		for (int m = 5; m < 6; m++) {
			string now;
			vector<string> idol = RecursiveTestcase(now, i);
			now.clear();
			vector<string> fan = RecursiveTestcase(now, m);
			now.clear();
			for (int j = 0; j < idol.size(); j++) {
				for (int k = 0; k < fan.size(); k++) {
					int count = GetHugCount(idol[j], fan[k]);
					cout << "idol: " << idol[j] << endl;
					cout << "fan: " << fan[k] << endl;
					cout << "count:" << count << endl;
					cout << endl;
				}
			}
		}
		
	}
}*/


/*int main(void) {
	string idol, fan;
	for (int i = 0; i < 100000; i++) {
		idol.push_back('M');
	}
	for (int j = 0; j < 200000; j++) {
		fan.push_back('F');
	}
	int count=GetHugCount(idol, fan);
	cout << "count:" << count;
}*/

/*int main(void) {
	int testcase; cin >> testcase;
	while (testcase-- > 0) {
		string idol;
		string fan;
		cin >> idol >> fan;
		vector<int> idolVec =FANMEETING::StrToVector(idol);
		vector<int> fanVec = FANMEETING::StrToVector(fan);
		reverse(idolVec.begin(), idolVec.end());
		vector<int> ret = FANMEETING::karatsuba(fanVec, idolVec);
		int count = 0;
		for (int i = idol.size() - 1; i < fan.size(); i++) {
			if (ret[i] == 0) {
				count++;
			}
		}
		cout << count << endl;
	}
	return 0;

}*/


vector<string> RecursiveTestcase(string& now, const int size) {
	vector<string> ret;

	if (now.size() > size) {
		ret.push_back(now);
		return ret;
	}
	vector<string> result;

	now.push_back('F');
	result = RecursiveTestcase(now, size);
	ret.insert(ret.begin(), result.begin(), result.end());
	now.pop_back();
	now.push_back('M');
	result = RecursiveTestcase(now, size);
	ret.insert(ret.begin(), result.begin(), result.end());
	now.pop_back();

	return ret;
}
int GetHugCount(const string& idol, const string& fan) {
	vector<int> idolVec = FANMEETING::StrToVector(idol);
	vector<int> fanVec = FANMEETING::StrToVector(fan);
	reverse(idolVec.begin(), idolVec.end());
	vector<int> ret = FANMEETING::karatsuba(fanVec, idolVec);
	int count = 0;
	for (int i = idol.size() - 1; i < fan.size(); i++) {
		if (ret[i] == 0) {
			count++;
		}
	}
	return count;
}

void PrintVector2(const vector<string>& vec) {
	for (auto iter = vec.begin(); iter != vec.end(); iter++) {
		for (auto iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++) {
			cout << *iter2 << " ";
		}
		cout << endl;
	}
}