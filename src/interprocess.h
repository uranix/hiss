#ifndef __HISS__INTERPROCESS_H__
#define __HISS__INTERPROCESS_H__

#include "common.h"
#include <vector>

namespace hiss {

class interprocess {
protected:	
	int _size;
	int _rank;
	int _device;
public:
	interprocess() { }
	virtual ~interprocess() { }

	virtual void barrier() = 0;

	virtual void send(int *buf, int count, int to) = 0;
	virtual void recv(int *buf, int count, int from) = 0;
	virtual int probe_size(int from) = 0;

	virtual void sendrecv(double *sbuf, int scnt, int to, double *rbuf, int rcnt, int from) = 0;
	virtual void sendrecv(index *sbuf, int scnt, int to, index *rbuf, int rcnt, int from) = 0;

	virtual int rank() { return _rank; }
	virtual int device() { return _device; }
	virtual int size() { return _size; }
};

};

#endif
