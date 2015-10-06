#include <isdecide.h>
#include <cassert>

using namespace isdectree;

int main()
{
	Node *root = new Node;
	Divide dv;
	dv.decisionType = Number;
	dv.threshold = 1.0;
	dv.paramater = 0;
	root->statement = dv;
	root->left = new Node;
	root->right = new Node;
	root->left->left = root->left->right = root->right->left = root->right->right = nullptr;
	root->left->result = 0;
	root->right->result = 2;
	Datum dt;
	dt.numbers.push_back(0.5);
	assert(decide(dt,root) == 0);
	dt.numbers.clear();
	dt.numbers.push_back(2.0);
	assert(decide(dt,root) == 2);
	return 0;
}
