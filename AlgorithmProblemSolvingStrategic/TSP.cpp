#include<iostream>
#include<vector>

using namespace std;
const int MAX_CITY = 16;
const int INF = 987654321;
int cityNum;

int dist[MAX_CITY][MAX_CITY];
int visitCount[MAX_CITY];

int DistanceOf(const vector<int>& route) {
	int distance = 0;
	for (int i = 0; i < route.size() - 1; i++) {
		int front = route[i];
		int back = route[i + 1];
		distance += dist[front][back];
	}
	return distance;
}

int Min(int val1,int val2) {
	return val1 < val2 ? val1 : val2;
}

int MinDist(vector<int>& route) {
	int size = route.size();
	if (size == cityNum) {
		route.push_back(route.front());
		int distance = DistanceOf(route);
		route.pop_back();
		return distance;
	}
	if (size >= 2) {
		int front = route[size - 2];
		int back = route[size - 1];
		if (dist[front][back] == 0) {
			return INF;
		}
	}
	int min = INF;
	for (int next = 0; next < cityNum; next++) {
		if (visitCount[next]==0) {
			route.push_back(next);
			visitCount[next]++;
			min = Min(min, MinDist(route));
			route.pop_back();
			visitCount[next]--;
		}
	}
	return min;
}

/*
int main(void) {
	//Input 받기
	cin >> cityNum;
	for (int i = 0; i < cityNum; i++) {
		for (int j = 0; j < cityNum; j++) {
			cin >> dist[i][j];
		}
	}
	//hasVisted초기화
	for (int i = 0; i < cityNum; i++) {
		visitCount[i] = false;
	}

	vector<int> route;
	cout << MinDist(route) << endl;
}
*/