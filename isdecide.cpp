#include "isdecide.h"
#include "isutil.h"

namespace isdectree {
	EnumType decide(const Datum &datum, Node *tree)
	{
		if(tree->left == nullptr && tree->right == nullptr)
			return tree->result;
		if(util_datajudge(tree->statement,datum))
			return decide(datum,tree->right);
		else
			return decide(datum,tree->left);
	}
}
