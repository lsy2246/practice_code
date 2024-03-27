import requests
from threading import Thread
from lxml import etree
import re
import os


def get_html(url):
    if not os.path.exists("wz"):
        os.mkdir("wz")
    resp = requests.get(url)
    resp.close()
    html = etree.HTML(resp.text)
    title = html.xpath('/html/body/div[2]/div/main/div[1]/div/h1/text()')
    content = html.xpath('/html/body/div[2]/div/main/article/div')
    title = ''.join(list(title[0]))
    file = open(f"wz\\{title}.txt", "a+", errors='ignore')
    URL = (f"URL : {url}\n")
    file.write(URL)
    print(f"正在抓取{title}")
    ## 获取内容
    for i in content:
        text = i.xpath('.//text()')
        for word in text:
            file.write(word)
    file.close()
    print(f"{title}抓取成功")


for index in range(1, 4):
    domain = f"https://wyc21.com/index.php/page/{index}"
    resp = requests.get(domain)
    resp.close()
    html = etree.HTML(resp.text)
    dev = html.xpath("/html/body/div[2]/div/main/div[1]/div")
    urls = []
    for item in dev:
        url = item.xpath("./div[2]/div[1]/a/@href")
        urls.append(url[0])

    for url in urls:
        get_html(url)
