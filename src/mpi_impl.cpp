#include "mpi_impl.h"
#include <stdint.h>
#include <cassert>

namespace hiss {

int MPI_impl::hash(const char *str) {
	unsigned const char *p = reinterpret_cast<unsigned const char *>(str);
	uint32_t ret = 0;
	uint32_t upper;
	while (*p) {
		upper = ret & 0xf8000000;
		ret <<= 5;
		ret |= (upper >> 27);
		ret ^= (uint32_t)*p++;
	}
	return (int)ret;
}

MPI_impl::MPI_impl(const char *hostname) : tag('H' + ('I' << 8) | ('S' << 16) | ('S' << 24)) { 
	MPI::Init(); 
	assert(sizeof(index) == MPI::UNSIGNED_LONG.Get_size());
	assert(sizeof(int) == MPI::INT.Get_size());

	_size = MPI::COMM_WORLD.Get_size();
	_rank = MPI::COMM_WORLD.Get_rank();
	int color;
	if (hostname) 
		color = hash(hostname);
	else {
		char hostname[MPI_MAX_PROCESSOR_NAME+1];
		int ret;
		MPI::Get_processor_name(hostname, ret);
		color = hash(hostname);
	}
	local_comm = MPI::COMM_WORLD.Split(color, _rank);
	_device = local_comm.Get_rank();
}

MPI_impl::~MPI_impl() { 
	local_comm.Free();
	MPI::Finalize(); 
}

void MPI_impl::barrier() {
	MPI::COMM_WORLD.Barrier();
}

void MPI_impl::send(int *buf, int cnt, int to) {
	(void) MPI::COMM_WORLD.Send(buf, cnt, MPI::INT, to, tag);
}

void MPI_impl::recv(int *buf, int cnt, int from) {
	(void) MPI::COMM_WORLD.Recv(buf, cnt, MPI::INT, from, tag);
}

void MPI_impl::sendrecv(double *sbuf, int scnt, int to, double *rbuf, int rcnt, int from) {
	(void) MPI::COMM_WORLD.Sendrecv(
		sbuf, scnt, MPI::DOUBLE, to, tag,
		rbuf, rcnt, MPI::DOUBLE, from, tag);
}

void MPI_impl::sendrecv(int *sbuf, int scnt, int to, int *rbuf, int rcnt, int from) {
	(void) MPI::COMM_WORLD.Sendrecv(
		sbuf, scnt, MPI::INT, to, tag,
		rbuf, rcnt, MPI::INT, from, tag);
}

void MPI_impl::sendrecv(index *sbuf, int scnt, int to, index *rbuf, int rcnt, int from) {
	(void) MPI::COMM_WORLD.Sendrecv(
		sbuf, scnt, MPI::UNSIGNED_LONG, to, tag,
		rbuf, rcnt, MPI::UNSIGNED_LONG, from, tag);
}

};
