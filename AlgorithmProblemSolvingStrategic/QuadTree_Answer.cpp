#include<iostream>
using namespace std;

string FlipImageHor(string::iterator& iter) {
	char element = *(iter++);
	if (element == 'w' || element == 'b') {
		return string(1, element);
	}
	const string& leftUp = FlipImageHor(iter);
	const string& rightUp= FlipImageHor(iter);
	const string& leftDown = FlipImageHor(iter);
	const string& rightDown = FlipImageHor(iter);

	return "x" + leftDown + rightDown + leftUp + rightUp;
}

/*
int main(void) {
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		string str;
		cin >> str;
		auto iter = str.begin();
		cout << FlipImageHor(iter) << endl;
	}
}*/