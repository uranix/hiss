#include "coloring.h"

#include <set>
#include <algorithm>
#include <cassert>

namespace hiss {

color color::uncolored(-1);

color coloring::first_missing(int at) {
	color ret(0);
	std::set<color> cols;
	__hiss_dprintf("used at %d:", at);
	for (std::map<int, color>::const_iterator i = neib[at].begin(); i != neib[at].end(); ++i) {
		if (i->second != color::uncolored) {
			__hiss_dprintf("%d ", i->second.v);
			cols.insert(i->second);
		}
	}
	__hiss_dprintf("\n");
	for (std::set<color>::const_iterator i = cols.begin(); i != cols.end(); ++i)	{
		if (*i != ret)
			return ret;
		++ret;
	}
	return ret;
}

int coloring::find_edge_of_color(int at, color c) {
	for (std::map<int, color>::const_iterator i = neib[at].begin(); i != neib[at].end(); ++i) {
		if (i->second == c)
			return i->first;
	}
	return -1;
}

color &coloring::edge_color(int i, int j) {
	return neib[i].find(j)->second;
}

void coloring::color_edge_into(int ii, int jj, color vv) {
	if (maxcolor < vv) maxcolor = vv; 
	__hiss_dprintf("Coloring (%d, %d) into %d\n", ii, jj, vv.v);
	edge_color(ii, jj) = vv;
	edge_color(jj, ii) = vv;
}

int coloring::build_fan(int x, int to, std::vector<int> &y, std::vector<color> &t) {
	y.push_back(to);
	t.push_back(first_missing(to));
	__hiss_dprintf("y%d = %d\n", 0, to);
	__hiss_dprintf("t%d = %d\n", 0, t.back().v);

	while (true) {
		int z = find_edge_of_color(x, t.back());
		__hiss_dprintf("find_edge_of_color = %d\n", z);
		if (z == -1)
			/* No edge of color t[h] */
			return -1;
		int j = find(y.begin(), y.end(), z) - y.begin();
		if (j != y.size())
			/* That edge is already in the fan */
			return j;
		y.push_back(z);
		t.push_back(first_missing(z));
		__hiss_dprintf("y%lu = %d\n", t.size() - 1, y.back());
		__hiss_dprintf("t%lu = %d\n", t.size() - 1, t.back().v);
	}
}

void coloring::color_edge(int x, int to) {
	color s = first_missing(x);
	std::vector<int> y;
	std::vector<color> t;

	__hiss_dprintf("s = %d\n", s.v);
	assert(edge_color(x, to) == color::uncolored);

	int j = build_fan(x, to, y, t);

	__hiss_dprintf("built fan of size %lu with stop reason %d\n", y.size(), j);
	if (j == -1) {
		__hiss_dprintf("no edge of color t.back()\n");
		/* no edge of color t.back() */
		for (int i = 0; i < y.size(); i++) 
			color_edge_into(x, y[i], t[i]);
	} else {
		/* xy[j] has color t.back() */
		for (int i = 0; i < j; i++) 
			color_edge_into(x, y[i], t[i]);
		color_edge_into(x, y[j], color::uncolored);
		int z = x;
		color w = t.back();
		int sum = s.v + w.v;
		bool b1 = true;
		while (true) {
			z = find_edge_of_color(z, w);
			if (z == -1)
				break;
			w.v = sum - w.v;
			if (z == y[j]) {
				b1 = false;
				break;
			}
			if (z == y.back()) {
				break;
			}
		}
		if (b1) {
			__hiss_dprintf("no path from x to y[j]\n");
			/* no path from x to y[j] */
			z = y[j];
			w = s;
			std::vector<int> path(1, z);
			while (true) {
				z = find_edge_of_color(z, w);
				if (z == -1)
					break;
				w.v = sum - w.v;
				path.push_back(z);
			}
			__hiss_dprintf("length of y[j] comp : %lu\n", path.size());
			for (int i = 0; i < path.size() - 1; ++i) {
				color newc = sum - edge_color(path[i], path[i+1]).v;
				color_edge_into(path[i], path[i+1], newc);
			}
			color_edge_into(x, y[j], s);
		} else {
			__hiss_dprintf("no path from x to y.back()\n");
			/* no path from x to y.back() */
			for (int i = j; i < y.size(); i++) 
				color_edge_into(x, y[i], t[i]);
			color_edge_into(x, y.back(), color::uncolored);
			z = y.back();
			w = s;
			std::vector<int> path(1, z);
			while (true) {
				z = find_edge_of_color(z, w);
				if (z == -1)
					break;
				w.v = sum - w.v;
				path.push_back(z);
			}
			__hiss_dprintf("length of y.back() comp : %lu\n", path.size());
			for (int i = 0; i < path.size() - 1; ++i) {
				color newc = sum - edge_color(path[i], path[i+1]).v;
				color_edge_into(path[i], path[i+1], newc);
			}
			color_edge_into(x, y.back(), s);
		}
	}
}

void coloring::color_graph() {
	for (int x = 0; x < neib.size(); x++) {
		__hiss_dprintf("x = %d\n", x);
		for (std::map<int, color>::iterator edge = neib[x].begin(); 
			edge != neib[x].end(); ++edge) 
		{
			if (edge->first < x)
				continue;
			color_edge(x, edge->first);
		}
	}
}

bool coloring::check_coloring() const {
	for (int x = 0; x < neib.size(); x++) {
		std::set<color> cols;
		for (std::map<int, color>::const_iterator edge = neib[x].begin(); 
			edge != neib[x].end(); ++edge) 
		{
			if (edge->second == color::uncolored)
				return false;
			if (cols.find(edge->second) != cols.end())
				return false;
			cols.insert(edge->second);
		}
	}
	return true;
}

coloring::coloring(int n) : neib(n), maxcolor(0) { }

void coloring::insert_edge(int ii, int jj) {
	assert(ii != jj);
	neib[ii].insert(std::pair<int,color>(jj, color::uncolored));
	neib[jj].insert(std::pair<int,color>(ii, color::uncolored));
}

int coloring::used_colors() const {
	return maxcolor.v + 1;
}

const std::vector<std::map<int, color> > &coloring::get_coloring() const {
	return neib;
}

};
