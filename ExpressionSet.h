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

	bool isomorphism(TNode* root1, TNode* root2);		// �����ж����ö������Ƿ���ͬ����
	bool check_isomorphism(TNode* root);				// �����жϵ�ǰ�����Ƿ���֮ǰ��ĳ������ͬ��
	bool add_exp(string str, string ans, TNode* root);	// ���ڽ����ʽ���뼯�ϡ����Ż��Ƿ����ɹ�
	void disp();			// ���ڵ��ԣ���ӡ������ʽ�Լ���
	void write_to_file();	// ���ڽ����ʽ���д���ļ�
	bool read_from_file();	// ���ڴ��ļ��ж����û�����Ĵ��Լ����ʽ��ȷ�Ĵ�
	void do_exercises();	// �����ж��û�����Ĵ�����ȷ�𰸵���ȷ��
};