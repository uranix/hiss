#include "parts.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<vector<pair<int,int> > > vert(4);
vector<vector<pair<int,int> > > edges(4);
vector<vector<pair<float,float> > > pos(4);

string cols[4] = {"red", "green", "blue", "black"};

int main() {

#define VERT(part, idx) \
	for (int i = 0; i < sizeof(part) / sizeof(part[0]); i++) \
		vert[idx].push_back(pair<int,int>(part[i][0]-1,part[i][1]-1))

#define EDGES(part, idx) \
	for (int i = 0; i < sizeof(part) / sizeof(part[0]); i++) \
		edges[idx].push_back(pair<int,int>(part[i][0]-1,part[i][1]-1))

#define POS(part, idx, dx, dy) \
	for (int i = 0; i < sizeof(part) / sizeof(part[0]); i++) \
		pos[idx].push_back(pair<float,float>(2*(part[i][0]+dx),2*(part[i][1]+dy)))

	VERT(part1, 0);
	VERT(part2, 1);
	VERT(part3, 2);
	VERT(part4, 3);

	EDGES(edges1, 0);
	EDGES(edges2, 1);
	EDGES(edges3, 2);
	EDGES(edges4, 3);

	POS(pos1, 0, 0, 0);
	POS(pos2, 1, 0, -.7);
	POS(pos3, 2, .7, 0);
	POS(pos4, 3, 3, 3);

	cout << "digraph doms {\nsplines=true\n" << endl;

	for (int dom = 0; dom < 4; dom++) {
//		cout << "subgraph part" << dom << " { " << endl;
		for (int i = 0; i < vert[dom].size(); i++) {
			if (vert[dom][i].first == dom && vert[dom][i].second == i)
				cout << "\"" << dom << "x" << i << "\"[color=" << cols[dom] << 
				",pos=\"" << pos[dom][i].first << "," << pos[dom][i].second <<  "!\"" <<
				"];" << endl;
			else
				cout << "\"" << dom << "x" << i << "\"[color=" << cols[dom] << 
				",pos=\"" << pos[dom][i].first << "," << pos[dom][i].second <<  "!\"" <<
				", style=dashed];" << endl;
		}
//		cout << "}" << endl;
	}
	

	for (int dom = 0; dom < 4; dom++)
		for (int i = 0; i < edges[dom].size(); i++)
			cout << "\"" << 
			dom << "x" << edges[dom][i].first << "\" -> \"" <<
			dom << "x" << edges[dom][i].second << "\"[dir=none,style=bold];" << endl;
	
	for (int dom = 0; dom < 4; dom++)
		for (int i = 0; i < vert[dom].size(); i++) {
			if (vert[dom][i].first == dom && vert[dom][i].second == i)
				continue;
			cout << "\"" << 
			dom << "x" << i << "\" -> \"" <<
			vert[dom][i].first << "x" << vert[dom][i].second << "\"[style=solid];" << endl;
		}

	cout << "}" << endl;

	return 0;
}
