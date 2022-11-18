#!/usr/bin/env python3
from mpi4py import MPI
import numpy

# WORKER

comm = MPI.Comm.Get_parent()
rank = comm.Get_rank()

# data = None
comm.send(rank, dest=0, tag=10)

print(f"Worker created with rank {rank}")

comm.Disconnect()
