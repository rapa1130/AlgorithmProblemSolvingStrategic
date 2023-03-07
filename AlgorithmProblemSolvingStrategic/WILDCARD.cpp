#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
bool WildCard2(const string& wildcard, const string& str) {
    int wildLen = wildcard.length();
    int strLen = str.length();
    if (wildLen==0&&strLen == 0) {
        return true;
    }
    if (strLen != 0 && wildLen == 0) {
        return false;
    }
    if (strLen == 0&& wildLen!=0) {
        for (int i = 0; i < wildcard.length(); i++) {
            if (wildcard.substr(i, 1) != "*") {
                return false;
            }
        }
        return true;
    }
    string nowWild = wildcard.substr(0, 1);
    if (nowWild == "*") {
        for (int i = 0; i <= str.length(); i++) {
            if (WildCard2(wildcard.substr(1), str.substr(i))){
                return true;
            }
        }
        return false;
    }
    else if (nowWild == "?") {
        return WildCard2(wildcard.substr(1), str.substr(1));
    }
    else {
        if (nowWild == str.substr(0, 1)) {
            return WildCard2(wildcard.substr(1), str.substr(1));
        }
        else {
            return false;
        }
    }
}

bool WildCard(const string& wildcard, const string& str) {
    int wildLen = wildcard.length();
    int strLen = str.length();
    if (wildLen == 0 || strLen == 0) {
        if (wildLen != 0&&wildcard.substr(0,1)=="*") {
            return true;
        }
        return wildLen == 0 && strLen == 0;
    }
    string nowWild = wildcard.substr(0, 1);
    if (nowWild == "*") {
        if (wildcard.length() == 1) {
            return true;
        }
        else {
            string nextWild = wildcard.substr(1, 1);
            int findIndex = 0;
            while (findIndex < str.length()) {
                findIndex = str.find(nextWild, findIndex);
                if (findIndex == string::npos) {
                    return false;
                }
                if (WildCard(wildcard.substr(1), str.substr(findIndex))) {
                    return true;
                }
                findIndex++;
            }
            return false;
        }
    }
    else if (nowWild == "?") {
        return WildCard(wildcard.substr(1), str.substr(1));
    }
    else {
        if (str.substr(0, 1) != nowWild) {
            return false;
        }
        return WildCard(wildcard.substr(1), str.substr(1));
    }
}

int main() 
{
    int testcase; cin >> testcase;
    while (testcase-- > 0) {
        string wild;
        string str;

        cin >> wild;
        int strCount; cin >> strCount;

        vector<string> correct;
        for (int i = 0; i < strCount; i++) {
            cin >> str;
            if (WildCard2(wild, str)) {
                correct.push_back(str);
            }
        }
        sort(correct.begin(), correct.end());
        for (int i = 0; i < correct.size(); i++)
        {
            cout << correct[i] << endl;
        }
    }
}