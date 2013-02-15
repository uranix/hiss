#include <coloring.h>
#include <iostream>
#include <fstream>
#include <stdio.h>

int main() {
	std::string junk;
	std::ifstream mtx("dwt__209.mtx");
	getline(mtx, junk);
	int n, m, nnz;
	mtx >> n >> m >> nnz;

	hiss::coloring col(n);

	for (; nnz; nnz--) {
		int i, j;
		mtx >> i >> j;
		i--; j--;
		if (i != j)
			col.insert_edge(i, j);
	}

	col.color_graph();
	std::cerr << (col.check_coloring() ? "Coloring ok." : "Coloring failed!") << std::endl;
	for (int c = 0; c < col.used_colors(); c++) {
		char fn[1024];
		sprintf(fn, "graph.%d.gv", c);
		std::ofstream f(fn, std::ios::out);
		f << "graph coloring {\nnodesep=1.0\nsplines=true" << std::endl;
		for (int i = 0; i < n; i++)
			f << i << ";" << std::endl;
		for (int i = 0; i < n; i++) {
			const std::map<int, hiss::color> &vert = col.get_coloring()[i];
			for (std::map<int, hiss::color>::const_iterator j = vert.begin(); 
				j != vert.end(); j++)
				if (i < j->first)
					f << i << " -- " << j->first << "[style=\"" << (j->second.v == c ? "" : "invis")<< "\"];" << std::endl;
		}
		f << "}" << std::endl;
		f.close();
	}
	return 0;
}
