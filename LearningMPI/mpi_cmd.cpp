//  Test the command-line input for MPI
#include <mpi.h>
#include <cstdio>

using namespace std;

int main(int argc, char** argv) {
    MPI::Init(argc, argv);

    int worldSize = MPI::COMM_WORLD.Get_size();
    int worldRank = MPI::COMM_WORLD.Get_rank();
    fprintf(stderr, "Process %d has %d parameters.\n", worldRank, argc);
    for (int i = 0; i < argc; i++) {
        fprintf(stderr, "Process %d, parameter %d: %s\n", worldRank, i, argv[i]);
    }
    MPI::Finalize();
}

