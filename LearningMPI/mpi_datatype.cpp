#include <cstdio>
#include <algorithm>
#include <mpi.h>

using namespace std;

const int MsgTag = 13;

int main(int argc, char **argv) {
    MPI::Init(argc, argv);

    int worldSize = MPI::COMM_WORLD.Get_size();
    int worldRank = MPI::COMM_WORLD.Get_rank();

    //  Define a MPI type for pair<int, int>
    int blocklens[2] = {1, 1};
    MPI_Aint offsets[2] = {0, sizeof(int)};
    MPI_Datatype old_types[2] = {MPI_INT, MPI_INT};
    MPI_Datatype MPI_PAIR_INT_INT;
    MPI_Type_struct(2, blocklens, offsets, old_types, &MPI_PAIR_INT_INT);
    MPI_Type_commit(&MPI_PAIR_INT_INT);

    if (worldRank != 0) {
        pair<int, int> msg(worldRank, worldSize);
        MPI::COMM_WORLD.Send(&msg, 1 /* count */, MPI_PAIR_INT_INT, 0 /* dest */, MsgTag);
    } else {
        printf("Main node !\n");
        pair<int, int> buf;
        for (int r = 1; r < worldSize; r++) {
            MPI::COMM_WORLD.Recv(&buf, 1 /* count */, MPI_PAIR_INT_INT, r /* src */, MsgTag);
            printf("Receive pair (%d, %d) form Process %d !\n", buf.first, buf.second, r);
        }
    }

    MPI_Type_free(&MPI_PAIR_INT_INT);
    MPI::Finalize();

    return 0;
}

