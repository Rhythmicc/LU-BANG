# LU implementation with BANG

[toc]

## ENV

### Hardware

1. CPU: 32 cores
2. MLU: MLU270
3. MEM: 30 GB

### Software

1. [QuickProject](https://github.com/Rhythmicc/QuickProject): compile, run & report performance.
2. [SockServer](https://github.com/Rhythmicc/SockServer): get performance reports then upload them to cloud & test process control.
3. Cambricon BANG Lauguage toolkits


## Structure

1. `.vscode`: vscode settings
2. `benchmark`: A SockServer Implementation to get performance and upload them to cloud.
3. versions:
    1. `CPU`: LU implementation with CPU.
    2. `GDRAM`: LU implementation using MLU270 GDRAM.
    3. `NRAM`: LU implementation using MLU270 NRAM and NFUs.
    4. `NRAMNRS`: (Splited NRAM N-row parallel algorithm) LU implementation using MLU270 NRAM, NFUs and many cores.
    5. `NRAMNRC`: (Combined NRAM N-row parallel algorithm) LU implementation using MLU270 NRAM, NFUs and many cores.
    6. `NRAMRB`: (NRAM Row-block parallel algorithm) Another LU implementation using MLU270 NRAM, NFUs, many cores and Balanced core scheduling strategy.
4. `include`: common headers for different versions
5. `test`: A link symbol of current testing version
6. `main.py`: test script


## TEST

```shell
qrun <version> <matrix size> [LB-using-cores-number, default=4] [-build: compile before running]
```

This command will create or cover a link symbol named `test` to `<version>`, and it will generate a specific square matrix to test, which like the following format:

    ```
    [
        1, 1, 1, 1, 1,
        1, 2, 2, 2, 2,
        1, 2, 3, 3, 3,
        1, 2, 3, 4, 4,
        1, 2, 3, 4, 5
    ]
    ```

So, the correct LU will be:

    ```
    [
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1
    ]
    ```
It's easy and fast to verify.

### Examples:

1. Use CPU version to test a 1024 * 1024 matrix
    ```shell
    qrun cpu 1024
    ```

2. Use CPU version to test a 1024 * 1024 matrix, compile before running
    ```shell
    qrun cpu 1024 -build
    ```
