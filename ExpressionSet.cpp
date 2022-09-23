#include "ExpressionSet.h"

// �����ж����ö������Ƿ���ͬ����
bool ExpressionSet::isomorphism(TNode* root1, TNode* root2) {
	if (!root1 && !root2) {	// �������ǿ�����ͬ��
		return true;
	}
	else if (root1 && root2) {	// ������������
		if (root1->val == root2->val) {	// ���ڵ��ŵ�ֵ��ͬ
			if (!root1->l && !root2->l) {	// ����������������������
				return isomorphism(root1->r, root2->r);	// �ж��������Ƿ�ͬ��
			}
			else if (root1->l && root2->l && root1->l->val == root2->l->val) {	// �������������������ڣ����Ҵ�ŵ�ֵ��ͬ
				return isomorphism(root1->l, root2->l) && isomorphism(root1->r, root2->r);	// �ж��������Ƿ�ͬ�����������Ƿ�ͬ��
			}
			else {
				return isomorphism(root1->l, root2->r) && isomorphism(root1->r, root2->l);	// �ж����������Ƿ�ͬ��
			}
		}
		else {	// ���ڵ��ŵ�ֵ��ͬ����ͬ��
			return false;
		}
	}
	else {	// һ����Ϊ�գ���һ������Ϊ�գ���ͬ��
		return false;
	}
}

// �����жϵ�ǰ�����Ƿ���֮ǰ��ĳ������ͬ��
bool ExpressionSet::check_isomorphism(TNode* root) {
	for (auto& it : exp_tree) {
		if (isomorphism(it, root)) return true;
	}
	return false;
}

// ���ڽ����ʽ���뼯�ϡ����Ż��Ƿ����ɹ�
bool ExpressionSet::add_exp(string str, string ans, TNode* root) {
	if (check_isomorphism(root)) return false;	// ��֮ǰĳ�����ʽͬ���������Լ���������ʽ
	exp_string.push_back(str);
	exp_ans.push_back(ans);
	exp_tree.push_back(root);
	return true;
}

// ���ڵ��ԣ���ӡ������ʽ�Լ���
void ExpressionSet::disp() {
	for (int i = 0; i < exp_string.size(); i++) {
		cout << exp_string[i] << endl << exp_ans[i] << endl << endl;
	}
}

// ���ڽ����ʽ���д���ļ�
void ExpressionSet::write_to_file() {
	ofstream ofs;
	ofs.open("Exercises.txt", ios::out | ios::trunc);
	for (int i = 0; i < exp_string.size(); i++) {
		ofs << i + 1 << ". ����������Ŀ" << i + 1 << ":  " << exp_string[i] << endl;
	}
	ofs.close();

	ofs.open("Answers.txt", ios::out | ios::trunc);
	for (int i = 0; i < exp_string.size(); i++) {
		ofs << i + 1 << ". ��" << i + 1 << ":  " << exp_ans[i] << endl;
	}
	ofs.close();
}

// ���ڴ��ļ��ж����û�����Ĵ��Լ����ʽ��ȷ�Ĵ�
bool ExpressionSet::read_from_file() {
	ifstream ifs;
	ifs.open("Exercises.txt", ios::in);

	// �쳣����
	if (!ifs.is_open()) {	// δ�ɹ����ļ�����ʱ�û���δ������Ŀ
		cout << "δ�ҵ���Ӧ�ļ�������������Ŀ\n";
		return false;
	}

	string buf;
	user_ans.clear();
	while (getline(ifs, buf)) {	// �����û�����Ĵ�
		string ans = buf.substr(buf.rfind('=') + 2);
		user_ans.push_back(ans);
	}
	ifs.close();

	ifs.open("Answers.txt", ios::in);
	exp_ans.clear();
	while (getline(ifs, buf)) {	// ������ʽ��ȷ�Ĵ�
		string ans = buf.substr(buf.rfind(':') + 3);
		exp_ans.push_back(ans);
	}
	ifs.close();

	return true;
}

// �����ж��û�����Ĵ�����ȷ�𰸵���ȷ��
void ExpressionSet::do_exercises() {
	if (!read_from_file()) return;	// �޷����ļ����Ż�

	vector<int> correct, wrong;	// ��¼��ȷ����źʹ�������

	ifstream ifs;
	ifs.open("Exercises.txt", ios::in);

	for (int i = 0; i < exp_ans.size(); i++) {
		if (user_ans[i] == exp_ans[i]) correct.push_back(i + 1);	// ��ȷ��Ŀ�ͼ��뵽correct������
		else wrong.push_back(i + 1);	// ������Ŀ�ͼ��뵽wrong������
	}

	// �����ȷ�Խ��
	cout << "Correct: " << correct.size() << " ( ";
	for (int i = 0; i < correct.size(); i++) {
		if (i) cout << ", ";
		cout << correct[i];
	}
	cout << " )" << endl;

	cout << "Wrong: " << wrong.size() << " ( ";
	for (int i = 0; i < wrong.size(); i++) {
		if (i) cout << ", ";
		cout << wrong[i];
	}
	cout << " )\n";

	// ������
	ofstream ofs;
	ofs.open("Grade.txt", ios::out | ios::trunc);

	ofs << "Correct: " << correct.size() << " ( ";
	for (int i = 0; i < correct.size(); i++) {
		if (i) ofs << ", ";
		ofs << correct[i];
	}
	ofs << " )" << endl;

	ofs << "Wrong: " << wrong.size() << " ( ";
	for (int i = 0; i < wrong.size(); i++) {
		if (i) ofs << ", ";
		ofs << wrong[i];
	}
	ofs << " )\n";

	ofs.close();
}