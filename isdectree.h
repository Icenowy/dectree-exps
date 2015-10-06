#ifndef _ISDECTREE_ISDECTREE_H
#define _ISDECTREE_ISDECTREE_H

#include <set>
#include <vector>

namespace isdectree {
	typedef unsigned int EnumType;
	typedef double NumberType;
	enum ParamaterType {
		Number, Enum
	};
	struct Divide {
		ParamaterType decisionType;
		int paramater;
		std::set<EnumType> judgment;
		NumberType threshold;
	};
	struct Node {
		Divide statement;
		Node *left, *right;
		int result;
		// Left: 
		// Number: <threshold
		// Enum: not in judgment
	};
	struct DatasetMetadata {
		int number_count;
		int enum_count;
		EnumType maxenum;
		EnumType maxresult;
	};
	struct Datum {
		std::vector<NumberType> numbers;
		std::vector<EnumType> enums;
		EnumType result;
	};
}

// Any item of data will be two vectors, one vector<double> (for Number) and one vector<int> (for Enum), and a int (result).

#include <vector>

#endif
