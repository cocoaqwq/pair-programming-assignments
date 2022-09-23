#include "ExpressionSet.h"

// 用于判断两棵二叉树是否是同构的
bool ExpressionSet::isomorphism(TNode* root1, TNode* root2) {
	if (!root1 && !root2) {	// 两个都是空树，同构
		return true;
	}
	else if (root1 && root2) {	// 两棵树都存在
		if (root1->val == root2->val) {	// 根节点存放的值相同
			if (!root1->l && !root2->l) {	// 两棵树的左子树都不存在
				return isomorphism(root1->r, root2->r);	// 判断右子树是否同构
			}
			else if (root1->l && root2->l && root1->l->val == root2->l->val) {	// 两棵树的左子树都存在，并且存放的值相同
				return isomorphism(root1->l, root2->l) && isomorphism(root1->r, root2->r);	// 判断左子树是否同构，右子树是否同构
			}
			else {
				return isomorphism(root1->l, root2->r) && isomorphism(root1->r, root2->l);	// 判断左右子数是否同构
			}
		}
		else {	// 根节点存放的值不同，不同构
			return false;
		}
	}
	else {	// 一棵树为空，另一颗树不为空，不同构
		return false;
	}
}

// 用于判断当前子树是否与之前的某棵子树同构
bool ExpressionSet::check_isomorphism(TNode* root) {
	for (auto& it : exp_tree) {
		if (isomorphism(it, root)) return true;
	}
	return false;
}

// 用于将表达式加入集合。并放回是否加入成功
bool ExpressionSet::add_exp(string str, string ans, TNode* root) {
	if (check_isomorphism(root)) return false;	// 与之前某个表达式同构，不可以加入这个表达式
	exp_string.push_back(str);
	exp_ans.push_back(ans);
	exp_tree.push_back(root);
	return true;
}

// 用于调试，打印输出表达式以及答案
void ExpressionSet::disp() {
	for (int i = 0; i < exp_string.size(); i++) {
		cout << exp_string[i] << endl << exp_ans[i] << endl << endl;
	}
}

// 用于将表达式与答案写入文件
void ExpressionSet::write_to_file() {
	ofstream ofs;
	ofs.open("Exercises.txt", ios::out | ios::trunc);
	for (int i = 0; i < exp_string.size(); i++) {
		ofs << i + 1 << ". 四则运算题目" << i + 1 << ":  " << exp_string[i] << endl;
	}
	ofs.close();

	ofs.open("Answers.txt", ios::out | ios::trunc);
	for (int i = 0; i < exp_string.size(); i++) {
		ofs << i + 1 << ". 答案" << i + 1 << ":  " << exp_ans[i] << endl;
	}
	ofs.close();
}

// 用于从文件中读入用户输入的答案以及表达式正确的答案
bool ExpressionSet::read_from_file() {
	ifstream ifs;
	ifs.open("Exercises.txt", ios::in);

	// 异常处理
	if (!ifs.is_open()) {	// 未成功打开文件，此时用户还未生成题目
		cout << "未找到对应文件，请先生成题目\n";
		return false;
	}

	string buf;
	user_ans.clear();
	while (getline(ifs, buf)) {	// 读入用户输入的答案
		string ans = buf.substr(buf.rfind('=') + 2);
		user_ans.push_back(ans);
	}
	ifs.close();

	ifs.open("Answers.txt", ios::in);
	exp_ans.clear();
	while (getline(ifs, buf)) {	// 读入表达式正确的答案
		string ans = buf.substr(buf.rfind(':') + 3);
		exp_ans.push_back(ans);
	}
	ifs.close();

	return true;
}

// 用于判断用户输入的答案与正确答案的正确性
void ExpressionSet::do_exercises() {
	if (!read_from_file()) return;	// 无法打开文件，放回

	vector<int> correct, wrong;	// 记录正确的题号和错误的题号

	ifstream ifs;
	ifs.open("Exercises.txt", ios::in);

	for (int i = 0; i < exp_ans.size(); i++) {
		if (user_ans[i] == exp_ans[i]) correct.push_back(i + 1);	// 正确题目就加入到correct数组中
		else wrong.push_back(i + 1);	// 错误题目就加入到wrong数组中
	}

	// 输出正确性结果
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

	// 保存结果
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