#ifndef __HISS__PORTRAIT_H__
#define __HISS__PORTRAIT_H__

#include "common.h"

#include <vector>
#include <set>

#include "sparsecomm.h"

namespace hiss {

struct csr {
	std::vector<index> rowstart;
	std::vector<index> cols;
	csr() {
		rowstart.push_back(0);
	}
	void add(const std::set<index> &row) {
		rowstart.push_back(rowstart.back() + row.size());
		cols.insert(cols.end(), row.begin(), row.end());
	}
};

class portrait {
	sparsecomm &sc;

	std::vector<std::pair<int, index> > map; /* local index -> (r, local index in domain r) */

	std::vector<std::set<index> > pattern; /* may have empty rows */

	std::vector<std::vector<index> > ext; 
	std::vector<std::vector<index> > brd;

	std::vector<index> reorder;

	bool finalized;

	void add_mapping(int i, int rank, int ri);
	void exchange_ext();

public:
	csr matrix;
	std::vector<index> brd_rows; /* matrix(brd(:), :) */

	portrait(sparsecomm &sc, index n_cols);
	void add_normal(index i, index j);
	void add_ghost(index i, index j, int q, index rj);
	void finalize_portrait();

};

};

#endif 
