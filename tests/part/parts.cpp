#include "parts.h"

#include <iostream>
#include <vector>
#include <string>

#include <mpi_impl.h>
#include <sparsecomm.h>
#include <portrait.h>

using namespace std;
using namespace hiss;

vector<vector<pair<int,int> > > vert(4);
vector<vector<pair<int,int> > > edges(4);

int main() {

#define VERT(part, idx) \
	for (int i = 0; i < sizeof(part) / sizeof(part[0]); i++) \
		vert[idx].push_back(pair<int,int>(part[i][0]-1,part[i][1]-1))

#define EDGES(part, idx) \
	for (int i = 0; i < sizeof(part) / sizeof(part[0]); i++) \
		edges[idx].push_back(pair<int,int>(part[i][0]-1,part[i][1]-1))

#define IS_REAL(i) \
	((vert[dom][i].first == dom) && (vert[dom][i].second == i))

	VERT(part1, 0);
	VERT(part2, 1);
	VERT(part3, 2);
	VERT(part4, 3);

	EDGES(edges1, 0);
	EDGES(edges2, 1);
	EDGES(edges3, 2);
	EDGES(edges4, 3);


	MPI_impl ipc;
	sparsecomm sc(ipc);
	int dom = ipc.rank();
	portrait p(sc, vert[dom].size());

	for (int e = 0; e < edges[dom].size(); e++) {
		int i = edges[dom][e].first;
		int j = edges[dom][e].second;
		if (IS_REAL(i) && IS_REAL(j)) {
			p.add_normal(i, j);
			p.add_normal(j, i);
		}
		if (IS_REAL(i) && !IS_REAL(j)) {
			p.add_ghost(i, j, vert[dom][j].first, vert[dom][j].second);
		}
		if (IS_REAL(j) && !IS_REAL(i)) {
			p.add_ghost(j, i, vert[dom][i].first, vert[dom][i].second);
		}
	}

	p.finalize_portrait();
	int foo = 1;

	if (ipc.rank() > 0)
		ipc.recv(&foo, 1, ipc.rank() - 1);

	cout << "matrix for rank " << ipc.rank() << endl << "rowstart: ";
	for (int i = 0; i < p.matrix.rowstart.size(); i++)
		cout << p.matrix.rowstart[i] << ", ";
	cout << endl << "cols: ";
	int row = 0;
	for (int i = 0; i < p.matrix.cols.size(); i++) {
		while (i == p.matrix.rowstart[row]) {
			cout << endl;
			row++;
		}
		cout << p.matrix.cols[i] << ", ";
	}
	cout << endl << "brd_start: ";
	for (int i = 0; i < p.brd_start.size(); i++)
		cout << p.brd_start[i] << ", ";
	cout << endl << "brd_rows: ";
	row = 0;
	for (int i = 0; i < p.brd_rows.size(); i++) {
		while (i == p.brd_start[row]) {
			cout << endl;
			row++;
		}
		cout << p.brd_rows[i] << ", ";
	}
	cout << endl;
	
	if (ipc.rank() < ipc.size() - 1)
		ipc.send(&foo, 1, ipc.rank() + 1);

	return 0;
}
