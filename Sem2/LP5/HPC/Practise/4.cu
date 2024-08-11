%%cu

#include <bits/stdc++.h>

using namespace std;

__global__ void add(int* A,int *B,int *C, int n)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if(tid < n)
    {
        C[tid] = A[tid] + B[tid];
    }
}

void initialize(int *a,int n)
{
    for (int i = 0; i < n;i++)
    {
        a[i] = rand() % 100;
    }
}

void print(int *a,int n)
{
    for (int i = 0; i < n;i++)
    {
        cout << a[i]<<" ";
    }
    cout << endl;
}

int main()
{
    int n = 5;

    int *A, *B, *C;

    int size = n;
    size_t memBytes = size * sizeof(int);

    A = new int[size];
    B = new int[size];
    C = new int[size];

    initialize(A, n);
    initialize(B, n);

    cout << "Vector A:- " << endl;
    print(A, n);
    cout << "Vector B:- " << endl;
    print(B, n);

    int *X, *Y, *Z;
    cudaMalloc(&X, memBytes);
    cudaMalloc(&Y, memBytes);
    cudaMalloc(&Z, memBytes);

    cudaMemcpy(X, A, memBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(Y, B, memBytes, cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

    add<<<blocksPerGrid , threadsPerBlock>>>(X,Y,Z,n);

    cudaMemcpy(C, Z, memBytes, cudaMemcpyDeviceToHost);

    cout<<"Vector C :- "<<endl;
    print(C,n);

    delete[] A;
    delete[] B;
    delete[] C;

    cudaFree(X);
    cudaFree(Y);
    cudaFree(Z);
}
