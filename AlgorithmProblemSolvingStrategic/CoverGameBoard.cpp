#include<iostream>
#include<vector>
#include<random>
using namespace std;

class GameBoard {
public:
	GameBoard(int height, int width)
		:gameBoard(Allocate(height, width)), height(height), width(width) {}
	void Input() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				char ch;
				cin >> ch;
				if (ch == BLACK) {
					gameBoard[i][j]++;
				}
			}
		}
	}
	
	void PrintBoard() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << gameBoard[i][j];
			}
			cout << endl;
		}
	}
	static int BrickCountOfCoverBoard(GameBoard& board) {
		pair<int, int> pos = board.FindEmpty();
		int x = pos.first;
		int y = pos.second;

		if (x == -1 && y == -1) {
			return 1;
		}
		int ret = 0;

		for (int i = 0; i < 4; i++) {
			if (board.IsAllRightIndex(x, y, i) && board.IsAllEmpty(x, y, i)) {
				board.PaintBoard(x, y, i);
				ret += BrickCountOfCoverBoard(board);
				board.EraseBoard(x, y, i);
			}
		}
		return ret;

	}
	int** gameBoard;

	bool CanCover() {
		int count = 0;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (gameBoard[i][j] == 0)count++;
			}
		}
		return count % 3 == 0;
	}
private:
	int** Allocate(int height, int width) const {
		int** ret = new int* [height];
		for (int i = 0; i < height; i++) {
			ret[i] = new int[width];
			for (int j = 0; j < width; j++) {
				ret[i][j] = 0;
			}
		}
		return ret;
	}

	bool IsRightIndex(int index, int max) const {
		return index >= 0 && index < max;
	}
	bool IsAllRightIndex(int xIndex, int yIndex, int dir) const {
		bool ret = IsRightIndex(xIndex, width) && IsRightIndex(yIndex, height);
		ret = ret && IsRightIndex(xIndex + dx[dir][0], width) && IsRightIndex(yIndex + dy[dir][0], height);
		ret = ret && IsRightIndex(xIndex + dx[dir][1], width) && IsRightIndex(yIndex + dy[dir][1], height);
		return ret;
	}
	bool IsAllEmpty(int x, int y, int direction)const {
		bool ret = IsEmpty(x, y);
		ret = ret && IsEmpty(x + dx[direction][0], y + dy[direction][0]);
		ret = ret && IsEmpty(x + dx[direction][1], y + dy[direction][1]);
		return ret;
	}
	bool IsEmpty(int x, int y)const {
		return gameBoard[y][x] == 0;
	}
	void PaintBoard(int x, int y, int dir) {
		if (!IsAllRightIndex(x, y, dir)) {
			return;
		}
		gameBoard[y][x] ++;
		gameBoard[y + dy[dir][0]][x + dx[dir][0]]++;
		gameBoard[y + dy[dir][1]][x + dx[dir][1]] ++;
	}
	void EraseBoard(int x, int y, int dir) {
		if (!IsAllRightIndex(x, y, dir)) {
			return;
		}
		gameBoard[y][x] --;
		gameBoard[y + dy[dir][0]][x + dx[dir][0]] --;
		gameBoard[y + dy[dir][1]][x + dx[dir][1]] --;
	}
	pair<int, int> FindEmpty()const {
		int x = -1;
		int y = -1;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (gameBoard[i][j] == 0) {
					x = j;
					y = i;
					break;
				}
			}
			if (y != -1)break;
		}
		return pair<int, int>(x, y);
	}



	int height;
	int width;
	const int dx[4][2] = { {-1,0},{1,0},{1,1},{0,1} };
	const int dy[4][2] = { {1,1},{0,1},{0,1},{1,1} };
	const char BLACK = '#';
	const char WHITE = '.';
	

};
const int coverType[4][3][2] = {
		{{0,0},{1,0},{0,1}},
		{{0,0},{0,1},{1,1}},
		{{0,0},{1,0},{1,1}},
		{{0,0},{1,0},{1,-1} }
};
bool set(vector<vector<int>>& board, int y, int x, int type, int delta) {
	bool ok = true;
	for (int i = 0; i < 3; i++) {
		const int ny = y + coverType[type][i][0];
		const int nx = x + coverType[type][i][1];
		if (ny < 0 || ny >= board.size() || nx < 0||nx>=board[0].size()) {
			ok = false;
		}
		else if ((board[ny][nx] += delta) > 1) {
			ok = false;
		}
	}
	return ok;
}

static int BrickCountTest(vector<vector<int>>& board) {
	int y = -1, x = -1;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		}
		if (y != -1) {
			break;
		}
	}

	if (y == -1)return 1;

	int ret = 0;
	for (int type = 0; type < 4; type++) {
		if (set(board, y, x, type, 1)) {
			ret += BrickCountTest(board);
		}
		set(board, y, x, type, -1);
	}
	return ret;
}
void PrintBoard(vector<vector<int>>& board) {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
}
/*int main(void) {

	for (int b = 0; b < 10000; b++) {
		int size = 3;
		for (int size = 1; size < 20; size++) {
			vector<vector<int>> board;
			GameBoard board2 = GameBoard(size, size);
			board.resize(size);
			for (int i = 0; i < size; i++) {
				srand(time(NULL) + i * size +  size+b*size*size);
				for (int j = 0; j < size; j++) {
					int value = rand() % 2;
					board[i].push_back(value);
					board2.gameBoard[i][j] = value;
				}
			}
			int count1 = BrickCountTest(board);
			int count2 = GameBoard::BrickCountOfCoverBoard(board2);
			if (count1 != count2) {
				cout << "답 불일치 발견) " << count1 << "/" << count2 << endl;
				cout << "정답족 보드)" << endl;
				PrintBoard(board);
				cout << "내꺼쪽 보드)" << endl;
				board2.PrintBoard();
			}

		}
	}
	
	
}*/
/*
int main(void) {
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		int H;
		int W;
		cin >> H >> W;


		GameBoard board = GameBoard(H, W);
		board.Input();
		cout << GameBoard::BrickCountOfCoverBoard(board) << endl;

	}
}*/