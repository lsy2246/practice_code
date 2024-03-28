import requests  # 请求
from threading import Thread  # 单线程
from lxml import etree  # xpath
import re  # 正则表达
import os  # 系统
import json  # json
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor  # 多线程/多进程
import csv

from pip._internal.utils import urls

filename = "xingcaidi.csv"

csvfile = open(filename, 'a+', newline='')
writer = csv.writer(csvfile)

writer.writerow(
    ['品名', '一级分类', '最低价', '最高价', '平均价', '产地', '规格', '单位', '发布日期'])


def download(index):
    url = "http://www.xinfadi.com.cn/getPriceData.html"
    print(index)
    data = {
        "limit": "20",
        "current": index,
        "pubDateStartTime": "",
        "pubDateEndTime": "",
        "prodPcatid": "",
        "prodCatid": "",
        "prodName": ""
    }

    obj = re.compile(r'"prodName":"(?P<prodName>.*?)"'
                     r'.*?"prodCat":"(?P<prodCat>.*?)",'
                     r'.*?"lowPrice":"(?P<lowPrice>.*?)",'
                     r'"highPrice":"(?P<highPrice>.*?)",'
                     r'"avgPrice":"(?P<avgPrice>.*?)",'
                     r'"place":"(?P<place>.*?)",'
                     r'"specInfo":"(?P<specInfo>.*?)",'
                     r'"unitInfo":"(?P<unitInfo>.*?)",'
                     r'"pubDate":"(?P<pubDate>.*?)"', re.S)

    get = requests.post(url=url, data=data)

    data = obj.findall(get.text)

    content = []

    for item in data:
        content_item = tuple(field.replace('\\', '') for field in item)
        content.append(content_item)

    for row in content:
        writer.writerow(row)


if __name__ == '__main__':
    with ThreadPoolExecutor(max_workers=100) as t:
        for index in range(1,1):
            t.submit(download, index=index)

print("打印完成")
csvfile.close()
