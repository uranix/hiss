#ifndef __HISS__COLORING_H__
#define __HISS__COLORING_H__

#include <vector>
#include <map>

namespace hiss {

struct color {
	int v;
	color(int v): v(v) {}
	bool operator <(const color &o) const { return v < o.v;	}
	color &operator =(const int _v) { v = _v; return *this; }
	bool operator ==(const color &o) const { return v == o.v; }
	bool operator !=(const color &o) const { return v != o.v; }
	const color &operator++() { ++v; return *this; }
	static color uncolored;
};

#ifdef DPRINT
#include <stdio.h>
#define __hiss_dprintf(fmt, args...) fprintf(stderr, fmt, ##args)
#else
#define __hiss_dprintf(fmt, args...) do {} while (0)
#endif

class coloring {
	int n;
	std::vector<std::map<int, color> > neib; /* (i,j) -> color */
	color maxcolor;

	color first_missing(int at);
	int find_edge_of_color(int at, color c);
	color &edge_color(int i, int j);

	void color_edge_into(int ii, int jj, color vv);
	int build_fan(int x, int to, std::vector<int> &y, std::vector<color> &t);
	void color_edge(int x, int to);

public:

	coloring(int n);
	void color_graph();
	bool check_coloring() const;
	void insert_edge(int ii, int jj);
	int used_colors() const;
	const std::vector<std::map<int, color> > &get_coloring() const;
};

};

#endif
