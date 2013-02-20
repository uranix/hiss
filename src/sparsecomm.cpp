#include "sparsecomm.h"
#include <cassert>

namespace hiss {

sparsecomm::sparsecomm(interprocess &ipc) : ipc(ipc) {}

void sparsecomm::build_sched(const std::set<int> &neibs) {
	std::vector<int> seq(neibs.begin(), neibs.end());
	/* coloring is done at master */
	if (ipc.rank() == 0) {
		coloring sched(ipc.size());
		for (int i = 0; i < seq.size(); i++) 
			if (seq[i])
				sched.insert_edge(0, seq[i]);
		for (int i = 1; i < ipc.size(); i++) {
			int nedges;
			ipc.recv(&nedges, 1, i);
			std::vector<int> edges(nedges);
			ipc.recv(&edges[0], edges.size(), i);
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
		for (int i = 1; i < ipc.size(); i++) {
			std::vector<int> temp(nrounds, -1);
			const std::map<int, color> &node = sched.get_coloring()[i];
			for (std::map<int, color>::const_iterator j = node.begin(); j != node.end(); ++j)
				temp[j->second.v] = j->first;
			int tsize = temp.size();
			ipc.send(&tsize, 1, i);
			ipc.send(&temp[0], temp.size(), i);
		}
	} else {
		int ssize = seq.size();
		ipc.send(&ssize, 1, 0);
		ipc.send(&seq[0], seq.size(), 0);
		int nrounds;
		ipc.recv(&nrounds, 1, 0);
		rounds.resize(nrounds);
		ipc.recv(&rounds[0], rounds.size(), 0);
	}
}

};
