#include <cstdio>
#include <cstring>
#include <mpi.h>

const int MaxString = 100;

int main(int argc, char **argv) {
    char greeting[MaxString];
    int commSize;
    int myRank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    if (myRank != 0) {
        sprintf(greeting, "Greetings from process %d of %d!\n", myRank, commSize);
        MPI_Send(greeting, strlen(greeting) + 1, MPI_CHAR, 0 /* dest */, 0 /* tag */, MPI_COMM_WORLD);
    } else {
        printf("Main node !\n");
        for (int q = 1; q < commSize; q++) {
            MPI_Recv(greeting, MaxString, MPI_CHAR, q /* source */, 0 /* tag */, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", greeting);
        }
    }

    MPI_Finalize();
    return 0;
}

