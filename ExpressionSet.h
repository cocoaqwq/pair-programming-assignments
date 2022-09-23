#pragma once
#include <bits/stdc++.h>
#include "TNode.h"
#include "GetExpression.h"
using namespace std;

typedef long long LL;

class ExpressionSet {
public:
	vector<string> exp_string;
	vector<string> exp_ans;
	vector<TNode*> exp_tree;
	vector<string> user_ans;

	bool isomorphism(TNode* root1, TNode* root2);		// 用于判断两棵二叉树是否是同构的
	bool check_isomorphism(TNode* root);				// 用于判断当前子树是否与之前的某棵子树同构
	bool add_exp(string str, string ans, TNode* root);	// 用于将表达式加入集合。并放回是否加入成功
	void disp();			// 用于调试，打印输出表达式以及答案
	void write_to_file();	// 用于将表达式与答案写入文件
	bool read_from_file();	// 用于从文件中读入用户输入的答案以及表达式正确的答案
	void do_exercises();	// 用于判断用户输入的答案与正确答案的正确性
};