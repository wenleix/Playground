#include <cstdio>
#include <cstring>
#include <mpi.h>

const int MaxString = 100;

int main(int argc, char **argv) {
    char greeting[MaxString];
    int commSize;
    int myRank;

    MPI::Init(argc, argv);
    commSize = MPI::COMM_WORLD.Get_size();
    myRank = MPI::COMM_WORLD.Get_rank();

    if (myRank != 0) {
        sprintf(greeting, "Greetings from process %d of %d!\n", myRank, commSize);
        MPI::COMM_WORLD.Send(greeting, strlen(greeting) + 1, MPI_CHAR, 0 /* dest */, 0 /* tag */);
    } else {
        printf("Main node !\n");
        for (int q = 1; q < commSize; q++) {
//            MPI::Status ignoreStatus;
//            MPI::COMM_WORLD.Recv(greeting, MaxString, MPI_CHAR, q /* source */, 0 /* tag */, ignoreStatus);
        
            //  We can simply omit the status argument.
            MPI::COMM_WORLD.Recv(greeting, MaxString, MPI_CHAR, q /* source */, 0 /* tag */);
            printf("%s\n", greeting);
        }
    }

    MPI_Finalize();
    return 0;
}

