from mpi4py import MPI
import time

def sleep_for(tm=25):
    full_times = int(tm/5)
    for i in range(full_times):
        time.sleep(5)
        print("WAITING...")
    rest = tm % 5
    time.sleep(rest)

# Get my rank
rank = MPI.COMM_WORLD.Get_rank()

if rank == 0:
    # master
    mes0 = "AMOGUS"
    MPI.COMM_WORLD.isend(mes0, dest=1, tag=0)
    sleep_for()
    mes1 = MPI.COMM_WORLD.recv(source=1, tag=1)
    print(f"Master {rank} received worker message '{mes1}'")

# this program will work only with single worker
if rank == 1:
    # worker
    mes0 = MPI.COMM_WORLD.recv(source=0, tag=0)
    print(f"Worker {rank} received master message '{mes0}'")
    mes1 = mes0 + " back"
    MPI.COMM_WORLD.isend(mes1, dest=0, tag=1)
    print(f"Worker {rank} sent message '{mes1}' to master")

