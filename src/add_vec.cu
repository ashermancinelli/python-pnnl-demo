
#include <cassert>
#include <cstdio>
#include <cuda.h>
#include <cuda_runtime.h>
#include "cublas_v2.h"

void add_vec_kernel(double* a, double* b, double* c, int size)
{
  cudaError_t cudaStat;
  cublasStatus_t stat;
  cublasHandle_t handle;
  double *da, *db;
  
  cudaStat = cudaMalloc((void**)&da, sizeof(double) * size); assert(cudaStat == cudaSuccess);
  cudaStat = cudaMalloc((void**)&db, sizeof(double) * size); assert(cudaStat == cudaSuccess);
  cudaStat = cudaMemcpy(da, a, sizeof(double) * size, cudaMemcpyHostToDevice); assert(cudaStat == cudaSuccess);
  cudaStat = cudaMemcpy(db, b, sizeof(double) * size, cudaMemcpyHostToDevice); assert(cudaStat == cudaSuccess);
  stat = cublasCreate(&handle); assert(stat == CUBLAS_STATUS_SUCCESS);
  double one=1.;
  stat = cublasDaxpy(handle, size, &one, a, 1, b, 1); assert(stat == CUBLAS_STATUS_SUCCESS);
  cudaStat = cudaMemcpy(c, db, sizeof(double) * size, cudaMemcpyDeviceToHost); assert(cudaStat == cudaSuccess);
  stat = cublasDestroy(handle);
  cudaFree(da);
  cudaFree(db);
}
