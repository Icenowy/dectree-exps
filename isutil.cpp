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
		if(node->left != nullptr) util_freenode(node->left);
		if(node->right != nullptr) util_freenode(node->right);
		delete node; // node should be allocated with operator new in algorithm_* function family
	}
	
	std::string util_divide_stringize(const Divide &dv) {
		if(dv.decisionType == Number)
			throw std::runtime_error("Number Divide convert to string not implemented.");
		std::string jud;
		for(EnumType e : dv.judgment) {
			jud = jud + " " + "_p" + std::to_string(dv.paramater) + "_e" + std::to_string(e) + "_";
		}
		return std::string() + std::string("Param _p") + std::to_string(dv.paramater) + "_, with item" + jud;
	}

	static std::string util_node_stringize(Node *n) {
		if(n->left == nullptr && n->right == nullptr)
			return "Result " + std::to_string(n->result);
		else
			return util_divide_stringize(n->statement);
	}

	void util_dotize(Node *node, FILE *fp) {
		if(node->left == nullptr && node->right == nullptr) return;
		fprintf(fp,"\"%s\"->\"%s\" [label=\"out of range\"];\n" , util_node_stringize(node).c_str(),util_node_stringize(node->left).c_str());
		fprintf(fp,"\"%s\"->\"%s\" [label=\"in range\"];\n" , util_node_stringize(node).c_str(),util_node_stringize(node->right).c_str());
		util_dotize(node->left, fp);
		util_dotize(node->right, fp);
	}
}
