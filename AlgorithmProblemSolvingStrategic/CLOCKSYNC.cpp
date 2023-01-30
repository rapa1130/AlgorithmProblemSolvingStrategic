#include<iostream>
#include<vector>
#include<math.h>
using namespace std;
vector<vector<int>> switchToClocks = {
	{0,1,2},
	{3,7,9, 11},
	{4,10,14,15},
	{0,4,5,6,7},
	{6,7,8,10,12},
	{0,2,14,15},
	{3,14,15},
	{4,5,7,14,15},
	{1,2,3,4,5},
	{3,4,5,9,13}
};
void TimePass(vector<int>& nowClockState, int switchIndex, int delta);
int SwitchCount(vector<int>& nowClockState, int nowSwitch, int count);
vector<int> GetClockState();
bool IsAllTwelveClock(vector<int>& nowClockState);

const int INF = 987654321;

/*
int main(void) {
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		vector<int> nowClockState = GetClockState();

		int minCount = SwitchCount(nowClockState, 0, 0);
		if (minCount == INF) {
			minCount = -1;
		}
		cout << minCount << endl;
	}
}*/
int SwitchCount(vector<int>& nowClockState, int nowSwitch,int count) {
	if (nowSwitch >= switchToClocks.size()) {
		if (IsAllTwelveClock(nowClockState)) {
			return count;
		}
		else {
			return INF;

		}
	}
	int minCount = INF;
	for (int switchIndex = nowSwitch; switchIndex < switchToClocks.size(); switchIndex++) {
		int nextCount = count;
		for (int i = 0; i < 4; i++) {
			minCount = min(SwitchCount(nowClockState, switchIndex + 1, nextCount), minCount);
			TimePass(nowClockState, switchIndex, 3);
			nextCount++;
		}
	}
	return minCount;
}
bool IsAllTwelveClock(vector<int>& nowClockState) {
	for (int i = 0; i < nowClockState.size(); i++) {
		if (nowClockState[i] != 12) {
			return false;
		}
	}
	return true;
}
vector<int> GetClockState() {
	vector<int> nowClockState;
	for (int i = 0; i < 16; i++) {
		int clock;
		cin >> clock;
		nowClockState.push_back(clock);
	}
	return nowClockState;
}
void TimePass(vector<int>& nowClockState,int switchIndex, int delta) {
	for (int i = 0; i < switchToClocks[switchIndex].size(); i++) {
		int clockIndex = switchToClocks[switchIndex][i];
		nowClockState[clockIndex] += delta;
		if (nowClockState[clockIndex] > 12) {
			nowClockState[clockIndex] = nowClockState[clockIndex] % 12;
		}
	}
}