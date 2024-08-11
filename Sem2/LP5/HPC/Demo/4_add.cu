%%cu 
#include<bits/stdc++.h>
#include<cuda.h>

using namespace std;

__global__ void add(int *a,int *b,int *c,int n)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if(tid<n)
    {
        c[tid] = a[tid] + b[tid];
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
        cout<<a[i]<<" ";
    }
}

int main()
{
    int n = 5;

    int size = n;
    size_t mem = size * sizeof(int);

    int *A, *B, *C;
    int *X, *Y, *Z;

    A = new int[size];
    B = new int[size];
    C = new int[size];

    initialize(A, n);
    initialize(B, n);

    cout<<"Vector A:- \n";
    print(A, n);

    cout<<"Vector B:- \n";
    print(B, n);

    cudaMalloc(&X, mem);
    cudaMalloc(&Y, mem);
    cudaMalloc(&Z, mem);

    cudaMemcpy(X, A, mem, cudaMemcpyHostToDevice);
    cudaMemcpy(Y, B, mem, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocksPerThread = (n + threads - 1) / threads;

    add<<<blocksPerThread,threads>>> (X,Y,Z,n);
    
    cudaMemcpy(C, Z, mem, cudaMemcpyDeviceToHost);

    cout<<"Vector C:- ";
    print(C, n);

    delete[] A;
    delete[] B;
    delete[] C;

    cudaFree(X);
    cudaFree(Y);
    cudaFree(Z);

}