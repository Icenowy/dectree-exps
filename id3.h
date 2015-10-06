#ifndef _ISDECTREE_ID3_H
#define _ISDECTREE_ID3_H

#include "isdectree.h"

namespace isdectree {
        double algorithm_id3_entropy(const DatasetMetadata &meta, const std::vector<Datum> &data);
	//double algorithm_id3_gain(const Divide &divide, 
	Node *algorithm_id3(const DatasetMetadata &meta, const std::vector<Datum> &data);
}

#endif
