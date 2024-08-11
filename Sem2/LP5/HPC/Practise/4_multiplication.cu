%%cu
#include<bits/stdc++.h>
#include<cuda.h>

#define BLOCK_SIZE 16

using namespace std;

__global__ void multiply(int *a,int *b,int *c,int c_rows,int common,int c_cols)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int sum = 0;

    if(col < c_cols && row < c_rows)
    {
        for (int j = 0; j < common;j++)
        {
            sum += a[row * common + j] * b[j * c_cols + col];
        }
        c[c_cols * row + col] = sum;
    }
}

void initialize(int *a,int rows,int cols)
{
    for (int i = 0; i < rows;i++)
    {
        for (int j = 0; j < cols;j++)
        {
            a[i * cols + j] = rand() % 10;
        }
    }
}

void print(int *a,int rows,int cols)
{
    for (int i = 0; i < rows;i++)
    {
        for (int j = 0; j < cols;j++)
        {
            cout << a[i * cols + j] << " ";
        }
        cout << endl;
    }
}



int main()
{
    int A_rows = 3, A_cols = 2, B_rows = 2, B_cols = 4, C_rows = A_rows, C_cols = B_cols;

    int *A, *B, *C;
    int *m1, *m2, *m3;

    int A_size = A_rows * A_cols;
    int B_size = B_rows * B_cols;
    int C_size = C_rows * C_cols;

    A = new int[A_size];
    B = new int[B_size];
    C = new int[C_size];

    cudaMalloc(&m1, A_size * sizeof(int));
    cudaMalloc(&m2, B_size * sizeof(int));
    cudaMalloc(&m3, C_size * sizeof(int));


    initialize(A, A_rows, A_cols);
    cout << "Matrix A:- " << endl;
    print(A, A_rows, A_cols);

    initialize(B, B_rows, B_cols);
    cout << "Matrix B:- " << endl;
    print(B, B_rows, B_cols);

    cudaMemcpy(m1, A, A_size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(m2, B, B_size * sizeof(int), cudaMemcpyHostToDevice);

    dim3 dimGrid(A_rows + BLOCK_SIZE - 1 / BLOCK_SIZE, B_cols + BLOCK_SIZE - 1 / BLOCK_SIZE);
    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);

    multiply<<<dimGrid, dimBlock>>>(m1, m2, m3, C_rows, A_cols, C_cols);

    cudaMemcpy(C,m3,C_size*sizeof(int),cudaMemcpyDeviceToHost);

    cout << "Matrix C:- " << endl;
    print(C, C_rows, C_cols);

    delete[] A;
    delete[] B;
    delete[] C;

    cudaFree(m1);
    cudaFree(m2);
    cudaFree(m3);
}

