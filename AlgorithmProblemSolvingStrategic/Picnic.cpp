#include<iostream>
#include<vector>
#include<stack>
using namespace std;
typedef pair<int, int> Relation;
Relation friendRelation[45];
int friendNum;
int studentNum;
bool isExist[10];

bool IsAllExist(stack<Relation> relations) {
	bool isExist[10];
	for (int i = 0; i < studentNum; i++) {
		isExist[i] = 0;
	}
	while (!relations.empty()) {
		isExist[relations.top().first] = true;
		isExist[relations.top().second] = true;
		relations.pop();
	}
	for (int i = 0; i < studentNum; i++) {
		if (!isExist[i])
			return false;
	}
	return true;
}
bool IsOverlaped(stack<Relation> relations) {
	if (relations.empty())
		return false;
	bool isExist[10];
	for (int i = 0; i < 10; i++) {
		isExist[i] = 0;
	}
	Relation top = relations.top();
	relations.pop();

	while (!relations.empty()) {
		isExist[relations.top().first] = true;
		isExist[relations.top().second] = true;
		relations.pop();
	}
	return isExist[top.first] || isExist[top.second];
}

//ÇÐ»ýÂ¦Áþ±â ¼ö Ãâ·Â
int StudentLineCount(stack<Relation>& relations, int first) {
	int count = 0;
	if (IsOverlaped(relations)) {
		return 0;
	}
	if (relations.size() == studentNum / 2) {
		if (IsAllExist(relations)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	for (int i = first; i < friendNum; i++) {

		relations.push(friendRelation[i]);
		count += StudentLineCount(relations, i + 1);
		relations.pop();
	}
	return count;
}

/*int main(void) {
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {

		cin >> studentNum >> friendNum;
		for (int j = 0; j < friendNum; j++) {
			int firstFriendIndex;
			int secondFriendIndex;
			cin >> firstFriendIndex >> secondFriendIndex;
			friendRelation[j] = Relation(firstFriendIndex, secondFriendIndex);
		}
		stack<Relation> stack;
		cout << StudentLineCount(stack, 0) << endl;
	}
}*/