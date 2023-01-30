#include<iostream>
#include<string>
#define TREE_BRANCH_NUM 4
using namespace std;

class QuadTree {
public:
	char data;
	QuadTree* nexts[TREE_BRANCH_NUM];
	QuadTree(const QuadTree& tree) {
		this->data = tree.data;
		for (int i = 0; i < TREE_BRANCH_NUM; i++) {
			this->nexts[i] = tree.nexts[i];
		}
	}
	QuadTree(char data) :data(data) {}
	QuadTree() {}
};

void GetTree(QuadTree& nowTree, const string& str, int& nowStrIndex);
string TreeToString(const QuadTree& tree);
void SwapTree(QuadTree* tree1, QuadTree* tree2);
void FlipHorTree(QuadTree& nowTree);


/*
int main(void) {
	QuadTree tree;
	int testcase;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		string str;
		cin >> str;
		int nowStrIndex = 0;
		GetTree(tree, str, nowStrIndex);
		FlipHorTree(tree);
		string treeStr = TreeToString(tree);
		cout << treeStr << endl;
	}
}*/
void FlipHorTree(QuadTree& nowTree) {
	char nowData = nowTree.data;
	if (nowData != 'x') {
		return;
	}
	SwapTree(nowTree.nexts[0], nowTree.nexts[2]);
	SwapTree(nowTree.nexts[1], nowTree.nexts[3]);

	for (int i = 0; i < TREE_BRANCH_NUM; i++) {
		if (nowTree.nexts[i]->data == 'x') {
			FlipHorTree(*nowTree.nexts[i]);
		}
	}
}

void GetTree(QuadTree & nowTree, const string & str, int& nowStrIndex) {

	for (; nowStrIndex < str.size() && str[nowStrIndex] != '\0';) {
		switch (str[nowStrIndex]) {
		case 'x':
			nowTree.data = 'x';
			nowStrIndex++;
			for (int i = 0; i < TREE_BRANCH_NUM; i++) {
				nowTree.nexts[i] = new QuadTree();
				GetTree(*nowTree.nexts[i], str, nowStrIndex);
			}
			return;
			break;
		case 'w':
		case 'b':
			nowTree.data = str[nowStrIndex];
			nowStrIndex++;
			return;
			break;
		}
	}
}

string TreeToString(const QuadTree& tree) {
	string ret;

	if (tree.data != 'x') {
		ret.push_back(tree.data);
		return ret;
	}

	ret.push_back(tree.data);
	for (int i = 0; i < TREE_BRANCH_NUM; i++) {
		ret += TreeToString(*tree.nexts[i]);
	}
	return ret;
}

void SwapTree(QuadTree* tree1, QuadTree* tree2) {
	QuadTree temp = *tree1;
	*tree1 = *tree2;
	*tree2 = temp;
}