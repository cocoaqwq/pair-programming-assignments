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

	string get_expression_string(int n);		// �������ɱ��ʽ���ַ���
	string str_to_frac(string s);				// ���ڽ��ַ�����ʽ������ͳһת���ɼٷ�ʽ
	void frac_to_int(string& s, LL& a, LL& b);	// ������ȡ�淽ʽ�ķ��Ӻͷ�ĸ
	string int_to_real_frac(LL up, LL down);	// ���ڽ����Ӻͷ�ĸת�����ַ�����ʽ�����ʽ
	LL gcd(LL a, LL b);							// ŷ����ù�ʽ����ȡ���������������
	bool cal();									// ����ջ���������ַ����ļ��㣬ͬʱ������������
	bool solve(string str);						// ����õ����ʽ�����������������ʽ��Ӧ�Ķ�����
	pair<pair<string, string>, TNode*> return_exp(int n);	// ���ڽ����ʽ���ַ�����ʽ����Ӧ�Ĵ𰸣��Լ����ʽ��Ӧ�Ķ���������
};