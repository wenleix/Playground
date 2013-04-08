//  Test MPI_Probe for Async Message Send/Recv

#include <cstdio>
#include <cstring>
#include <mpi.h>
#include <cmath>

using namespace std;

const int MsgTag = 17;

int main(int argc, char **argv) {
    MPI::Init(argc, argv);
    
    int worldSize = MPI::COMM_WORLD.Get_size();
    int worldRank = MPI::COMM_WORLD.Get_rank();

    if (worldRank == 0) {
        int msgRecvCount = 0;
        while (msgRecvCount != 10 * (worldSize - 1)) {
            //  Receive all the messages
            for (int src = 1; src < worldSize; src++) {
                int recvCount = 0;
                while (MPI::COMM_WORLD.Iprobe(src, MsgTag)) {
                    double recvSum = 0;
                    MPI::COMM_WORLD.Recv(&recvSum, 1 /* count */, MPI_DOUBLE, src, MsgTag);
                    recvCount++;
                }
                if (recvCount != 0) {
                    fprintf(stderr, "Receive %d messages from %d !\n", recvCount, src);
                    msgRecvCount += recvCount;
                }
            }
        }
    } else {
        for (int i = 0; i < 10; i++) {
            double sum = 0.0;
            for (int j = 0; j < 100; j++)
                sum += exp(1.0 / j);

            MPI::COMM_WORLD.Send(&sum, 1 /* count */, MPI_DOUBLE, 0 /* dest */, MsgTag);
        } 
    }

    MPI::Finalize();
}

