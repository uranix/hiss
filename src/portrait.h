#ifndef __HISS__PORTRAIT_H__
#define __HISS__PORTRAIT_H__

#include "common.h"

#include <vector>
#include <set>
#include <cassert>

namespace hiss {

class portrait {
	MPI_impl *mpi;

	std::vector<std::pair<int, index> > map;

	std::vector<std::set<index> > pattern; /* may have empty rows */

	std::vector<std::vector<index> > external;
	std::vector<std::vector<index> > exported;

	std::vector<std::set<index> > cols;

	bool finalized;

	void add_mapping(int i, int rank, int ri) {
		if (map[i].first == -1) 
			map[i] = std::pair<int, index>(rank, ri);
		else {
			assert(map[i] == std::pair<int, index>(rank, ri));
		}
	}


public:

	portrait(MPI_impl *_mpi, index n_cols) :
		map(n_cols, std::pair<int, index>(-1, 0)),
		pattern(n_cols),
		external(_mpi->size()),
		exported(_mpi->size()),
		mpi(_mpi),
		finalized(false)
	{
	}

	void add_normal(index i, index j) {
		assert(!finalized);
		if (i == j)
			return; /* Aztec compatibility */
		add_mapping(i, mpi->rank(), i);
		add_mapping(j, mpi->rank(), j);
		pattern[i].insert(j);
	}

	void add_ghost(index i, index j, int q, index rj) {
		assert(!finalized);
		add_mapping(i, mpi->rank(), i);
		add_mapping(j, q, rj);
		pattern[i].insert(j);
	}

	void finalizePortrait() {
		
	}
};

};



#endif 
