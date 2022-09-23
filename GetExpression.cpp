#include "GetExpression.h"

// 用于生成表达式的字符串
string GetExpression::get_expression_string(int n) {
	string str = to_string(rand() % n);	// 表达式
	string op = "+-*/";	// 4个运算符

	int k = rand() % 3 + 1, cnt = 1;	// k是这个表达式的运算符个数，不超过3个。cnt用于生成括号，这是一个随机的结果
	while (k--) {
		string ch(1, op[rand() % 4]);	// 随机生成运算符
		str += " " + ch + " ";

		int m = rand() % 3;	// m是加入数的类型
		if (m == 0) {	// m == 0表示加入的数是一个整数
			if (ch == "/") str += to_string(rand() % (n - 1) + 1);	// 如果此时的运算符是'/'号，那么这个数不可以是0
			else str += to_string(rand() % n);
		}
		else if (m == 1) {	// m == 1表示加入的数是一个真分数
			int down = rand() % max(1, n - 4) + 2;	// 分母要大于等于2
			int up = rand() % (down - 1) + 1;	// 保证分子小于分母
			str += to_string(up) + "/" + to_string(down);
		}
		else {	// m == 2表示加入的分数是 x'up/down类型的
			int down = rand() % max(1, n - 4) + 2;	// 分母要大于等于2
			int up = rand() % (down - 1) + 1;	// 保证分子小于分母
			int x = rand() % max(1, n - 1) + 1;	// x要大于0
			str += to_string(x) + "\'" + to_string(up) + "/" + to_string(down);
		}

		// 用于随机生成括号
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

// 用于将字符串形式的数字统一转换成假分式
string GetExpression::str_to_frac(string s) {
	if (~s.find('\'')) {	// x'up/down形式
		int k1 = s.find('\''), k2 = s.find('/');
		LL x = 0, up = 0, down = 0;
		for (int i = 0; i < k1; i++) {	// 找到x对应的数字
			x = x * 10 + s[i] - '0';
		}
		for (int i = k1 + 1; i < k2; i++) {	// 找到分子对应的数字
			up = up * 10 + s[i] - '0';
		}
		for (int i = k2 + 1; i < s.size(); i++) {	// 找到分母对应的数字
			down = down * 10 + s[i] - '0';
		}
		return to_string(x * down + up) + "/" + to_string(down);
	}
	else if (~s.find('/')) {	// up/down形式
		return s;	// 直接放回
	}
	else {	// 整数
		return s + "/1";	// 等价于除以1
	}
}

// 用于提取真方式的分子和分母
void GetExpression::frac_to_int(string& s, LL& up, LL& down) {
	int k = s.find('/');	// 找到'/'的下标
	for (int i = 0; i < k; i++) {
		up = up * 10 + s[i] - '0';	// 算出分子
	}
	for (int i = k + 1; i < s.size(); i++) {
		down = down * 10 + s[i] - '0';	// 算出分母
	}
}

// 用于将分子和分母转换成字符串形式的真分式
string GetExpression::int_to_real_frac(LL up, LL down) {
	if (down == 1) return to_string(up);	// 分母为1，表示是整数
	LL x = up / down, r = up % down;	// 算出倍数x，r是余数
	string s;
	if (x) s += to_string(x) + "\'";
	s += to_string(r) + "/" + to_string(down);
	return s;
}

// 欧几里得公式，获取两个数的最大公因数
LL GetExpression::gcd(LL a, LL b) {
	return b ? gcd(b, a % b) : a;
}

// 用于栈顶弹出的字符串的计算，同时构造二叉树结点
bool GetExpression::cal() {
	string s2 = str_to_frac(num.top());	// 栈顶弹出一个数字，并转换成假分式形式
	num.pop();
	string s1 = str_to_frac(num.top());	// 栈顶弹出一个数字，并转换成假分式形式
	num.pop();

	char ch = op.top();	// 栈顶弹出一个运算符
	op.pop();

	// s1 = a/b, s2 = c/d
	LL a = 0, b = 0, c = 0, d = 0;
	frac_to_int(s1, a, b), frac_to_int(s2, c, d);	// 获取分式的分子和分母

	LL up, down;	// 计算结果的分子和分母
	if (ch == '+') {
		up = a * d + b * c;
		down = b * d;
		LL cd = gcd(up, down);
		up /= cd, down /= cd;
	}
	else if (ch == '-') {
		up = a * d - b * c;
		down = b * d;
		if (up < 0) return true;	// 异常处理，如果计算过程中出现负数，该表达式不满足条件
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
		if (down == 0) return true;	// 异常处理，如果计算过程中出现除以0的情况，该表达式存在错误
		LL cd = gcd(up, down);
		up /= cd, down /= cd;
	}
	num.push(int_to_real_frac(up, down));	// 把计算结果转换成真分式并压入栈中

	// 生成表达式对应的二叉树的结点
	TNode* r = stk.top(); stk.pop();
	TNode* l = stk.top(); stk.pop();
	stk.push(new TNode(string(1, ch), l, r));

	return false;
}

// 计算得到表达式结果，并构建这个表达式对应的二叉树
bool GetExpression::solve(string str) {
	for (int i = 0; i < str.size(); i++) {
		if (isspace(str[i])) continue;	// 空格直接跳过
		if (isdigit(str[i])) {	// 如果发现是数字
			string t(1, str[i++]);
			while (i < str.size() && !isspace(str[i]) && str[i] != ')') {	// 把数字全部提取出来
				t += str[i++];
			}

			num.push(t);	// 把数字压入栈中
			stk.push(new TNode(t));	// 生成对应的二叉树结点

			i--;
			continue;
		}

		if (str[i] == '(') {	// 左括号直接压入
			op.push(str[i]);
		}
		else if (str[i] == ')') {
			while (op.top() != '(') {	// 一直弹出运算符直到遇到'('
				if (cal()) return false;	// 计算结果出现错误，返回false表示该表达式不满足条件
			}
			op.pop();
		}
		else {
			while (!op.empty() && (str[i] == '+' || str[i] == '-') && op.top() != '(') {	// '+','-'号运算级低
				if (cal()) return false;	// 计算结果出现错误，返回false表示该表达式不满足条件
			}
			while (!op.empty() && (str[i] == '*' || str[i] == '/') && (op.top() == '*' || op.top() == '/')) {	// '*','/'号运算级高
				if (cal()) return false;	// 计算结果出现错误，返回false表示该表达式不满足条件
			}
			op.push(str[i]);
		}
	}

	while (!op.empty()) {	// 处理最后的结果
		if (cal()) return false;
	}

	ans = num.top();	// 此时栈顶元素就是表达式的答案
	root = stk.top();	// 此时栈顶元素就是表达式对应的二叉树

	return true;
}

// 用于将表达式的字符串形式，对应的答案，以及表达式对应的二叉树返回
pair<pair<string, string>, TNode*> GetExpression::return_exp(int n) {
	bool flag = false;
	while (!flag) {	// 如果表达式不符合条件，则继续生成表达式
		// 清空栈
		stack<string>().swap(num);
		stack<char>().swap(op);
		stack<TNode*>().swap(stk);

		exp_string = get_expression_string(n);
		flag = solve(exp_string);	// 放回该表达式是否满足条件
	}

	return { {exp_string, ans}, root };
}