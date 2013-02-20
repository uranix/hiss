#ifndef __HISS__SPARSECOMM_H__
#define __HISS__SPARSECOMM_H__

#include "interprocess.h"
#include "coloring.h"

#include <set>
#include <vector>

namespace hiss {

struct sparsecomm {
	interprocess &ipc;

	std::vector<int> rounds;

	sparsecomm(interprocess &ipc);
	void build_sched(const std::set<int> &neibs);
};

};

#endif
