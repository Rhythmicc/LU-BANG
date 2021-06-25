#include "common.h"

extern cnrtQueue_t __cu2bang_CommandQueue;
typedef float value_type;

#define min(a, b) (a) < (b)? (a): (b)
#define max(a, b) (a) > (b)? (a): (b)

int usingKernelNum = 4;

void lu_kernel(value_type*A, int n, int i, int RowBlockSz, int workingKernelNum);

float lu(value_type*A, int n) {
    value_type*dA = NULL;
    cnrtMalloc((void**)&dA, sizeof(value_type) * n * n);
    cnrtMemcpy(dA, A, sizeof(value_type) * n * n, CNRT_MEM_TRANS_DIR_HOST2DEV);
    
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    for (int i = 0; i < n - 1; ++i) {
        int RowBlockSz = ceil((n - i - 1) * 1.0 / usingKernelNum);

        cnrtKernelParamsBuffer_t param;
        cnrtGetKernelParamsBuffer(&param);
        cnrtKernelParamsBufferAddParam(param, &dA, sizeof(value_type*));
        cnrtKernelParamsBufferAddParam(param, &n, sizeof(int));
        cnrtKernelParamsBufferAddParam(param, &i, sizeof(int));
        cnrtKernelParamsBufferAddParam(param, &RowBlockSz, sizeof(int));
        cnrtKernelParamsBufferAddParam(param, &usingKernelNum, sizeof(int));
        
        cnrtInvokeKernel_V2(
            (void*)&lu_kernel, 
            (cnrtDim3_t) {16, 1, 1}, 
            param, 
            CNRT_FUNC_TYPE_UNION4, 
            __cu2bang_CommandQueue);
    }
    gettimeofday(&t2, NULL);

    cnrtMemcpy(A, dA, sizeof(value_type) * n * n, CNRT_MEM_TRANS_DIR_DEV2HOST);

    check(A, n);
    float time_lu = (t2.tv_sec - t1.tv_sec) * 1000.0 + (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("The LU(NRAMRB) factorization takes %.2f ms\n", time_lu);

    cnrtFree(dA);
    return time_lu;
}

int main(int argc, char**argv) {
__cu2bang_Init();
    int n = atoi(argv[1]);
    if (argc > 2) usingKernelNum = atoi(argv[2]);

    float *A = (float *)malloc(sizeof(float) * n * n);

    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) A[i * n + j] = i < j ? i + 1: j + 1;

    float useTime = lu(A, n);

    free(A);
__cu2bang_Cleanup();
    return 0;
}
