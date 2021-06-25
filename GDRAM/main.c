#include "common.h"

extern cnrtQueue_t __cu2bang_CommandQueue;
typedef float value_type;

void lu_gdram(value_type*A, int n);

float lu(value_type*A, int n) {
    value_type*dA = NULL;
    cnrtMalloc((void**)&dA, sizeof(value_type) * n * n);
    cnrtMemcpy(dA, A, sizeof(value_type) * n * n, CNRT_MEM_TRANS_DIR_HOST2DEV);
    cnrtKernelParamsBuffer_t param;
    cnrtGetKernelParamsBuffer(&param);
    cnrtKernelParamsBufferAddParam(param, &dA, sizeof(value_type*));
    cnrtKernelParamsBufferAddParam(param, &n, sizeof(int));

    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    cnrtInvokeKernel_V2((void*)&lu_gdram, (cnrtDim3_t) {1, 1, 1}, param, CNRT_FUNC_TYPE_BLOCK, __cu2bang_CommandQueue);
    gettimeofday(&t2, NULL);

    cnrtMemcpy(A, dA, sizeof(value_type) * n * n, CNRT_MEM_TRANS_DIR_DEV2HOST);

    check(A, n);
    float time_lu = (t2.tv_sec - t1.tv_sec) * 1000.0 + (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("The LU(GDRAM) factorization takes %.2f ms\n", time_lu);

    cnrtFree(dA);
    return time_lu;
}

int main(int argc, char**argv) {
__cu2bang_Init();
    int n = atoi(argv[1]);
    float *A = (float *)malloc(sizeof(float) * n * n);

    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) A[i * n + j] = i < j ? i + 1: j + 1;

    float useTime = lu(A, n);

    free(A);
__cu2bang_Cleanup();
    return 0;
}
