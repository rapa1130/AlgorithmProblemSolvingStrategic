#include<iostream>
using namespace std;
int boardSize = 5;

char board[5][5] = {
	{'u','r','l','p','m'},
	{'x','p','r','e','t'},
	{'g','i','a','e','t'},
	{'x','t','n','z','y'},
	{'x','o','q','r','s'}
};

int dx[8] = { 0,1,1,1,0,-1,-1,-1 };
int dy[8] = { 1,1,0,-1,-1,-1,0,1 };


bool CheckIndexInBoundary(int x, int y) {
	return (x >= 0 && x < boardSize) && (y >= 0 && y < boardSize);
}
void PrintBoard() {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			cout.width(3);
			cout << board[i][j];
		}
		cout << endl;
	}
}

bool HasWord(const string& word, int x, int y) {
	if (!CheckIndexInBoundary(x, y)) {
		return false;
	}
	if (board[y][x] != word.front()) {
		return false;
	}
	if (word.size() == 1) {
		return true;
	}
	for (int i = 0; i < 8; i++) {
		int newX = x + dx[i];
		int newY = y + dy[i];
		if (HasWord(word.substr(1), newX, newY)) {
			return true;
		}
	}
	return false;
}


/*int main(void) {
	PrintBoard();
	cout << "찾고싶은 문자열을 입력:";
	string str;
	cin >> str;
	cout << HasWord(str, 1, 1) ? "있음!" : "없음";

}*/