#include "portrait.h"
#include <cassert>

namespace hiss {

void portrait::add_mapping(int i, int rank, int ri) {
	if (map[i].first == -1) 
		map[i] = std::pair<int, index>(rank, ri);
	else {
		std::pair<int, index> should_be(rank, ri);
		assert(map[i] == should_be);
	}
}

void portrait::exchange_ext() {
	assert(finalized);
	for (int round = 0; round < sc.rounds.size(); round++) {
		int other = sc.rounds[round];
		if (other < 0)
			continue;
		int rcnt, scnt = ext[other].size();
		sc.ipc.sendrecv(&scnt, 1, other, &rcnt, 1, other);
		brd[other].resize(rcnt);
		sc.ipc.sendrecv(&(ext[other][0]), scnt, other, &(brd[other][0]), rcnt, other);
	}
}

portrait::portrait(sparsecomm &sc, index n_cols) :
	sc(sc),
	map(n_cols, std::pair<int, index>(-1, 0)),
	pattern(n_cols),
	ext(sc.ipc.size()),
	brd(sc.ipc.size()),
	reorder(n_cols, n_cols),
	finalized(false)
{
}

void portrait::add_normal(index i, index j) {
	assert(!finalized);
	add_mapping(i, sc.ipc.rank(), i);
	add_mapping(j, sc.ipc.rank(), j);
	pattern[i].insert(j);
}

void portrait::add_ghost(index i, index j, int q, index rj) {
	assert(!finalized);
	add_mapping(i, sc.ipc.rank(), i);
	add_mapping(j, q, rj);
	pattern[i].insert(j);
}

void portrait::finalize_portrait() {
	finalized = true;
	int myrank = sc.ipc.rank();
	std::vector<index> self;
	std::vector<index> cstart(sc.ipc.size() + 1);
	std::vector<int> count(sc.ipc.size(), 0);

	for (int i = 0;	i < map.size(); i++) {
		const std::pair<int, index> &pos = map[i];
		if (pos.first != myrank) /* remote ghost */
			ext[pos.first].push_back(pos.second);
		else if (pos.second == i) /* not self-ghost */
			ext[myrank].push_back(i);
	}

	cstart[0] = 0;
	for (int i = 0; i < sc.ipc.size(); i++)
		cstart[i+1] = cstart[i] + ext[i].size();

	for (int i = 0; i < map.size(); i++) {
		const std::pair<int, index> &pos = map[i];
		if (pos.first != myrank) /* remote ghost */
			reorder[i] = cstart[pos.first] + count[pos.first]++;
		else if (pos.second == i) /* not self-ghost */
			reorder[i] = cstart[myrank] + count[myrank]++;
	}

	for (int i = 0; i < sc.ipc.size(); i++) {
		assert(count[i] == cstart[i+1] - cstart[i]);
		assert(count[i] == ext[i].size());
	}

	std::set<int> other;
	for (int i = 0; i < sc.ipc.size(); i++)
		if (ext[i].size())
			other.insert(i);
	sc.build_sched(other);
	
	exchange_ext();

	std::vector<index> ireord(count[myrank]);
	for (int i = 0; i < pattern.size(); i++) {
		int rj = reorder[i];
		if (rj >= cstart.back())
			continue;
		rj -= cstart[myrank];
		if (rj < 0 || rj >= count[myrank])
			continue;
		ireord[rj] = i;
	}

	for (int ri = 0; ri < count[myrank]; ri++) {
		int i = ireord[ri];
		std::set<index> row;
		for (std::set<index>::const_iterator j = pattern[i].begin(); j != pattern[i].end(); ++j) {
			if (reorder[*j] >= cstart.back()) {
				if (map[*j].first == myrank) {/* self-ghost */
					row.insert(map[*j].second);
					continue;
				}
				assert(false /* what else could it be*/);
			}
			row.insert(reorder[*j]);
		}
		matrix.add(row);
	}

	for (int k = 0; k < sc.ipc.size(); k++) 
		for (int m = 0; m < brd[k].size(); m++) {
			int i = brd[k][m];
			brd_rows.push_back(reorder[i]);
		}
}

};
