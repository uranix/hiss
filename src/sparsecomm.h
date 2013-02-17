#ifndef __HISS__SPARSECOMM_H__
#define __HISS__SPARSECOMM_H__

#include "interprocess.h"
#include "coloring.h"

#include <set>
#include <vector>
#include <cassert>

namespace hiss {

struct sparsecomm {
	interprocess *ipc;

	std::vector<int> rounds;

	sparsecomm(interprocess *ipc) : ipc(ipc) {}
	void build_sched(const std::set<int> &neibs) {
		std::vector<int> seq(neibs.begin(), neibs.end());
		/* coloring is done at master */
		if (ipc->rank() == 0) {
			coloring sched(ipc->size());
			for (int i = 0; i < seq.size(); i++) 
				if (seq[i])
					sched.insert_edge(0, seq[i]);
			for (int i = 1; i < ipc->size(); i++) {
				int nedges = ipc->probe_size(i) / sizeof(int); // XXX not the right way to check message size
				std::vector<int> edges(nedges);
				ipc->recv(&edges[0], edges.size(), i);
				for (int j = 0; j < edges.size(); j++)
					if (i != edges[j])
						sched.insert_edge(i, edges[j]);
			}
			sched.color_graph();
			assert(sched.check_coloring());
			int nrounds = sched.used_colors();
			rounds.insert(rounds.begin(), nrounds, -1);
			const std::map<int, color> &self = sched.get_coloring()[0];
			for (std::map<int, color>::const_iterator j = self.begin(); j != self.end(); ++j)
				rounds[j->second.v] = j->first;
			for (int i = 1; i < ipc->size(); i++) {
				std::vector<int> temp(nrounds, -1);
				const std::map<int, color> &node = sched.get_coloring()[i];
				for (std::map<int, color>::const_iterator j = node.begin(); j != node.end(); ++j)
					temp[j->second.v] = j->first;
				ipc->send(&temp[0], temp.size(), i);
			}
		} else {
			ipc->send(&seq[0], seq.size(), 0);
			int nrounds = ipc->probe_size(0) / sizeof(int);
			rounds.resize(nrounds);
			ipc->recv(&rounds[0], rounds.size(), 0);
		}
	}
};

};

#endif
