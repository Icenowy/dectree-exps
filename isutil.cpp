#include "isdectree.h"
#include "isutil.h"

#include <set>
#include <vector>
#include <stdexcept>

namespace isdectree {
	bool util_datajudge(const Divide &divide, const Datum &datum) {
		switch(divide.decisionType) {
			case Number: 
				return datum.numbers[divide.paramater] >= divide.threshold;
				break;
			case Enum:
				return divide.judgment.count(datum.enums[divide.paramater]);
				break;
			default:
				throw std::invalid_argument("Invaild Decision Type.");
				return false;
		}
		
	}
	
	std::pair<std::vector<Datum>, std::vector<Datum> > util_datadivide(const Divide &divide, const std::vector<Datum> original) {
		std::vector<Datum> left,right;
		for(const Datum & datum : original) {
			if(util_datajudge(divide,datum)) right.push_back(datum);
			else left.push_back(datum);
		}
		return std::make_pair(left,right);
	}
	
	void util_freenode(Node *node) {
		if(node.left != nullptr) util_freenode(node.left);
		if(node.right != nullptr) util_freenode(node.right);
		delete node; // node should be allocated with operator new in algorithm_* function family
	}
}
