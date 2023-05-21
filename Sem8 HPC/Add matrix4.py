import numpy as np
from numba import cuda

# CUDA kernel for vector addition
@cuda.jit
def vectorAdd(a, b, c):
    tid = cuda.grid(1)
    if tid < c.shape[0]:
        c[tid] = a[tid] + b[tid]

# CUDA kernel for matrix multiplication
@cuda.jit
def matrixMul(a, b, c):
    row, col = cuda.grid(2)
    if row < c.shape[0] and col < c.shape[1]:
        sum = 0
        for i in range(a.shape[1]):
            sum += a[row, i] * b[i, col]
        c[row, col] = sum

def main():
    # Vector addition
    size = 1000000
    h_a = np.random.randint(0, 100, size=size).astype(np.int32)
    h_b = np.random.randint(0, 100, size=size).astype(np.int32)
    h_c = np.zeros_like(h_a)

    # Allocate memory on the device
    d_a = cuda.to_device(h_a)
    d_b = cuda.to_device(h_b)
    d_c = cuda.device_array_like(d_a)

    # Define the grid and block dimensions
    threads_per_block = 256
    blocks_per_grid = (size - 1) // threads_per_block + 1

    # Perform vector addition on the GPU
    vectorAdd[blocks_per_grid, threads_per_block](d_a, d_b, d_c)

    # Transfer the result back to the host
    d_c.copy_to_host(h_c)

    print("Vector Addition Result:")
    print(h_c)

    # Matrix multiplication
    N = 1024
    h_A = np.random.randint(0, 10, size=(N, N)).astype(np.int32)
    h_B = np.random.randint(0, 10, size=(N, N)).astype(np.int32)
    h_C = np.zeros((N, N), dtype=np.int32)

    # Allocate memory on the device
    d_A = cuda.to_device(h_A)
    d_B = cuda.to_device(h_B)
    d_C = cuda.device_array_like(d_A)

    # Define the grid and block dimensions
    threads_per_block = (16, 16)
    blocks_per_grid = ((N - 1) // threads_per_block[0] + 1, (N - 1) // threads_per_block[1] + 1)

    # Perform matrix multiplication on the GPU
    matrixMul[blocks_per_grid, threads_per_block](d_A, d_B, d_C)

    # Transfer the result back to the host
    d_C.copy_to_host(h_C)

    print("Matrix Multiplication Result:")
    print(h_C)

if _name_ == '_main_':
    main()