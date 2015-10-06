#ifndef _ISDECTREE_ISDECTREE_H
#define _ISDECTREE_ISDECTREE_H

namespace isdectree {
	typedef unsigned int EnumType;
	enum ParamaterType {
		Number, Enum
	}
	class Node {
		ParamaterType decisionType;
		union {
			set<EnumType> judgment;
			double threshold;
		}
		Node *left, right;
		// Left: 
		// Number: <threshold
		// Enum: not in judgment
	}
}

#endif
