#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <mpi.h>

const int MaxString = 100;

//  An example for Sendrecv
//  Comment: Send a message and post a receive before blocking. Will block until the sending application buffer is free for reuse and until the receiving application buffer contains the received message.
//  See https://computing.llnl.gov/tutorials/mpi/ and http://www.mcs.anl.gov/research/projects/mpi/www/www3/MPI_Sendrecv.html
//  Pass messages alone a ring

const int PassStep = 3;
const int MsgTag = 37;  //  A randomly picked number.

int main(int argc, char **argv) {
    MPI::Init(argc, argv);
    
    int worldSize = MPI::COMM_WORLD.Get_size();
    int worldRank = MPI::COMM_WORLD.Get_rank();

    if (worldSize <= PassStep) {
        char errorBuf[1000];
        sprintf(errorBuf, "World Size: %d, is less then the pass step %d!\n", worldSize, PassStep);
        fprintf(stderr, "%s", errorBuf);
        throw std::logic_error(errorBuf);
    }
    
    char sendBuf[MaxString];
    char recvBuf[MaxString];
    int dest = (worldRank + PassStep) % worldSize;
    int src = (worldRank + worldSize - PassStep) % worldSize;
    sprintf(sendBuf, "Hello to %d from %d", dest, src);

    MPI::COMM_WORLD.Sendrecv(sendBuf, strlen(sendBuf) + 1, MPI::CHAR, dest, MsgTag, 
            recvBuf, sizeof(recvBuf), MPI::CHAR, src, MsgTag);
    printf("Process %d received message: %s\n", worldRank, recvBuf);

    MPI::Finalize();

    return 0;
}

