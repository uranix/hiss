#ifndef __HISS__MPI_IMPL_H__
#define __HISS__MPI_IMPL_H__

#include "common.h"
#include <stdint.h>
#include <mpi.h>

namespace hiss {

class MPI_impl {
	int size;
	int rank;
	int device;
	MPI::Comm localComm;
	int hostname2color(char *hostname) {
		unsigned char *p = reinterpret_cast<unsigned char *>hostname;
		uint32_t hash = 0;
		uint32_t upper;
		while (*p) {
			upper = hash & 0xf8000000;
			hash <<= 5;
			hash |= (upper >> 27);
			hash ^= (uint32_t)*p++;
		}
		return (int)hash;
	}
public:
	MPI_impl(const char *hostname = 0) { 
		MPI::Init(); 
		size = MPI::COMM_WORLD.Get_size();
		rank = MPI::COMM_WORLD.Get_rank();
		int color;
		if (hostname) 
			color = hostname2color(hostname)
		else {
			char hostname[256];
			gethostname(hostname, 255);
			color = hostname2color(hostname)
		}
		localComm = MPI::COMM_WORLD.Split(hostname2color(hostname), rank);
		device = localComm.Get_rank();
	}
	virtual ~MPI_impl() { MPI::Finalize(); }
	virtual int rank() { return rank; }
	virtual int device() { return device; }
	virtual int size() { return size; }
};

};

#endif
