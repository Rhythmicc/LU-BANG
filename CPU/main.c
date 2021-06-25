#include "common.h"

float lu(float*A, int n) {
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j) {
            A[j * n + i] /= A[i * n + i];
            for (int x = i + 1; x < n; ++x) A[j * n + x] -= A[j * n + i] * A[i * n + x];
        }
    gettimeofday(&t2, NULL);
    float time_lu = (t2.tv_sec - t1.tv_sec) * 1000.0 + (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("The LU(CPU) factorization takes %.2f ms\n", time_lu);
    return time_lu;
}

int main(int argc, char**argv) {
    int n = atoi(argv[1]);
    float *A = (float *)malloc(sizeof(float) * n * n);

    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) A[i * n + j] = i < j ? i + 1: j + 1;

    float useTime = lu(A, n);
    check(A, n);
    free(A);
    return 0;
}
