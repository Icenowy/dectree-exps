#ifndef _ISDECTREE_ISUTIL_H
#define _ISDECTREE_ISUTIL_H

#include <utility>
#include <vector>
#include "isdectree.h"
#include <cstdio>
#include <string>

namespace isdectree {
	// false for left, true for right
	bool util_datajudge(const Divide &divide, const Datum &datum);
	// The standard is equal to left,right
	std::pair<std::vector<Datum>, std::vector<Datum> > util_datadivide(const Divide &divide, const std::vector<Datum> original);
	// Used to free a Node* returned from the algorithm_* function family
	void util_freenode(Node *node);
	// Write a Graphviz dot file including a decision tree
	void util_dotize(Node *node, FILE *fp);
	// Stringize a divide
	std::string util_divide_stringize(const Divide &dv);
}

#endif
