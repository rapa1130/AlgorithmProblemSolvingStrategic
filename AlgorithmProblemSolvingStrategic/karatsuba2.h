#pragma once
#include<iostream>
#include<vector>

using namespace std;

void normalize(vector<int>& num);
void SubFrom(vector<int>& to, vector<int>& from);
void AddTo(vector<int>& to, vector<int> from, int digit);
vector<int> karatsuba(vector<int>& a, vector<int>& b);
void PrintVector(const vector<int>& num);
