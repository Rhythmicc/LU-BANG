from rich.console import Console
from rich.progress import Progress

from concurrent.futures import ThreadPoolExecutor, wait

import numpy as np
import os


sz = [32 * i for i in range(1, 129)] + [128 * i for i in range(1, 65)]
console = Console()
process = Progress(console=console)
pid = process.add_task('Data Gen', total= len(sz) * 5)
pool = ThreadPoolExecutor(max_workers=8)
jobls = []


def mapSzToNum(sz):
    return 5


def write_mtx(n: int, mtx: np.array, filename: str, is_tril: bool = False):
    with open(filename, 'w') as f:
        print(n, file=f)
        if not is_tril:
            for line in mtx:
                print(' '.join([str(i) for i in line]), file=f)
        else:
            for idx, line in enumerate(mtx):
                print(' '.join([str(i) for i in line[:idx+1]]), file=f)


def doWork(size: int, case: int):
    if os.path.exists(f'dist/{size}/{case}_ans') and os.path.exists(f'dist/{size}/{case}_test'):
        process.advance(pid, 1)
        return
    mtx = np.tril(np.random.randint(1, 10, (size, size)))
    write_mtx(size, mtx, f'dist/{size}/{case}_ans', True)
    mtx = np.dot(mtx, mtx.T)
    write_mtx(size, mtx, f'dist/{size}/{case}_test')
    process.advance(pid, 1)
    del mtx


console.log('Start generating data')
process.start()
process.start_task(pid)
for i in sz:
    if not (os.path.exists('dist/%d' % i) and os.path.isdir('dist/%d' % i)):
        os.mkdir('dist/%d' % i)
    for j in range(mapSzToNum(i)):
        jobls.append(pool.submit(doWork, i, j))
wait(jobls)
process.stop()
console.log('Done')
