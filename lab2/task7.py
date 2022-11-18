from mpi4py import MPI
from sys import getsizeof
import time

# Get info
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

N = 10

assert size == N, f"Number of workers ({size}) != {N}"

cycle_list = list(range(N)) + [0]
mes = "Sample text"

for i in range(N+1):
    if i == rank or i == rank+N:
        if i != 0:
            req = MPI.COMM_WORLD.irecv(source=cycle_list[i-1], tag=i-1)
            mes = req.wait()
            print(f"Node {rank} received message: '{mes}' from node {cycle_list[i-1]}.")
        if i != N:
            MPI.COMM_WORLD.send(mes, dest=cycle_list[i+1], tag=i)
            print(f"Node {rank} sent message to node {cycle_list[i+1]}.")
