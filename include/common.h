#include <SockClient/SockClient.h>
#include <cu2bang_util.h>
#include <math.h>

void check(float *A, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j)
            if (A[i * n + j] != 1 && A[i * n + j] != 0) {
                printf("ERROR: A[%d, %d] = %.4f\n", i, j, A[i * n + j]);
                return;
            }
    puts("LU success!");
}
