import os
import requests
from SockServer import SockServer

dataPath = {}

def dfs(rt: str):
    if not os.path.isdir(rt):
        return [os.path.abspath(rt)]
    if not rt.endswith('/'):
        rt += '/'
    res = []
    ls = os.listdir(rt)
    for item in ls:
        cur = rt + item
        if os.path.isdir(cur):
            res += dfs(cur)
        else:
            res.append(os.path.abspath(cur))
    return res

def buildIndex():
    ls = dfs('DataGen/dist')
    for item in ls:
        try:
            key = int(item.split('/')[-2])
        except:
            continue
        if key not in dataPath:
            dataPath[key] = []
        item = item.replace('_test', '').replace('_ans', '')
        if item not in dataPath[key]:
            dataPath[key].append(item)

buildIndex()

server = SockServer(8000, workers=8)

@server.register()
def getData(size:int, index:int):
    if size not in dataPath:
        return False, f'No such size: {size}'
    if index >= len(dataPath[size]):
        return False, f'INDEX LIMIT'
    return True, dataPath[size][index]


@server.register()
def getSizeLength(size:int, tableName: str):
    url = f'http://vhr.aliyun.rhythmlian.cn/checkSize?size={size}&tableName={tableName}'
    res = int(requests.get(url).text)
    # return True, str(max(len(dataPath[size]) - res, 0))
    return True, str(max(1 - res, 0))


@server.register()
def rebuild():
    buildIndex()


@server.register()
def report(size:int, block:int, index:int, useTime:float, tableName: str):
    _gflops = size * size * size / 3 / useTime / 1e6
    url = f'http://vhr.aliyun.rhythmlian.cn/?index={index}&size={size}&block={block}&gflops={_gflops}&tableName={tableName}'
    server.console.print(server.infoString, '开始请求:', url)
    try:
        res = requests.get(url).text
        server.console.print(res, justify='center')
        return True, 'Success'
    except Exception as e:
        return False, repr(e)


if __name__ == '__main__':
    server.start()
