#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<int>> Vector2;
bool IsRightIndex(int x,int y,const Vector2& board) {
	int ySize = board.size();
	int xSize = board[0].size();
	bool isRightX = x >= 0 && x < xSize;
	bool isRightY = y >= 0 && y < ySize;
	return isRightX && isRightY;
}
int Cash[100][100];

bool CanReach(const Vector2& board,int x,int y) {
	if (!IsRightIndex(x, y,board)) {
		return false;
	}
	int nowValue = board[y][x];
	if (nowValue == 0) {
		return true;
	}
	int& cash = Cash[y][x];
	if (cash ==0) {
		return false;
	}
	else if (cash == 1) {
		return true;
	}
	return Cash[y][x] = CanReach(board, x + nowValue, y) || CanReach(board, x, y + nowValue);
}
int main(void) {
	int testcase; cin >> testcase;
	while (testcase-->0) {
		int size; cin >> size;
		Vector2 board(size);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				Cash[i][j] = -1;
			}
		}
		for (int i = 0; i < size; i++) {
			board[i].resize(size);
			for (int j = 0; j < size; j++) {
				cin >> board[i][j];
			}
		}
		bool canReach = CanReach(board, 0, 0);
		if (canReach) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}
}
