#include<iostream>
#include<vector>

using namespace std;

int MaxArea_BruteForce2(const vector<int>& fenceHeight);
int MaxArea(const vector<int>& fenceHeight);
int MaxArea_BruteForce(const vector<int>& fenceHeight) {
	int maxArea = -1;
	int num =(int)fenceHeight.size();
	for (int i = 0; i < num; i++) {
		int minHeight = fenceHeight[i];
		for (int j = i; j < num; j++) {
			minHeight = min(minHeight, fenceHeight[j]);
			int nowArea = minHeight * (j - i + 1);
			maxArea = max(nowArea, maxArea);
		}
	}

	return maxArea;
}

/*
int main(void) {
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		int fenceNum;
		cin >> fenceNum;

		vector<int> fenceHeight;
		for (int j = 0; j < fenceNum; j++) {
			int height;
			cin >> height;
			fenceHeight.push_back(height);
		}
		cout << MaxArea(fenceHeight) << '\n';
	}
}
*/

int MaxArea(const vector<int>& fenceHeight) {
	int size = (int)fenceHeight.size();
	if (size < 20) {
		return MaxArea_BruteForce2(fenceHeight);
	}
	int half = size / 2;
	vector<int> frontGroup(fenceHeight.begin(), fenceHeight.begin() + half);
	vector<int> backGroup(fenceHeight.begin() + half, fenceHeight.end());
	int maxArea = max(MaxArea(frontGroup), MaxArea(backGroup));

	int frontIndex = half - 1;
	int backIndex = half;
	int minHeigth = min(fenceHeight[frontIndex], fenceHeight[backIndex]);
	maxArea = max(maxArea, minHeigth * (backIndex - frontIndex + 1));

	while (!(frontIndex == 0 && backIndex + 1 == size)) {
		maxArea = max(maxArea, minHeigth * (backIndex - frontIndex + 1));
		if (frontIndex <= 0) {
			backIndex++;
			minHeigth = min(minHeigth, fenceHeight[backIndex]);
		}
		else if (backIndex + 1 >= size) {
			frontIndex--;
			minHeigth = min(minHeigth, fenceHeight[frontIndex]);
		}
		else {
			if (fenceHeight[frontIndex - 1] > fenceHeight[backIndex + 1]) {
				frontIndex--;
				minHeigth = min(minHeigth, fenceHeight[frontIndex]);
			}
			else {
				backIndex++;
				minHeigth = min(minHeigth, fenceHeight[backIndex]);
			}
		}
	}
	maxArea = max(maxArea, minHeigth * (backIndex - frontIndex + 1));

	return maxArea;
}

int MaxArea_BruteForce2(const vector<int>& fenceHeight) {
	int maxArea = -1;
	int num = (int)fenceHeight.size();
	for (int i = 0; i < num; i++) {
		int nowHeigth = fenceHeight[i];
		int leftIndex;
		int rightIndex;
		for (leftIndex = i - 1; leftIndex >= 0 && fenceHeight[leftIndex] >= nowHeigth; leftIndex--);
		for (rightIndex = i + 1; rightIndex < num && fenceHeight[rightIndex] >= nowHeigth; rightIndex++);

		int length = rightIndex - leftIndex - 1;
		maxArea = max(maxArea, nowHeigth * length);
	}

	return maxArea;
}