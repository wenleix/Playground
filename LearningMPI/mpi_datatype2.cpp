#include <cstdio>
#include <algorithm>
#include <mpi.h>

using namespace std;

const int MsgTag = 13;

int main(int argc, char **argv) {
    MPI::Init(argc, argv);

    int worldSize = MPI::COMM_WORLD.Get_size();
    int worldRank = MPI::COMM_WORLD.Get_rank();

    //  Define a MPI type for pair<int, double>
    int blocklens[2] = {1, 1};
    pair<int, double> temp;

    MPI_Aint firstAddr, secondAddr;
    MPI_Get_address(&temp.first, &firstAddr);
    MPI_Get_address(&temp.second, &secondAddr);

    MPI_Aint offsets[2] = {0, secondAddr - firstAddr};
    MPI_Datatype old_types[2] = {MPI_INT, MPI_DOUBLE};

    MPI_Datatype MPI_PAIR_INT_DOUBLE;
    MPI_Type_create_struct(2, blocklens, offsets, old_types, &MPI_PAIR_INT_DOUBLE);
    MPI_Type_commit(&MPI_PAIR_INT_DOUBLE);

    if (worldRank != 0) {
        pair<int, double> msg(worldRank, worldSize / 10.0);
        MPI::COMM_WORLD.Send(&msg, 1 /* count */, MPI_PAIR_INT_DOUBLE, 0 /* dest */, MsgTag);
    } else {
        printf("Main node !\n");
        pair<int, double> buf;
        for (int r = 1; r < worldSize; r++) {
            MPI::COMM_WORLD.Recv(&buf, 1 /* count */, MPI_PAIR_INT_DOUBLE, r /* src */, MsgTag);
            printf("Receive pair (%d, %.2f) form Process %d !\n", buf.first, buf.second, r);
        }
    }

    MPI_Type_free(&MPI_PAIR_INT_DOUBLE);
    MPI::Finalize();

    return 0;
}

