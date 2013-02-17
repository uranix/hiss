#ifndef __HISS__MPI_IMPL_H__
#define __HISS__MPI_IMPL_H__

#include <mpi.h>
#include "interprocess.h"

namespace hiss {

class MPI_impl : public interprocess {
	const int tag;
	MPI::Intracomm local_comm;
	int hash(const char *str);
public:
	MPI_impl(const char *hostname = 0);
	virtual void barrier();

	virtual void send(int *buf, int count, int to);
	virtual void recv(int *buf, int count, int from);

	virtual int probe_size(int from);
	virtual void sendrecv(double *sbuf, int scnt, int to, double *rbuf, int rcnt, int from);
	virtual void sendrecv(index *sbuf, int scnt, int to, index *rbuf, int rcnt, int from);

	virtual ~MPI_impl();
};

};

#endif
