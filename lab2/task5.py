from mpi4py import MPI
import numpy as np

# Get info
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

if rank == 0:
    # master
    num = int(10e5)
    
    vec1 = np.random.random(num)
    vec2 = np.random.random(num)

    mes1 = np.array_split(vec1, size-1)
    mes2 = np.array_split(vec2, size-1)
    
    for worker in range(size-1):
        req1 = MPI.COMM_WORLD.isend(mes1[worker], dest=worker+1, tag=worker+1)
        req2 = MPI.COMM_WORLD.isend(mes2[worker], dest=worker+1, tag=worker+1001)

    dot_prod = 0

    for worker in range(size-1):
        dot_prod += MPI.COMM_WORLD.recv(source=worker+1, tag=worker+2001)

    print(f"Total dot product:         {dot_prod:.3f}")

else:
    # workers
    arr1 = MPI.COMM_WORLD.recv(source=0, tag=rank)
    arr2 = MPI.COMM_WORLD.recv(source=0, tag=rank+1000)
    result = np.dot(arr1, arr2)
    print(f"Worker {rank} submitting sum:   {result:.4f}")

    res = MPI.COMM_WORLD.isend(result, dest=0, tag=rank+2000)

