#ifndef __HISS__PORTRAIT_H__
#define __HISS__PORTRAIT_H__

#include "common.h"

#include <vector>
#include <set>

namespace hiss {

struct portrait {
	MPI_impl *mpi;

	index nSelf;
	std::vector<index> nGhost; 

	std::vector<std::vector<index> > map;
	std::vector<std::vector<index> > rmap;

	std::vector<std::set<index> > cols;
	
	portrait(MPI_impl *_mpi, index _nSelf, const std::vector<index> &_nGhost) :
		nGhost(_mpi->size() + 1),
		map(_mpi->size())
	{
		mpi = _mpi;
		nSelf = _nSelf;
		nGhost[0] = 0;
		for (int i = 0; i < mpi->size(); i++) {
			nGhost[i+1] = nGhost[i] + _nGhost[i];
			map[i].reserve(_nGhost[i]);
		}
		cols = new index*[nSelf];
	}

	void addLocal(index i, index j) {
		assert(i < nSelf);
		assert(j < nSelf);
		
		if (i == j)
			return; /* Aztec compatibility */

		cols[i].insert(j);
	}

	void addRemote(index i, index j, int q, index rj) {
		assert(i < nSelf);
		assert(q < mpi->size());
		index cj = nGhost[q] + j;
		assert(cj < nGhost[q+1]);

		add_set(cols[i], rowsz[i], cj);
		/* check q = rank is deferred to setVal. Otherwise, is will be 
		impossible to set self-ghosts values only by (i,j) index pair */
		map[q][j] = rj;
	}

	void finalizePortrait() {
		
	}
};

};



#endif 
