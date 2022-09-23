#include <bits/stdc++.h>
#include "TNode.h"
#include "ExpressionSet.h"
#include "GetExpression.h"
using namespace std;

typedef long long LL;

int main() {
	srand(time(0));	// 随机数种子

	while (true) {
		cout << "输入0 退出程序\n";
		cout << "输入1 生成表达式题目\n";
		cout << "输入2 验证题目答案正确性\n";
		cout << "\n输入您的选择：";

		// 输入操作数
		int op;
		cin >> op;

		switch (op) {
		case 0: {
			cout << "程序已成功退出\n";
			system("pause");
			exit(0);
		}
		case 1: {
			int n, m;	// n是题目个数，m是数值范围
			cout << "输入生成题目的个数：";
			while (cin >> n, n > 10000) {
				cout << "生成题目的个数应不超过10000个，请重新输入\n";
				cout << "输入生成题目的个数：";
			}

			cout << "输入数值的范围：";
			while (cin >> m, m > 100) {
				cout << "数值的范围应不超过100，请重新输入\n";
				cout << "输入数值的范围：";
			}
			cout << endl;

			ExpressionSet exp_set;	// 生成表达式集合类，用于维护表达式以及对应的答案
			for (int i = 0; i < n; i++) {
				auto t = GetExpression().return_exp(m);	// 通过生成表达式类来生成表达式
				string str = t.first.first, ans = t.first.second;	// 提取表达式的字符串以及答案
				TNode* root = t.second;	// 表达式对应的二叉树，用于检查该表达式是否重复
				while (!exp_set.add_exp(str, ans, root)) {	// 无法加入该表达式，因为与之前已存在的某个表达式重复，
					t = GetExpression().return_exp(m);	// 重新获取表达式
					str = t.first.first;
					ans = t.first.second;
					root = t.second;
				}
			}

			exp_set.write_to_file();	// 将表达式和答案写入文件

			cout << n << "道题目已成功生成，已保存至Exercises.txt中\n";
			break;
		}
		case 2: {
			ExpressionSet exp_set;
			exp_set.do_exercises();	// 检查答案的正确性
			break;
		}
		default: {
			cout << "输入的值是0到2之间的整数，请重新输入\n";
			break;
		}
		}

		system("pause");
		system("cls");
	}

	return 0;
}