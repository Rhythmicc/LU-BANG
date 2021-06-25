#include "cu2bang_util.h"
extern void addKernel(int * c, const int * a, const int * b);

cnrtDev_t __cu2bang_Device;
cnrtQueue_t __cu2bang_CommandQueue;

cnrtDim3_t globalWorkSize;
cnrtDim3_t localWorkSize;
cnrtFunctionType_t globalFuncType;
void __cu2bang_Init() {
    cnrtInit(0);
    cnrtGetDeviceHandle(&__cu2bang_Device, 0);
    cnrtSetCurrentDevice(__cu2bang_Device);
    cnrtCreateQueue(&__cu2bang_CommandQueue);
    globalFuncType = CNRT_FUNC_TYPE_UNION4;
}

void __cu2bang_Cleanup() {
}
