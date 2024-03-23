import re

import requests

i = 0  # 控制页数的遍历

url = "https://movie.douban.com/top250"

UA = {"User-Agent":
          "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/123.0.0.0 Safari/537.36"}

douban = [] #储存数据

##预订正则表达式
obj = re.compile(r'<li>.*?<span class="title">(?P<title>.*?)</span>.*?'
                 r' <span class="playable">\[(?P<playable>.*?)\]</span>.*?'
                 r'<p class="">.*?导演: (?P<name>[\u4e00-\u9fa5]+).*?&nbsp;&nbsp;&nbsp;.*?'
                 r'<br>.*?(?P<time>\d+)',re.S)

##循环获取数据
for i in range(0,250,25):

    param = {"start": i,
             "filter": ""
             }

    resp = requests.get(url, headers=UA, params=param)
    sj = obj.findall(resp.text)
    douban.append(sj)
    resp.close()

##输出
for i in range(0,10):
    for j in douban[i]:
        print(j)
