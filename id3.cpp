#include "id3.h"
#include "isutil.h"
#include <vector>
#include <cmath>
#include <stdexcept>

namespace isdectree {
	double algorithm_id3_entropy(const DatasetMetadata &meta, const std::vector<Datum> &data) {
		double entropy = 0;
		int len = data.size();
		if(!len) return 0;
		for(EnumType i = 0;i<=meta.maxresult;i++) {
			int count = 0;
			for(int j = 0;j<len;j++) {
				if(data[j].result == i) count++;
			}
			double p = (count*1.0)/len;
			if(p != 0)
				entropy -= p*std::log2(p);
		}
		return entropy;
	}
	double algorithm_id3_gain(const Divide &divide,const DatasetMetadata &meta, const std::vector<Datum> &data) {
		double original_entropy = algorithm_id3_entropy(meta,data);
		std::pair<std::vector<Datum>, std::vector<Datum> > datapair = util_datadivide(divide,data);
		double entropy_left = algorithm_id3_entropy(meta,datapair.first);
		double entropy_right = algorithm_id3_entropy(meta,datapair.second);
		int leftlen = datapair.first.size();
		int len = data.size();
		double entropy_new = (leftlen/len) * entropy_left + (1-leftlen/len) * entropy_right;
		return original_entropy - entropy_new;
	}
	static std::vector<std::set<EnumType> > full_set(EnumType i)
	{
		if(i < 0) throw std::runtime_error("cannot get full_set of a minus number");
		if(i == 0) {
			std::vector<std::set<EnumType> > v;
			std::set<EnumType> s;
			s.insert(0);
			v.push_back(s);
			return v;
		}
		else {
			std::vector<std::set<EnumType> > v;
			std::vector<std::set<EnumType> > ov = full_set(i-1);
			for(std::set<EnumType> os : ov) {
				v.push_back(os);
				os.insert(i);
				v.push_back(os);
			}
			return v;
		}
	}
	Node *algorithm_id3(const DatasetMetadata &meta, const std::vector<Datum> &data) {
		/*Divide dv;
		double number_maxgain = -INFINITY,number_threshold = 0.0;
		int number_i = -1;
		dv.decisionType = number;
		for(int i = 0;i<meta.number_count;i++) {
			dv.paramater = 
		}*/
		Divide dv;
		dv.decisionType = Enum;
		if(meta.number_count)
			throw std::runtime_error("Cannot use ID3 algorithm on number dataset");
		if(!data.size())
			throw std::runtime_error("Null dataset generated");
		double max_gain = -INFINITY;
		int max_gain_data = -1;
#ifdef SIMP
		int max_gain_item = -1;
#else
		std::set<EnumType> max_gain_set;
#endif
		for(int i = 0;i<meta.enum_count;i++) {
			dv.paramater = i;
#ifndef SIMP
			for(std::set<EnumType> s : full_set(meta.maxenum[i])) {
				dv.judgment = s;
				double gain;
				if((gain = algorithm_id3_gain(dv,meta,data)) > max_gain) {
					max_gain = gain;
					max_gain_data = i;
					max_gain_set = s;
				}
			}
#else
			for(int j = 0;j<meta.maxenum[i];j++) {
				dv.judgment.clear();
				dv.judgment.insert(j);
				double gain;
				if((gain = algorithm_id3_gain(dv,meta,data)) > max_gain) {
					max_gain = gain;
					max_gain_data = i;
					max_gain_item = j;
				}
			}
#endif
		}
		dv.paramater = max_gain_data;
#ifdef SIMP
		dv.judgment.clear();
		dv.judgment.insert(max_gain_item);
#else
		dv.judgment = max_gain_set;
#endif
		Node *node = new Node;
		node->statement = dv;
		int result = -1;
		std::pair<std::vector<Datum>, std::vector<Datum> > dtpr = util_datadivide(dv,data);
		if(!dtpr.first.size()) {
			result = dtpr.second[0].result;
			goto leaf;
		}
		if(!dtpr.second.size()) {
			result = dtpr.first[0].result;
			goto leaf;
		}
		node->left = algorithm_id3(meta,dtpr.first);
		node->right = algorithm_id3(meta,dtpr.second);
		node->result = -1;
		goto ret;
		leaf:
		node->left = node->right = nullptr;
		node->result = result;
		ret:
		return node;
	}
}
