#include "id3.h"
#include "isutil.h"
#include <vector>
#include <cmath>

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
	Node *algorithm_id3(const DatasetMetadata &meta, const std::vector<Datum> &data) {
	}
}
