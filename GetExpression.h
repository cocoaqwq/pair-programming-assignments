#pragma once
#include <bits/stdc++.h>
#include "TNode.h"
using namespace std;

typedef long long LL;

class GetExpression {
public:
	stack<string> num;
	stack<char> op;
	stack<TNode*> stk;
	string exp_string;
	string ans;
	TNode* root;

	string get_expression_string(int n);		// 用于生成表达式的字符串
	string str_to_frac(string s);				// 用于将字符串形式的数字统一转换成假分式
	void frac_to_int(string& s, LL& a, LL& b);	// 用于提取真方式的分子和分母
	string int_to_real_frac(LL up, LL down);	// 用于将分子和分母转换成字符串形式的真分式
	LL gcd(LL a, LL b);							// 欧几里得公式，获取两个数的最大公因数
	bool cal();									// 用于栈顶弹出的字符串的计算，同时构造二叉树结点
	bool solve(string str);						// 计算得到表达式结果，并构建这个表达式对应的二叉树
	pair<pair<string, string>, TNode*> return_exp(int n);	// 用于将表达式的字符串形式，对应的答案，以及表达式对应的二叉树返回
};