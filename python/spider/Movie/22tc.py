import re  # 正则表达式
import requests  # 获取网页
from bs4 import BeautifulSoup

##拿到发现图片页面信息

domian = "https://tc.lsy22.com/explore"

i = 1

UA = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/123.0.0.0 Safari/537.36"}

param = {"page": i,
         "seek": "2023-10-20+13%3A40%3A23.5pOu"}

resp = requests.get(domian, headers=UA)

page = BeautifulSoup(resp.text, "html.parser")

list = page.find_all("div", class_="list-item fixed-size c8 gutter-margin-right-bottom")

resp.close()

href = []
##获取子页面
for item in list:
    href.append(item.find("div", class_="list-item-image fixed-size").find("a").get("href"))
j = 0
## 下载图片
for i in range(len(list)):
    j += 1
    ##获取链接
    resp = requests.get(href[i], headers=UA)
    page = BeautifulSoup(resp.text, "html.parser")
    image = page.find("div", class_="content-width margin-top-10").find("div",
                                                                        class_="header header-content margin-bottom-10").find(
        "div", class_="header-content-right").find("a").get("href")
    ##下载图片
    img_resp = requests.get(image, headers=UA)
    img_name = r"image\\"+str(j)+"."+image.split(".")[-1]
    img_file =open(img_name, "wb")
    img_file.write(img_resp.content)
    ##关闭下载
    print("成功",j,"次")
    img_file.close()
    img_file.close()
    resp.close()
