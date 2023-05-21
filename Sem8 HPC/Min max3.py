import numpy as np
from numba import cuda

# Define the block size
block_size = 256

@cuda.reduce
def reduction_min(a, b):
    return min(a, b)

@cuda.reduce
def reduction_max(a, b):
    return max(a, b)

@cuda.reduce
def reduction_sum(a, b):
    return a + b

@cuda.reduce
def reduction_avg(a, b):
    return a + b

def parallel_reduction(arr):
    # Allocate memory on the GPU
    arr_gpu = cuda.to_device(arr)

    # Determine the grid size based on the array size
    n = arr.shape[0]
    grid_size = (n - 1) // block_size + 1

    # Perform parallel reduction for min, max, sum, and average
    min_val = reduction_min(arr_gpu)
    max_val = reduction_max(arr_gpu)
    sum_val = reduction_sum(arr_gpu)
    avg_val = reduction_avg(arr_gpu) / n

    # Transfer the results back to the CPU
    min_val = min_val.item()
    max_val = max_val.item()
    sum_val = sum_val.item()
    avg_val = avg_val.item()

    return min_val, max_val, sum_val, avg_val

# Test the parallel reduction
arr = np.random.randint(0, 100, size=1000000)
min_val, max_val, sum_val, avg_val = parallel_reduction(arr)

print("Min:", min_val)
print("Max:", max_val)
print("Sum:", sum_val)
print("Average:", avg_val)