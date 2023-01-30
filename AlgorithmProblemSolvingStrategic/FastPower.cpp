#include<iostream>
using namespace std;

long FastPower(long base,long exponent) {
	if (exponent == 1)return base;
	if (exponent % 2 == 1) {
		return FastPower(base, exponent - 1) * base;
	}
	return FastPower(base, exponent / 2) * FastPower(base, exponent / 2);
}

/*int main(void) {
	while (true)
	{
		cout << "n±îÁöÀÇ °ÅµìÁ¦°ö ÀÏ¶§ ¹Ø:";
		long base;
		long exponent;
		cin >> base;
		cout << "Áö¼ö:";
		cin >> exponent;
		cout << "ºÐÇÒÁ¤º¹ °ö:" << FastPower(base, exponent) << endl << endl;
	}
}*/