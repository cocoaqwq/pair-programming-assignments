#include <bits/stdc++.h>
#include "TNode.h"
#include "ExpressionSet.h"
#include "GetExpression.h"
using namespace std;

typedef long long LL;

int main() {
	srand(time(0));	// ���������

	while (true) {
		cout << "����0 �˳�����\n";
		cout << "����1 ���ɱ��ʽ��Ŀ\n";
		cout << "����2 ��֤��Ŀ����ȷ��\n";
		cout << "\n��������ѡ��";

		// ���������
		int op;
		cin >> op;

		switch (op) {
		case 0: {
			cout << "�����ѳɹ��˳�\n";
			system("pause");
			exit(0);
		}
		case 1: {
			int n, m;	// n����Ŀ������m����ֵ��Χ
			cout << "����������Ŀ�ĸ�����";
			while (cin >> n, n > 10000) {
				cout << "������Ŀ�ĸ���Ӧ������10000��������������\n";
				cout << "����������Ŀ�ĸ�����";
			}

			cout << "������ֵ�ķ�Χ��";
			while (cin >> m, m > 100) {
				cout << "��ֵ�ķ�ΧӦ������100������������\n";
				cout << "������ֵ�ķ�Χ��";
			}
			cout << endl;

			ExpressionSet exp_set;	// ���ɱ��ʽ�����࣬����ά�����ʽ�Լ���Ӧ�Ĵ�
			for (int i = 0; i < n; i++) {
				auto t = GetExpression().return_exp(m);	// ͨ�����ɱ��ʽ�������ɱ��ʽ
				string str = t.first.first, ans = t.first.second;	// ��ȡ���ʽ���ַ����Լ���
				TNode* root = t.second;	// ���ʽ��Ӧ�Ķ����������ڼ��ñ��ʽ�Ƿ��ظ�
				while (!exp_set.add_exp(str, ans, root)) {	// �޷�����ñ��ʽ����Ϊ��֮ǰ�Ѵ��ڵ�ĳ�����ʽ�ظ���
					t = GetExpression().return_exp(m);	// ���»�ȡ���ʽ
					str = t.first.first;
					ans = t.first.second;
					root = t.second;
				}
			}

			exp_set.write_to_file();	// �����ʽ�ʹ�д���ļ�

			cout << n << "����Ŀ�ѳɹ����ɣ��ѱ�����Exercises.txt��\n";
			break;
		}
		case 2: {
			ExpressionSet exp_set;
			exp_set.do_exercises();	// ���𰸵���ȷ��
			break;
		}
		default: {
			cout << "�����ֵ��0��2֮�������������������\n";
			break;
		}
		}

		system("pause");
		system("cls");
	}

	return 0;
}