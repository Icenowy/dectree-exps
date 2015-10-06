#ifndef _ISDECTREE_ID3_H
#define _ISDECTREE_ID3_H

#include "isdectree.h"

namespace isdectree {
	Node *algorithm_id3(const DatasetMetadata &meta, const std::vector<Datum> &data);
}

#endif
