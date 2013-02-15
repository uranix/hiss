#ifndef __HISS__VECTOR_H__
#define __HISS__VECTOR_H__

#include "common.h"

namespace hiss {

template <class T>
struct vector {
	index nSelf;
	index *nGhost;
	T *self;
	T **ghost;
	index **map;
	index **rmap;

};

};

#endif
