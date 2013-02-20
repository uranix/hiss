int part1[18][2] = {
	{2, 13}, {2, 17}, {1, 13}, {1, 4}, {1, 5},
	{3, 11}, {1, 12}, {1, 8}, {1, 9}, {1, 11},
	{1, 11}, {1, 12}, {1, 13}, {3, 14}, {1, 11},
	{1, 8}, {1, 4}, {1, 18}
};

int part2[20][2] = {
	{4, 5},	{4, 6},	{3, 16}, {2, 4}, {2, 5},
	{4, 10}, {3, 15}, {2, 8}, {2, 9}, {2, 10},
	{4, 12}, {3, 14}, {2, 13}, {2, 14}, {3, 4},
	{1, 4}, {2, 17}, {3, 7}, {1, 5}, {3, 11}
};

int part3[20][2] = {
	{2, 10}, {4, 15}, {2, 14}, {3, 4}, {4, 18},
	{2, 17}, {3, 7}, {3, 8}, {4, 20}, {1, 18},
	{3, 11}, {3, 12}, {1, 13}, {3, 14}, {3, 15}, 
	{3, 16}, {4, 23}, {2, 13}, {2, 8}, {2, 4}
};

int part4[26][2] = {
	{4, 24}, {4, 2}, {4, 3}, {4, 23}, {4, 5},
	{4, 6}, {4, 7}, {2, 4}, {2, 5}, {4, 10},
	{4, 11}, {4, 12}, {4, 13}, {2, 10}, {4, 15},
	{4, 16}, {3, 4}, {4, 18}, {3, 8}, {4, 20},
	{4, 21}, {3, 16}, {4, 23}, {4, 24}, {4, 5},
	{4, 2}
};

float pos1[18][2] = {
	{.3, 2.5}, {1.5, 2}, {-.8, 2}, {0, 2}, {1, 1.5},
	{2, 1.3}, {-.8, 1}, {0, 1}, {1, 1}, {-.8, 0},
	{0, 0}, {1, 0}, {2, 0}, {3, 0}, {0, -.8},
	{1, -.8}, {2, -.8}, {1.5, 1}
};

float pos2[20][2] = {
	{0, 8}, {1, 7.7}, {-1, 7}, {0, 7}, {1, 6.7},
	{2, 7.3}, {-1, 6}, {0, 6}, {.9, 5.7}, {2.3, 6},
	{3, 7}, {-1, 5}, {0, 5}, {1.6, 5.2}, {3, 5.4},
	{-.3, 4.2}, {.8, 4.5}, {1.8, 4.5}, {.3, 4}, {1.4, 4}
};

float pos3[20][2] = {
	{4.2, 3}, {5.3, 3.1}, {3.4, 2.2}, {4.5, 2.2}, {5.6, 2.2},
	{3, 1.5}, {4.1, 1.5}, {5.5, 1.2}, {6.7, 1.2}, {3, .7},
	{3.7, 1}, {4.8, .9}, {3, 0}, {4, 0}, {5, 0}, 
	{6, 0}, {7, 0}, {4, -1}, {5, -1}, {6, -1}
};

float pos4[26][2] = {
	{-1, 6.2}, {0, 6}, {1.1, 5.9}, {-1, 5.2}, {0, 5.2},
	{1, 4.9}, {2.5, 5.1}, {0, 4.3}, {1, 3.9}, {2, 4.3},
	{3.5, 4.2}, {2.7, 3.5}, {4.5, 3.5}, {2.2, 3}, {3.5, 2.8},
	{5, 2.5}, {3, 2}, {4.2, 2}, {3.5, 1}, {4.5, 1}, 
	{5.5, 1.3}, {3.8, 0}, {4.8, 0}, {5.8, 0}, {4.8, -1},
	{5.8, -1}
};

int edges1[21][2] = {
	{1, 4}, {2, 5}, {3, 4}, {4, 5}, {4, 8},
	{5, 9}, {5, 18}, {6, 18}, {7, 8}, {8, 9},
	{8, 11}, {9, 12}, {9, 18}, {10, 11}, {11, 12},
	{11, 15}, {12, 13}, {12, 16}, {13, 14}, {13, 17},
	{13, 18}
};

int edges2[24][2] = {
	{1, 4}, {2, 5}, {3, 4}, {4, 5}, {4, 8},
	{5, 6}, {5, 9}, {5, 10}, {7, 8}, {8, 9},
	{8, 13}, {9, 13}, {9, 14}, {9, 17}, {10, 11}, 
	{10, 14}, {10, 15}, {12, 13}, {13, 16}, {13, 17}, 
	{14, 17}, {14, 18},	{17, 19}, {17, 20}
};

int edges3[24][2] = {
	{1, 4}, {2, 4}, {3, 7}, {4, 7}, {4, 8},
	{5, 8}, {6, 11}, {7, 11}, {7, 12}, {8, 9},
	{8, 12}, {8, 16}, {10, 11}, {11, 12}, {11, 14},
	{12, 14}, {12, 15}, {13, 14}, {14, 15}, {14, 18},
	{15, 16}, {15, 19}, {16, 17}, {16, 20}
};

int edges4[34][2] = {
	{1, 2}, {2, 3}, {2, 5}, {3, 6}, {3, 7},
	{4, 5}, {5, 6}, {5, 8}, {6, 9}, {6, 10},
	{7, 10}, {7, 11}, {9, 10}, {10, 12}, {11, 12},
	{11, 13}, {12, 14}, {12, 15}, {13, 15}, {13, 16}, 
	{15, 17}, {15, 18}, {16, 18}, {16, 21}, {18, 19}, 
	{18, 20}, {19, 20}, {20, 21}, {20, 23}, {21, 24}, 
	{22, 23}, {23, 24}, {23, 25}, {24, 26}
};