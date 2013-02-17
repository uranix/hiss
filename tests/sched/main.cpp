#include <stdlib.h>
#include <mpi_impl.h>
#include <sparsecomm.h>

#include <iostream>

using namespace std;
using namespace hiss;

int main() {
	MPI_impl mpi;
	sparsecomm sc(&mpi);
	cout << "I'm " << mpi.rank() << " of " << mpi.size() << " using device " << mpi.device() << endl;
	srand(mpi.rank() + 100);

	set<int> comm_with;

	for (int i = 0; i < mpi.size(); i++) 
		if ((rand() & 3) == 3)
			comm_with.insert(i);

	for (set<int>::iterator j = comm_with.begin(); j != comm_with.end(); ++j) 
		cout << "I'm " << mpi.rank() << " and I want communicate with " << *j << endl;

	sc.build_sched(comm_with);
	mpi.barrier();
	cout << flush;

	for (int color = 0; color < sc.rounds.size(); color++) {
		if (sc.rounds[color] >= 0)
			cout << mpi.rank() << " communicating with " << sc.rounds[color] << endl;
		mpi.barrier();
		if (!mpi.rank())
			cout << " ---------------- New round ------------------ " << endl;
		cout << flush;
		mpi.barrier();
	}

	return 0;
}
