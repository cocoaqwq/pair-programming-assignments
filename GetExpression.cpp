#include "GetExpression.h"

// �������ɱ��ʽ���ַ���
string GetExpression::get_expression_string(int n) {
	string str = to_string(rand() % n);	// ���ʽ
	string op = "+-*/";	// 4�������

	int k = rand() % 3 + 1, cnt = 1;	// k��������ʽ�������������������3����cnt�����������ţ�����һ������Ľ��
	while (k--) {
		string ch(1, op[rand() % 4]);	// ������������
		str += " " + ch + " ";

		int m = rand() % 3;	// m�Ǽ�����������
		if (m == 0) {	// m == 0��ʾ���������һ������
			if (ch == "/") str += to_string(rand() % (n - 1) + 1);	// �����ʱ���������'/'�ţ���ô�������������0
			else str += to_string(rand() % n);
		}
		else if (m == 1) {	// m == 1��ʾ���������һ�������
			int down = rand() % max(1, n - 4) + 2;	// ��ĸҪ���ڵ���2
			int up = rand() % (down - 1) + 1;	// ��֤����С�ڷ�ĸ
			str += to_string(up) + "/" + to_string(down);
		}
		else {	// m == 2��ʾ����ķ����� x'up/down���͵�
			int down = rand() % max(1, n - 4) + 2;	// ��ĸҪ���ڵ���2
			int up = rand() % (down - 1) + 1;	// ��֤����С�ڷ�ĸ
			int x = rand() % max(1, n - 1) + 1;	// xҪ����0
			str += to_string(x) + "\'" + to_string(up) + "/" + to_string(down);
		}

		// ���������������
		if (rand() % 3 == 0 && k && cnt-- > 0) {
			int space_cnt = 0;
			for (int i = str.size() - 1; i >= 0; i--) {
				if (i - 1 >= 0 && isspace(str[i - 1])) space_cnt++;
				if (!i || space_cnt == 3) {
					str.insert(i, "(");
					str.push_back(')');
					break;
				}
			}
		}
	}

	return str;
}

// ���ڽ��ַ�����ʽ������ͳһת���ɼٷ�ʽ
string GetExpression::str_to_frac(string s) {
	if (~s.find('\'')) {	// x'up/down��ʽ
		int k1 = s.find('\''), k2 = s.find('/');
		LL x = 0, up = 0, down = 0;
		for (int i = 0; i < k1; i++) {	// �ҵ�x��Ӧ������
			x = x * 10 + s[i] - '0';
		}
		for (int i = k1 + 1; i < k2; i++) {	// �ҵ����Ӷ�Ӧ������
			up = up * 10 + s[i] - '0';
		}
		for (int i = k2 + 1; i < s.size(); i++) {	// �ҵ���ĸ��Ӧ������
			down = down * 10 + s[i] - '0';
		}
		return to_string(x * down + up) + "/" + to_string(down);
	}
	else if (~s.find('/')) {	// up/down��ʽ
		return s;	// ֱ�ӷŻ�
	}
	else {	// ����
		return s + "/1";	// �ȼ��ڳ���1
	}
}

// ������ȡ�淽ʽ�ķ��Ӻͷ�ĸ
void GetExpression::frac_to_int(string& s, LL& up, LL& down) {
	int k = s.find('/');	// �ҵ�'/'���±�
	for (int i = 0; i < k; i++) {
		up = up * 10 + s[i] - '0';	// �������
	}
	for (int i = k + 1; i < s.size(); i++) {
		down = down * 10 + s[i] - '0';	// �����ĸ
	}
}

// ���ڽ����Ӻͷ�ĸת�����ַ�����ʽ�����ʽ
string GetExpression::int_to_real_frac(LL up, LL down) {
	if (down == 1) return to_string(up);	// ��ĸΪ1����ʾ������
	LL x = up / down, r = up % down;	// �������x��r������
	string s;
	if (x) s += to_string(x) + "\'";
	s += to_string(r) + "/" + to_string(down);
	return s;
}

// ŷ����ù�ʽ����ȡ���������������
LL GetExpression::gcd(LL a, LL b) {
	return b ? gcd(b, a % b) : a;
}

// ����ջ���������ַ����ļ��㣬ͬʱ������������
bool GetExpression::cal() {
	string s2 = str_to_frac(num.top());	// ջ������һ�����֣���ת���ɼٷ�ʽ��ʽ
	num.pop();
	string s1 = str_to_frac(num.top());	// ջ������һ�����֣���ת���ɼٷ�ʽ��ʽ
	num.pop();

	char ch = op.top();	// ջ������һ�������
	op.pop();

	// s1 = a/b, s2 = c/d
	LL a = 0, b = 0, c = 0, d = 0;
	frac_to_int(s1, a, b), frac_to_int(s2, c, d);	// ��ȡ��ʽ�ķ��Ӻͷ�ĸ

	LL up, down;	// �������ķ��Ӻͷ�ĸ
	if (ch == '+') {
		up = a * d + b * c;
		down = b * d;
		LL cd = gcd(up, down);
		up /= cd, down /= cd;
	}
	else if (ch == '-') {
		up = a * d - b * c;
		down = b * d;
		if (up < 0) return true;	// �쳣���������������г��ָ������ñ��ʽ����������
		LL cd = gcd(up, down);
		up /= cd, down /= cd;
	}
	else if (ch == '*') {
		up = a * c;
		down = b * d;
		LL cd = gcd(up, down);
		up /= cd, down /= cd;
	}
	else {
		up = a * d;
		down = b * c;
		if (down == 0) return true;	// �쳣���������������г��ֳ���0��������ñ��ʽ���ڴ���
		LL cd = gcd(up, down);
		up /= cd, down /= cd;
	}
	num.push(int_to_real_frac(up, down));	// �Ѽ�����ת�������ʽ��ѹ��ջ��

	// ���ɱ��ʽ��Ӧ�Ķ������Ľ��
	TNode* r = stk.top(); stk.pop();
	TNode* l = stk.top(); stk.pop();
	stk.push(new TNode(string(1, ch), l, r));

	return false;
}

// ����õ����ʽ�����������������ʽ��Ӧ�Ķ�����
bool GetExpression::solve(string str) {
	for (int i = 0; i < str.size(); i++) {
		if (isspace(str[i])) continue;	// �ո�ֱ������
		if (isdigit(str[i])) {	// �������������
			string t(1, str[i++]);
			while (i < str.size() && !isspace(str[i]) && str[i] != ')') {	// ������ȫ����ȡ����
				t += str[i++];
			}

			num.push(t);	// ������ѹ��ջ��
			stk.push(new TNode(t));	// ���ɶ�Ӧ�Ķ��������

			i--;
			continue;
		}

		if (str[i] == '(') {	// ������ֱ��ѹ��
			op.push(str[i]);
		}
		else if (str[i] == ')') {
			while (op.top() != '(') {	// һֱ���������ֱ������'('
				if (cal()) return false;	// ���������ִ��󣬷���false��ʾ�ñ��ʽ����������
			}
			op.pop();
		}
		else {
			while (!op.empty() && (str[i] == '+' || str[i] == '-') && op.top() != '(') {	// '+','-'�����㼶��
				if (cal()) return false;	// ���������ִ��󣬷���false��ʾ�ñ��ʽ����������
			}
			while (!op.empty() && (str[i] == '*' || str[i] == '/') && (op.top() == '*' || op.top() == '/')) {	// '*','/'�����㼶��
				if (cal()) return false;	// ���������ִ��󣬷���false��ʾ�ñ��ʽ����������
			}
			op.push(str[i]);
		}
	}

	while (!op.empty()) {	// �������Ľ��
		if (cal()) return false;
	}

	ans = num.top();	// ��ʱջ��Ԫ�ؾ��Ǳ��ʽ�Ĵ�
	root = stk.top();	// ��ʱջ��Ԫ�ؾ��Ǳ��ʽ��Ӧ�Ķ�����

	return true;
}

// ���ڽ����ʽ���ַ�����ʽ����Ӧ�Ĵ𰸣��Լ����ʽ��Ӧ�Ķ���������
pair<pair<string, string>, TNode*> GetExpression::return_exp(int n) {
	bool flag = false;
	while (!flag) {	// ������ʽ��������������������ɱ��ʽ
		// ���ջ
		stack<string>().swap(num);
		stack<char>().swap(op);
		stack<TNode*>().swap(stk);

		exp_string = get_expression_string(n);
		flag = solve(exp_string);	// �Żظñ��ʽ�Ƿ���������
	}

	return { {exp_string, ans}, root };
}