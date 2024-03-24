import re  # 正则表达式
import requests  # 获取网页
import warnings
warnings.filterwarnings("ignore")#去除443警告

file = open("电影天堂.txt","a+",encoding="utf-8")


index = 1

domain = "https://www.dyttcn.com"


UA = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/123.0.0.0 Safari/537.36"}

rules1 = re.compile(r'<a href="(?P<url>.*?.html)" class="ulink" title="\d+年.*?片《.*?》.*?">.*?</a>')


data1 = []

for index in range(1, 16):
    class_typical = f"/jingdiandapian/list_18_{index}.html"
    resp1 = requests.get(domain + class_typical, headers=UA, verify=False)
    resp1.close()
    resp1.encoding = "gb2312"
    data1.append(rules1.findall(resp1.text))




rules2 = re.compile(r'.*?◎片　　名　(?P<name>.*?)</p>'
                    r'.*?◎年　　代　(?P<year>\d+)</p>'
                    r'.*?◎类　　别　(?P<class>.*?)</p>'
                    r'.*?<a href="(?P<url>magnet:\?xt=urn:btih:.*?")>',re.S)



for i in data1:
    for j in i:
        if type(j) == str:
            resp2 = requests.get(domain + j, headers=UA, verify=False)
        elif type(j) == list:
            resp2 = requests.get(domain + j[0], headers=UA, verify=False)
        print(j)
        resp2.close()
        resp2.encoding = "gb2312"
        data2 = rules2.findall(resp2.text)
        if len(data2) > 0:
            print(str(data2))
            file.write(str(data2))
            file.write('\n')



file.close()
