from mpi4py import MPI
from sys import getsizeof
import time

# Get info
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

N = 10

if rank == 0:
    # master

    for plus_1000 in range(51):
        obj = [69420]*(1000*plus_1000 + 1)
        L = getsizeof(obj) # in bytes
    
        T = time.time()
        for j in range(N):
            MPI.COMM_WORLD.send(obj, dest=1, tag=1000*plus_1000+j)
            obj = MPI.COMM_WORLD.recv(source=1, tag=1000*plus_1000+j+1)
        T = time.time() - T
    
        print(f"{L} B:    {((2 * N * L * 10e-6) / T):.2f} MB/s")#    {len(obj)}")

elif rank == 1:
    # only one worker
    for plus_1000 in range(51):
        for i in range(N):
            mes = MPI.COMM_WORLD.recv(source=0, tag=1000*plus_1000+i)
            MPI.COMM_WORLD.send(mes, dest=0, tag=1000*plus_1000+i+1)

