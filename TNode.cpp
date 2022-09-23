#include "TNode.h"

TNode::TNode(string val, TNode* l, TNode* r) {
	this->val = val;
	this->l = l;
	this->r = r;
}