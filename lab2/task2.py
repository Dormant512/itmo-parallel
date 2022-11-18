from mpi4py import MPI
import numpy as np

# Get my rank
rank = MPI.COMM_WORLD.Get_rank()

# Define objects
class Pair_of_nums:
    def __init__(self, num1, num2):
        self.num1 = num1
        self.num2 = num2

    def num_sum(self):
        return self.num1 + self.num2

object1 = list(range(42))
object2 = Pair_of_nums(420, 69)
object3 = np.arange(12).reshape((3, 4))

list_of_objects = [object1, object2, object3]

if rank == 0:
    data = list_of_objects
else:
    data = None

data = MPI.COMM_WORLD.scatter(data, root=0)
print(f"Rank {rank} shows data:\n{data}\n")
