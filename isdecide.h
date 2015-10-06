#ifndef _ISDECIDE_ISDECIDE_H
#define _ISDECIDE_ISDECIDE_H

#include "isdectree.h"

namespace isdectree {
	// The result argument of input datum is ignored
	EnumType decide(const Datum &datum, Node * tree);
}

#endif
