#pragma once
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

struct TNode {
	string val;
	TNode* l, * r;

	TNode(string val, TNode* l = NULL, TNode* r = NULL);
};